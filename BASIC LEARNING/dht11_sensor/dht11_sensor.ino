#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define DHTPIN 13     // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();                    
  lcd.backlight();               
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("DHTxx test!");
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f =0; dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).7DE7FY7D7F7EFEF
  if (isnan(h) || isnan(t) || isnan(f)) {
      lcd.setCursor(0,1);
      lcd.print("Failed to read from DHT sensor!");
    //return;
  }
else {
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("%  Temperature: ");
  lcd.print(t);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("°C ");
  lcd.print(f);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("°F  Heat index: ");
  lcd.print(hic);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("°C ");
  lcd.print(hif);
  lcd.print("°F");
  }
}
