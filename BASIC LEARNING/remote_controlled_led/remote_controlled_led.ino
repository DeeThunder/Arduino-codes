#include <IRremote.h>


const int IR_PIN = 2;

const int LED_PIN = 13;

const int LED_PIN2 = 12;

const int LED_PIN3 = 11;


const int LED_PIN4 = 10;


IRrecv irrecv(IR_PIN);

decode_results results;

bool led2State = false; // Initialize LED state to off

bool led3State = false; // Initialize LED state to off

bool led4State = false; // Initialize LED state to off


void setup() {

  pinMode(LED_PIN, OUTPUT);

  pinMode(LED_PIN2, OUTPUT);

  pinMode(LED_PIN3, OUTPUT);

  pinMode(LED_PIN4, OUTPUT);

  Serial.begin(9600); // Initialize serial communication
  irrecv.enableIRIn(); // Start the IR receiver

}
;

void loop() {

  if (irrecv.decode(&results)) {
    long int Decode= results.value;

    Serial.println(Decode ); // Print the received IR code 
    if (Decode == 1927151938 ) { // Check if the received IR signal matches 540C

      digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle the LED on or off

    }


    if (Decode == 2041407359 ) { // Check if the received IR signal matches 5C110

      led2State = !led2State;
      // Toggle the LED state

      digitalWrite(LED_PIN2, led2State); // Set the LED state according to the toggle

    }


    if (Decode == 1149885338) { // Check if the received IR signal matches 4B0D

      led3State = !led3State; // Toggle the LED state

      digitalWrite(LED_PIN3, led3State); // Set the LED state according to the toggle

    }

  

    if (Decode == 971247875 ) { // Check if the received IR signal matches 240C

      led4State = !led4State; // Toggleq the LED state

      digitalWrite(LED_PIN4, led4State); // Set the LED state according to the toggle

    }

  

    delay(200);
    irrecv.resume(); // Receive the next IR signal

  }

}
