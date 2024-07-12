#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor(5, 18);

LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int trigPin =5;
const int echoPin =18;

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void setup(){
  lcd.init();                    
  lcd.backlight();               
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop(){
  digitalWrite(trigPin, LOW); //clears the trigpin
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn (echoPin, HIGH);

  distanceCm = duration * SOUND_SPEED/2;
  distanceInch = distanceCm*CM_TO_INCH;
  
  lcd.setCursor(0,0);
  lcd.print("cm: ");
  lcd.print(distanceCm);
  lcd.setCursor(0,1);
  lcd.print("inch: ");
  lcd.print(distanceInch);

  delay(1000);
}
