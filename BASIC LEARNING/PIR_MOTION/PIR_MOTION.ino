#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
int ledPin = 5;      // choose the pin for the LED
int inputPin = 18;     // choose the input pin (for PIR sensor)
int pirState = LOW;             
int val = 0; 

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
}

void loop(){
  val = digitalRead(inputPin);    
  if (val == HIGH)  
  {            
    digitalWrite(ledPin, HIGH);  
  
    if (pirState == LOW) 
  {
      lcd.setCursor(0,0);
      lcd.print("Motion detected!"); 
      pirState = HIGH;
    }
  } 
  else 
  {
    digitalWrite(ledPin, LOW); 
    if (pirState == HIGH)
  {
      lcd.setCursor(0,1);
      lcd.print("Motion ended!");  
      pirState = LOW;
    }
  }
}
