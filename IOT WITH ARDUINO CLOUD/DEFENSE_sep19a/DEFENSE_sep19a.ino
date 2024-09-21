#include "arduino_secrets.h"
/* 
  Sketch generated by the Arduino IoT Cloud Thing "Untitled"
  https://create.arduino.cc/cloud/things/b6cbc345-3fde-41a9-96e7-4d821307655e 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  CloudSwitch gREEN;
  CloudSwitch rED;
  CloudLength uLTRASONIC;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <HCSR04.h>
#include <ESP32Servo.h> 

UltraSonicDistanceSensor distanceSensor(5, 18);

const int trigPin =5;
const int echoPin =18;


#define SOUND_SPEED 0.034

long duration;
Servo myservo;
int pos=0;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(13, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);
  myservo.attach(25);

}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  digitalWrite(trigPin, LOW); //clears the trigpin
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn (echoPin, HIGH);
  uLTRASONIC = duration * SOUND_SPEED/2;
  Serial.print("Distance(cm): ");
  Serial.println(uLTRASONIC);
    if(uLTRASONIC >= 11.00){
      for (pos =0; pos<=90; pos+=45){
    myservo.write(pos);
      digitalWrite(13, HIGH);
      digitalWrite(27, LOW);
      digitalWrite(26, LOW);
    Serial.println("low WATER LEVEL");
      }

  }
  else if ((uLTRASONIC <=10.59) && (uLTRASONIC >=2.51) ) {
    digitalWrite(13, LOW);
      digitalWrite(27, HIGH);
      digitalWrite(26, LOW);
    Serial.println("AVERAGE WATER LEVEL");
  }
  else if(uLTRASONIC <=2.50){
    for (pos =90; pos>=0; pos-=45){
    myservo.write(pos);
      digitalWrite(13, LOW);
      digitalWrite(27, LOW);
      digitalWrite(26, HIGH);
    Serial.println("FULL WATER LEVEL");
    }  
  }
  delay(1000);
  
  
}


/*
  Since RED is READ_WRITE variable, onREDChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onREDChange()  {
  // Add your code here to act upon RED change
  rED = digitalRead(13);
  if (rED== HIGH){
    for (pos =180; pos>=0; pos-=90){
    myservo.write(pos);
  }
  }
}

/*
  Since YELLOW is READ_WRITE variable, onYELLOWChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onYELLOWChange()  {
  // Add your code here to act upon YELLOW change
}

/*
  Since GREEN is READ_WRITE variable, onGREENChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onGREENChange()  {
  // Add your code here to act upon GREEN change
  gREEN = digitalRead(26);
  if (gREEN== HIGH){
    for (pos =0; pos<=180; pos+=90){
    myservo.write(pos);
  }
  }
}

/*
  Since ULTRASONIC is READ_WRITE variable, onULTRASONICChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onULTRASONICChange()  {
  // Add your code here to act upon ULTRASONIC change
}



