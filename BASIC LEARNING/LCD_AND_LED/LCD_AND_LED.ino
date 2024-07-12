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
}


void loop()
{
  delay(2000);
  digitalWrite(12, HIGH);
  lcd.clear();
   lcd.setCursor(2,0);
  lcd.print("LED 1 IS ON");
   lcd.setCursor(3,1);
   digitalWrite(13, HIGH);
   lcd.setCursor(2,1);
  lcd.print("LED 2 IS ON");
  delay(2000);
  digitalWrite(12, LOW);
  lcd.clear();
   lcd.setCursor(2,0);
  lcd.print("LED 1 IS OFF");
   lcd.setCursor(3,1);
   digitalWrite(13, LOW);
   lcd.setCursor(2,1);
  lcd.print("LED 2 IS OFF");
}
