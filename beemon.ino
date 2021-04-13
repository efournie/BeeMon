#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <HX711.h>
#include <LiquidCrystal_I2C.h>

// Settings
#define LCD_SCREEN 1
#define WEB_SERVER 1
#define TEST_MODE 0
const int DEEP_SLEEP_TIME_SEC = 30;

// Web server
const char *ssid = "wifi_ssid";
const char *password = "wifi_password";
String webserver = "192.168.1.100:1974";
String weburi_temp = "/store_hive_temp.php";
String weburi_humidity = "/store_hive_humidity.php";
String weburi_weight = "/store_hive_weight.php";
String weburi_battery = "/store_hive_battery.php";

// Weight sensor
const int SCALE_DOUT_PIN = 14;  // = D5
const int SCALE_SCK_PIN = 12;   // = D6
HX711 scale;

// DHT22 Temperature and humidity sensor
const int DHT2PIN = 13;         // = D7
#define DHT2TYPE DHT22
DHT dht(DHT2PIN, DHT2TYPE);

// Battery
#define BATTERY_PIN A0

// LCD
LiquidCrystal_I2C lcd(0x3F, 16, 2);


///
/// Peripherals on / off
///

void turnOnPeripherals()
{
  #ifdef LCD_SCREEN
  lcd.init();   // initializing the LCD
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("BeeMon");
  lcd.setCursor(0, 1);
  lcd.print("...startup...");
  #endif
  #ifdef WEB_SERVER
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  #endif
  dht.begin(); // initialize dht22
  scale.begin(SCALE_DOUT_PIN, SCALE_SCK_PIN);
  scale.set_scale(-6000/0.128);
  scale.power_up();
}

void turnOffPeripherals()
{
  scale.power_down();
  Serial.flush();
  ESP.deepSleep(DEEP_SLEEP_TIME_SEC * 1e6, WAKE_RFCAL);
}

float getBattery()
{
   float volt = analogRead(BATTERY_PIN);
   return volt/233.8;
}


///
/// Sensors reading
///

float getTemp()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // Read temperature as Celsius
  float temp = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(temp) || (temp < -30.0) || (temp > 60.0))
  {
    Serial.println("DHT22 reading seems wrong!");
    temp = 0.0;
  }
  return temp;
}
  
float getHumidity()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // Read humidity
  float humidity = dht.readHumidity();
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || (humidity < 0.0) || (humidity > 100.0))
  {
    Serial.println("DHT22 reading seems wrong!");
    humidity = 0.0;
  }
  return humidity;
}
  
float getWeight()
{
  float weight;
  if (scale.is_ready()) 
  {
    weight = scale.get_units(4);
    Serial.print("HX711 reading: ");
    Serial.println(weight);
  } else {
    Serial.println("HX711 not found.");
    weight = 0.0;
  }
  return weight;
}


///
/// Publish results
///

void lcdOut(float weight, float temp, float humidity, float voltage)
{
  String line1=String(weight, 1) + "kg   " + String(temp, 1)+"C";
  String line2=String(humidity, 1) + "%   " + String(voltage, 1) + "V";
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void webOut(float weight, float temp, float humidity, float voltage)
{
  String serverTemp = webserver + weburi_temp;
  String serverHumidity = webserver + weburi_humidity;
  String serverWeight = webserver + weburi_weight;
  String serverBattery = webserver + weburi_battery;

  postReading(serverTemp, "?temp_sensor=" + String(temp, 1));
  postReading(serverHumidity, "?humidity_sensor=" + String(humidity, 1));
  postReading(serverWeight, "?weight_sensor=" + String(weight, 1));
  postReading(serverBattery, "?battery=" + String(voltage, 1));
}

void postReading(String server, String data)
{
  Serial.println("Posting to " + server + "...");
  if(WiFi.status()== WL_CONNECTED)
  {
    HTTPClient http;
    String url = "http://" + server;
    http.begin(url.c_str());
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpResponseCode = http.POST(data);
    String payload = http.getString();
    Serial.println("httpCode: " + httpResponseCode);    // success = 200
    Serial.println("response: " + payload);
    if (httpResponseCode > 0)
    {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else
    {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
      }
  else
  {
    Serial.println("WiFi Disconnected");
  }
}


///
/// Setup and main loop
///
void setup() 
{
  //  Initialize everything
  Serial.begin(115200);
  Serial.setTimeout(2000);
  // Wait for serial to initialize.
  while(!Serial) { }
  pinMode(BATTERY_PIN, INPUT);
  turnOnPeripherals();

  // Wait 5 seconds, read sensors and publish results to LCD and/or web server
  delay(5000);
  float voltage = getBattery();
  float temp = getTemp();
  float humidity = getHumidity();
  float weight = getWeight();
  #ifdef LCD_SCREEN
  lcdOut(weight, temp, humidity, voltage);
  #endif
  #ifdef WEB_SERVER
  webOut(weight, temp, humidity, voltage);
  #endif

  // Wait 5 seconds and go to deep sleep if not in test mode
  #ifndef TEST_MODE
  delay(5000);
  turnOffPeripherals();
  #endif
}

void loop() 
{
  #ifdef TEST_MODE
  delay(5000);
  float voltage = getBattery();
  float temp = getTemp();
  float humidity = getHumidity();
  float weight = getWeight();
  #ifdef LCD_SCREEN
  lcdOut(weight, temp, humidity, voltage);
  #endif
  #ifdef WEB_SERVER
  webOut(weight, temp, humidity, voltage);
  #endif
  #endif
}
