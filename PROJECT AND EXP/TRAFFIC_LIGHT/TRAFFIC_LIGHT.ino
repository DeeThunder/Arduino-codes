#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
}


void loop()
{
   lcd.setCursor(0,0);
  lcd.print("TRAFFIC LIGHT");
  delay(2000);
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(14, LOW);
  lcd.clear();
   lcd.setCursor(4,0);
  lcd.print("STOP");
  delay(10000);
  
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(14, LOW);
  lcd.clear();
   lcd.setCursor(3,0);
  lcd.print("READY");
delay(3000);

  digitalWrite(14, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  lcd.clear();
   lcd.setCursor(5,0);
  lcd.print("GO");
  delay(2000);
}
