#include <HCSR04.h> 
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
const int oneWireBus = 4;     

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

// Initializing and defining the pins of the Ultrasonic sensor 
UltraSonicDistanceSensor distanceSensor(5, 18); 

const int trigPin =5;
const int echoPin =18;

#define SOUND_SPEED 0.034 // defining values to sound speed 

long duration;
float distanceCm;

void temp(){
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(temperatureC);
  lcd.print("ºC");
  Serial.print(temperatureC);
  Serial.println("ºC");
  
  Serial.print(temperatureF);
  Serial.println("ºF");
  lcd.setCursor(0,1);
  lcd.print(temperatureF);
  lcd.print("ºF");
}

void setup(){
  Serial.begin(115200);
  // Start the DS18B20 sensor
  sensors.begin();
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  pinMode(trigPin, OUTPUT); // making the trigpin an output pin 
  pinMode(echoPin, INPUT); // making the echopin a input pin
  }

void loop(){
  digitalWrite(trigPin, LOW); //clears the trigpin
  delayMicroseconds(2); // delays the trig pin for 2 microseconds 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn (echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED/2; // calculates the distance away from the ultra sonic sensor 
  Serial.print("Distance(cm): ");
  Serial.println(distanceCm);

// Control statement for the Ultrasonic sensor and servo motor 
//  if ( distanceCm <= 10.00){
  temp();
//  delay(5000);
//  }
//  else {
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("ERROR");
//  }
}
