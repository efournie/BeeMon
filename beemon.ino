#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <HX711.h>
#include <LiquidCrystal_I2C.h>

// Settings
const int LCD_SCREEN = 1;
const int WEB_SERVER = 1;
const int TEST_MODE = 0;
const int DEEP_SLEEP_TIME_SEC = 1800;
const int WIFI_INIT_MAX_SEC = 5;

// Web server
const char *ssid = "dd-wrt";
const char *password = "classyunicorn377";

const int SCALE_DOUT_PIN = 14;  // = D5
const int SCALE_SCK_PIN = 12;   // = D6
const int DHT2PIN = 13;         // = D7
const int BATTERY_PIN = A0;
const float SCALE_CALIBRATION_FACTOR = 47.905;
const int SCALE_CALIBRATION_OFFSET = 199725;

HX711 scale;
DHT dht(DHT2PIN, DHT22);
LiquidCrystal_I2C lcd(0x27, 16, 2);


///
/// Setup
///
void setup() 
{
  //  Initialize everything
  Serial.begin(115200);
  Serial.setTimeout(2000);
  // Wait for serial to initialize.
  while(!Serial) { }
  delay(500);
  Serial.println("Serial port initialized.");
  pinMode(BATTERY_PIN, INPUT);
  turnOnPeripherals();

  // Wait 5 seconds, read sensors and publish results to LCD and/or web server
  delay(5000);
  float voltage = getBattery();
  float temp = getTemp();
  float humidity = getHumidity();
  float weight = getWeight();

  if(!TEST_MODE)
  {
    if(LCD_SCREEN) lcdOut(weight, temp, humidity, voltage);
    if(WEB_SERVER) webOut(weight, temp, humidity, voltage);
    delay(5000);
    turnOffPeripherals();
  }
}


///
/// Peripherals on / off
///

void turnOnPeripherals()
{
  if(LCD_SCREEN)
  {
    Serial.println("LCD initialization...");
    lcd.init();   // initializing the LCD
    lcd.backlight();
    clearLcd();
    lcd.setCursor(0, 0);
    lcd.print("BeeMon");
    lcd.setCursor(0, 1);
    lcd.print("Init.");
  }
  if(WEB_SERVER)
  {
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi");
    int wait_sec = 0;
    while(WiFi.status() != WL_CONNECTED && wait_sec < WIFI_INIT_MAX_SEC)
    {
      delay(1000);
      Serial.print(".");
      wait_sec++;
    }
    if(wait_sec == WIFI_INIT_MAX_SEC)
    {
      Serial.println("WiFi connection failed, last tentative...");
      WiFi.begin(ssid, password);
      delay(1000);
    }
    if (WiFi.status() == WL_CONNECTED && LCD_SCREEN)
    {
       lcd.setCursor(15, 0);
       lcd.print("w");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
  }
  if (LCD_SCREEN)
  {
    lcd.setCursor(5,1);
    lcd.print(".");
  }
  Serial.println("Temperature and humidity sensor initialization...");
  dht.begin(); // initialize dht22
  if (LCD_SCREEN)
  {
    lcd.setCursor(6,1);
    lcd.print(".");
  }
  Serial.println("Weight sensors initialization...");
  scale.begin(SCALE_DOUT_PIN, SCALE_SCK_PIN);
  scale.set_offset(SCALE_CALIBRATION_OFFSET);
  scale.set_scale(SCALE_CALIBRATION_FACTOR);
  scale.power_up();
  if (LCD_SCREEN)
  {
    lcd.setCursor(7,1);
    lcd.print(".");
  }
  Serial.println("All sensors initialized!");
}

void turnOffPeripherals()
{
  Serial.println("Turning off peripherals and activating deep sleep for " + String(DEEP_SLEEP_TIME_SEC) + "seconds...");
  lcd.setCursor(15, 1);
  lcd.print("z");
  scale.power_down();
  Serial.flush();
  ESP.deepSleep(DEEP_SLEEP_TIME_SEC * 1e6, WAKE_RFCAL);
}

void clearLcd()
{
  lcd.clear();
  if (WiFi.status() == WL_CONNECTED && LCD_SCREEN)
  {
     lcd.setCursor(15, 0);
     lcd.print("w");
  }  
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
  String line1=String(weight, 1) + "kg  " + String(temp, 1)+"C";
  String line2=String(humidity, 1) + "%  " + String(voltage, 1) + "V";
  clearLcd();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void webOut(float weight, float temp, float humidity, float voltage)
{
  String temperature_url = "http://192.168.1.100:1974/store_hive_temp.php";
  String temperature_data = "temp_sensor=" + String(temp, 1);
  String humidity_url = "http://192.168.1.100:1974/store_hive_humidity.php";
  String humidity_data = "humidity_sensor=" + String(humidity, 1);
  String weight_url = "http://192.168.1.100:1974/store_hive_weight.php";
  String weight_data = "weight_sensor=" + String(weight, 1);
  String battery_url = "http://192.168.1.100:1974/store_hive_battery.php";
  String battery_data = "battery=" + String(voltage, 1);

  postReading(temperature_url, temperature_data);
  postReading(humidity_url, humidity_data);
  postReading(weight_url, weight_data);
  postReading(battery_url, battery_data);
}

void postReading(String url, String data)
{
  Serial.println("Posting " + data + " to " + url + "...");
  if(WiFi.status()== WL_CONNECTED)
  {
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpResponseCode = http.POST(data);
    String payload = http.getString();
    if (httpResponseCode <= 0)
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
/// Main loop
///

void loop() 
{
  if(TEST_MODE)
  {
    delay(5000);
    float voltage = getBattery();
    Serial.println("Battery: " + String(voltage, 2));
    float temp = getTemp();
    Serial.println("Temperature: " + String(temp, 2) + "C");
    float humidity = getHumidity();
    Serial.println("Humidity: " + String(humidity, 2) + "%");
    float weight = getWeight();
    Serial.println("Weight: " + String(weight, 2) + "kg");
    if(LCD_SCREEN) lcdOut(weight, temp, humidity, voltage);
    if(WEB_SERVER) webOut(weight, temp, humidity, voltage);
  }
}
