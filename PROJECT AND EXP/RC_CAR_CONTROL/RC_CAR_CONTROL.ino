#include <BluetoothSerial.h> // Include the Bluetooth Serial library

// Define Motor Control Pins
// Assuming MOTOR_IN1/MOTOR_IN2 control one motor (e.g., Left Motor)
// Assuming MOTOR_IN3/MOTOR_IN4 control another motor (e.g., Right Motor)
// Assuming MOTOR_PWM controls the speed of both motors (global speed)
#define MOTOR_IN1 4
#define MOTOR_IN2 5
#define MOTOR_IN3 19
#define MOTOR_IN4 23
#define MOTOR_PWM 25

// Initialize Bluetooth Serial
BluetoothSerial SerialBT;

// Global variable for motor speed (0-255)
int motorSpeed = 150; // Default speed

void setup() {
  Serial.begin(115200); // Initialize USB Serial for debugging output
  Serial.println("Starting RC Control Standalone Sketch...");

  // Initialize Bluetooth Serial
  SerialBT.begin("ESP32_RC_Car"); // Give your ESP32 a recognizable Bluetooth name
  Serial.println("Bluetooth Started! Ready to pair.");

  // Set motor control pins as outputs
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_IN3, OUTPUT);
  pinMode(MOTOR_IN4, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT); // PWM pin for speed control

  // Start with motors stopped and at default speed
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  digitalWrite(MOTOR_IN3, LOW);
  digitalWrite(MOTOR_IN4, LOW);
  analogWrite(MOTOR_PWM, motorSpeed); // Set initial speed
}

void loop() {
  // Check if any data is available from Bluetooth
  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('\n'); // Read incoming command until newline
    command.trim(); // Remove any leading/trailing whitespace

    Serial.print("Received BT Command: ");
    Serial.println(command);

    // --- Motor Control Logic ---
    // Example Protocol:
    // "F" -> Forward (Both motors)
    // "B" -> Backward (Both motors)
    // "L" -> Turn Left (Left motor backward, Right motor forward)
    // "R" -> Turn Right (Left motor forward, Right motor backward)
    // "S" -> Stop (Both motors)
    // "VXXX" -> Set Speed (e.g., "V150" for speed 150)

    if (command.startsWith("V")) {
      int receivedSpeed = command.substring(1).toInt(); // Extract number after 'V'
      motorSpeed = constrain(receivedSpeed, 0, 255); // Limit speed to 0-255
      analogWrite(MOTOR_PWM, motorSpeed);
      Serial.print("Set Speed: ");
      Serial.println(motorSpeed);
    } else if (command == "F") {
      digitalWrite(MOTOR_IN1, HIGH); // Left Motor Forward
      digitalWrite(MOTOR_IN2, LOW);
      digitalWrite(MOTOR_IN3, HIGH); // Right Motor Forward
      digitalWrite(MOTOR_IN4, LOW);
      Serial.println("Moving Forward");
    } else if (command == "B") {
      digitalWrite(MOTOR_IN1, LOW);  // Left Motor Backward
      digitalWrite(MOTOR_IN2, HIGH);
      digitalWrite(MOTOR_IN3, LOW);  // Right Motor Backward
      digitalWrite(MOTOR_IN4, HIGH);
      Serial.println("Moving Backward");
    } else if (command == "L") { // Turn Left (Right motor forward, Left motor backward/stop)
      digitalWrite(MOTOR_IN1, LOW); // Left Motor Reverse (pivot)
      digitalWrite(MOTOR_IN2, HIGH);
      digitalWrite(MOTOR_IN3, HIGH); // Right Motor Forward
      digitalWrite(MOTOR_IN4, LOW);
      Serial.println("Turning Left");
    } else if (command == "R") { // Turn Right (Left motor forward, Right motor backward/stop)
      digitalWrite(MOTOR_IN1, HIGH); // Left Motor Forward
      digitalWrite(MOTOR_IN2, LOW);
      digitalWrite(MOTOR_IN3, LOW);  // Right Motor Reverse (pivot)
      digitalWrite(MOTOR_IN4, HIGH);
      Serial.println("Turning Right");
    } else if (command == "S") {
      digitalWrite(MOTOR_IN1, LOW);
      digitalWrite(MOTOR_IN2, LOW);
      digitalWrite(MOTOR_IN3, LOW);
      digitalWrite(MOTOR_IN4, LOW);
      // analogWrite(MOTOR_PWM, 0); // Optionally stop PWM completely
      Serial.println("Stopping Motors");
    }
  }
}