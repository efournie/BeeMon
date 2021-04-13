#include <ESP8266WiFi.h>
#include <DHT.h>
#include <HX711.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>

// Settings
#define LCD_SCREEN 1
#define WEB_SERVER 1
const int DEEP_SLEEP_TIME_SEC = 30;

// Web server
String wifi_ssid = "wifi_ssid";
String wifi_password = "wifi_password";
String webserver = "192.168.1.100:1974";
String weburi_temp = "/store_hive_temp.php";
String weburi_humidity = "/store_hive_humidity.php";
String weburi_weight = "/store_hive_weight.php";

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
  dht.begin(); // initialize dht22
  scale.begin(SCALE_DOUT_PIN, SCALE_SCK_PIN);
  scale.set_scale(-6000/0.128);
  scale.power_up();
  #ifdef LCD_SCREEN
  lcd.init();   // initializing the LCD
  lcd.backlight();
  #endif
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
  // TODO
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

  // Wait 5 seconds and go to deep sleep
  delay(5000);
  turnOffPeripherals();
}

void loop() 
{
}
