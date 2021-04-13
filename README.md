# BeeMon
This is a cheap ESP8266 beehive monitoring system. The system is powered by a solar panel charging a 18650 battery.

It can either display values on an LCD screen or send them to an HTTP server.
KiCad schematics and some custom components are included. The code can be uploaded using the Arduino IDE.

Monitored values are:
- Temperature and humidity using a DHT22 sensor
- Weight with an HX711 module and 4 half bridge strain gauges
- Battery level

## Configuration
- Open beemon.ino using the Arduino IDE
- You will need the following libraries (can be added in Tools -> Manage Libraries...): LiquidCrystal, DHT Sensor Library for ESPx, LiquidCrystal I2C, HX711 Arduino Library.
- According to your hardware, set LCD_SCREEN and WEB_SERVER to 0 or 1
- TEST_MODE can be set to 1 to update the screen and/or the web server every 5 seconds.

## Parts list
- AMS117 Step-Down Voltage regulator
- NodeMCU Lolin V3 or any ESP8266 module with enough pins
- HX711 module with 4 50kg half bridge strain gauges
- DHT22 sensor
- 6V / 2W solar panel
- 18650 battery with corresponding holder
- TP4056 charge controller
- HD44780 1602 2x 16 characters LCD
The total should be less than 50€ for the whole system.
