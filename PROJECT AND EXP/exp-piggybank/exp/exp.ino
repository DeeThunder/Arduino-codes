#include <ESP32Servo.h> // including the library for the Ultrasonic sensor 
#include <HCSR04.h> // including the library for servo motor 

// Initializing and defining the pins of the Ultrasonic sensor 
UltraSonicDistanceSensor distanceSensor(5, 18); 

const int trigPin =13;
const int echoPin =12;

#define SOUND_SPEED 0.034 // defining values to sound speed 

long duration;
float distanceCm;

// Initializing the servo motor
Servo myservo;
int pos=0;

void setup(){
  Serial.begin(9600); // initializing the serial monitor 
  myservo.attach(14);
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
  if ( distanceCm <= 5.00){
    for (pos =180; pos>=0; pos-=90){
    myservo.write(pos);
    }
  }
    else {
      for (pos =0; pos<=180; pos+=90){
    myservo.write(pos);
  }
 }
  delay(3000);
}
