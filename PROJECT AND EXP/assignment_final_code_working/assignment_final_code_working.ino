#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Define LCD address and dimensions

void setup() {
  lcd.init();                      // Initialize the LCD
 lcd.backlight();                 // Turn on backlight
  lcd.clear();                 // Clear the LCD screen
}

void loop() {
   
  int count = 0;
  bool increasing = true; // Flag to indicate counting direction

  while (true) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Count: ");
    lcd.print(count);
    lcd.setCursor(0, 1);
    lcd.print("Steps: ");
    lcd.print(count / 10); // Calculate the number of steps taken
   

    if (increasing) {
      count+=10; //Increment count by 10
        lcd.setCursor(12,1);
        lcd.print("UP");
      if (count >= 1000) {
        increasing = false; // Change direction to decreasing
      }
    } else {
      count -= 10; // Decrement count by 10
      lcd.setCursor(12,1);
        lcd.print("DOWN");
      if (count <= 0) {
        increasing = true; // Change direction to increasing  
      }
    }
    delay(1000);
  }
}
