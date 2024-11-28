#include <VARSTEP_ultrasonic.h>

#define trigger_pin 8
#define echo_pin 9

double distance_cm, distance_m;

VARSTEP_ultrasonic my_HCSR04(trigger_pin, echo_pin); // You can create multiple instances for multiple sensors

void setup() {
  // put your setup code here, to run once:
  while(!Serial);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  distance_cm = my_HCSR04.distance_cm();
  distance_m = my_HCSR04.distance_m();

  if(distance_cm == -1.0) {
    Serial.println("No distance detected");
  } else {
    Serial.print("Distance: ");
    Serial.print(distance_cm);
    Serial.print("cm | ");
    Serial.print(distance_m);
    Serial.println("m");
  }

  delay(100); // We recommend 100ms minimum delay for good accuracy.
}
