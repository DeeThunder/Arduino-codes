#include <BluetoothSerial.h> // Include the Bluetooth Serial library

// Define Motor Control Pins for a single L298N Driver
// Two motors (e.g., Front Left and Rear Left) connected in parallel to L298N's Left Channel (OUT1/OUT2)
// Two motors (e.g., Front Right and Rear Right) connected in parallel to L298N's Right Channel (OUT3/OUT4)

#define MOTOR_IN1 15   // L298N IN1 -> Controls direction for Left Side motors (Front Left + Rear Left)
#define MOTOR_IN2 4   // L298N IN2 -> Controls direction for Left Side motors (Front Left + Rear Left)
#define MOTOR_ENA 5  // L298N ENA -> PWM pin for Left Side speed control (Connect to ENA on L298N)

#define MOTOR_IN3 19  // L298N IN3 -> Controls direction for Right Side motors (Front Right + Rear Right)
#define MOTOR_IN4 23  // L298N IN4 -> Controls direction for Right Side motors (Front Right + Rear Right)
#define MOTOR_ENB 25  // L298N ENB -> PWM pin for Right Side speed control (Matches your original MOTOR_PWM, connect to ENB on L298N)

// Initialize Bluetooth Serial
BluetoothSerial SerialBT;

// Global variable for motor speed (0-255)
int motorSpeed = 150; // Default speed

// Function to set both motor channels (Left and Right) of the single L298N
void setAllMotorChannelsState(int leftDir1, int leftDir2, int rightDir1, int rightDir2, int speed) {
  // Set directions for Left Side motors (connected to OUT1/OUT2)
  digitalWrite(MOTOR_IN1, leftDir1);
  digitalWrite(MOTOR_IN2, leftDir2);

  // Set directions for Right Side motors (connected to OUT3/OUT4)
  digitalWrite(MOTOR_IN3, rightDir1);
  digitalWrite(MOTOR_IN4, rightDir2);

  // Apply speed to both channels
  analogWrite(MOTOR_ENA, speed);
  analogWrite(MOTOR_ENB, speed);
}

void setup() {
  Serial.begin(115200); // Initialize USB Serial for debugging output
  Serial.println("Starting 4-Motor Control with Single L298N Sketch...");

  // Initialize Bluetooth Serial
  SerialBT.begin("ESP32_RC_Car_4x4"); // Give your ESP32 a recognizable Bluetooth name
  Serial.println("Bluetooth Started! Ready to pair.");

  // Set motor control pins as outputs
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_ENA, OUTPUT); // ENA is now a dedicated PWM output
  pinMode(MOTOR_IN3, OUTPUT);
  pinMode(MOTOR_IN4, OUTPUT);
  pinMode(MOTOR_ENB, OUTPUT); // ENB is now a dedicated PWM output

  // Start with motors stopped (direction inputs LOW, speed 0)
  setAllMotorChannelsState(LOW, LOW, LOW, LOW, 0);
  Serial.print("Initial motorSpeed set to: ");
  Serial.println(motorSpeed);
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
    // "F" -> Forward (All 4 motors)
    // "B" -> Backward (All 4 motors)
    // "L" -> Turn Left (Left side motors backward, Right side motors forward - Pivot)
    // "R" -> Turn Right (Left side motors forward, Right side motors backward - Pivot)
    // "S" -> Stop (All 4 motors)
    // "VXXX" -> Set Speed (e.g., "V150" for speed 150)

    if (command.startsWith("V")) {
      int receivedSpeed = command.substring(1).toInt(); // Extract number after 'V'
      motorSpeed = constrain(receivedSpeed, 0, 255); // Limit speed to 0-255
      Serial.print("Desired BT Speed: ");
      Serial.println(motorSpeed);
      analogWrite(MOTOR_ENA, motorSpeed); // Apply new speed to Left Channel
      analogWrite(MOTOR_ENB, motorSpeed); // Apply new speed to Right Channel
      Serial.print("Set Speed: ");
      Serial.println(motorSpeed);
    } else if (command == "F") {
      setAllMotorChannelsState(HIGH, LOW, HIGH, LOW, motorSpeed); // All motors Forward
      Serial.println("Moving All Forward");
    } else if (command == "B") {
      setAllMotorChannelsState(LOW, HIGH, LOW, HIGH, motorSpeed); // All motors Backward
      Serial.println("Moving All Backward");
    } else if (command == "L") { // Pivot Left (Right side forward, Left side backward)
      setAllMotorChannelsState(LOW, HIGH, HIGH, LOW, motorSpeed);
      Serial.println("Turning Left (Pivot)");
    } else if (command == "R") { // Pivot Right (Left side forward, Right side backward)
      setAllMotorChannelsState(HIGH, LOW, LOW, HIGH, motorSpeed);
      Serial.println("Turning Right (Pivot)");
    } else if (command == "S") {
      setAllMotorChannelsState(LOW, LOW, LOW, LOW, 0); // Stop all motors
      Serial.println("Stopping All Motors");
    } else {
      Serial.println("Unknown command received.");
    }
  }
}