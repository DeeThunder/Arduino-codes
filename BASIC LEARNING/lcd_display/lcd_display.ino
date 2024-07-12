#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  // Print a message to the LCD.
  
}


void loop()
{
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Happy");
   lcd.setCursor(3,1);
  lcd.print("Birthday");
}
