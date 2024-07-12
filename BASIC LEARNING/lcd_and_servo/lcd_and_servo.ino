#include <ESP32Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 
Servo myservo;

void setup(){
  myservo.attach(13);
  lcd.init();                    
  lcd.backlight();               
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SERVO ANGLE");
  
}

void loop(){
  int pos = 0;
  for (pos =0; pos<=180; pos+=5){
    myservo.write(pos);
    lcd.setCursor(0,1);
    lcd.print(pos);
    lcd.print(" ");
    delay(500);
  }
   for (pos =180; pos>=0; pos-=5){
    myservo.write(pos);
    lcd.setCursor(0,1);
    lcd.print(pos);
    lcd.print(" ");
    delay(500);
  }
}
