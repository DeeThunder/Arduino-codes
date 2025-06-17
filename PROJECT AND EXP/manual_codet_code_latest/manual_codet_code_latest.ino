#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>

// LCD Setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// GPS Setup (Serial1)
HardwareSerial gpsSerial(1); // UART1
TinyGPSPlus gps;

// GSM Setup (Serial2)
HardwareSerial gsmSerial(2); // UART2

// Pin Definitions
#define VIBRATION_PIN 34
#define MQ2_AO_PIN 35
#define TRIG_PIN 23
#define ECHO_PIN 5
#define STOP_SIGNAL_PIN 25

// LED Pins
#define BLUE_LED_PIN 12   // Obstacle Detected
#define RED_LED_PIN 4     // Accident Detected
#define GREEN_LED_PIN 18  // Normal

// I2C Pins (default for ESP32)
#define I2C_SDA 21
#define I2C_SCL 22

// Thresholds
#define GAS_THRESHOLD 1500
#define DISTANCE_THRESHOLD_CM 35
#define VIBRATION_DEBOUNCE_COUNT 5  // For false alarm reduction

// Variables
bool accidentDetected = false;
int vibrationCount = 0;

void setup() {
  Serial.begin(115200);

  // LCD
  Wire.begin(I2C_SDA, I2C_SCL);
  lcd.init();
  lcd.backlight();
  lcd.print("System Starting...");
  Serial.println("System Starting...");

  // Pin Modes
  pinMode(VIBRATION_PIN, INPUT);
  pinMode(MQ2_AO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(STOP_SIGNAL_PIN, OUTPUT);

  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  // GPS & GSM
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);  // GPS
  gsmSerial.begin(9600, SERIAL_8N1, 26, 27);  // GSM

  delay(2000);
  lcd.clear();
  lcd.print("System Ready");
  Serial.println("System Ready");
}

void loop() {
  // Read sensors
  int vibration = digitalRead(VIBRATION_PIN);
  int gasLevel = analogRead(MQ2_AO_PIN);
  float distance = readUltrasonic();

  // Process GPS data
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  // Obstacle detection
  bool obstacleDetected = false;
  if (distance > 0 && distance < DISTANCE_THRESHOLD_CM) {
    digitalWrite(STOP_SIGNAL_PIN, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Obstacle <35cm ");
    Serial.println("Obstacle detected: Object < 35cm");
    obstacleDetected = true;
  } else {
    digitalWrite(STOP_SIGNAL_PIN, LOW);
  }

  // Gas detection
  bool gasLeak = gasLevel > GAS_THRESHOLD;

  // Debounce vibration signal
  if (vibration == HIGH) {
    vibrationCount++;
  } else {
    if (vibrationCount > 0) vibrationCount--;
  }

  // If vibration strong enough, trigger accident
  if (vibrationCount >= VIBRATION_DEBOUNCE_COUNT && !accidentDetected) {
    accidentDetected = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Accident!");
    lcd.setCursor(0, 1);
    lcd.print("Sending Alert...");
    Serial.println("Accident detected! Sending SMS alert...");
    sendSMS();
  }

  // LCD Gas status display
  lcd.setCursor(0, 0);
  if (gasLeak) {
    lcd.print("Gas Leak!    ");
    Serial.println("Gas Leak Detected!");
  } else {
    lcd.print("Gas OK       ");
    Serial.println("Gas Level Normal.");
  }

  // LED Logic - live update
  if (accidentDetected) {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
  } else if (obstacleDetected) {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
  } else if (!gasLeak) {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
  } else {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
  }

  delay(500);  // Faster refresh
}

void sendSMS() {
  String location = "Unknown";
  if (gps.location.isValid()) {
    location = "Lat: " + String(gps.location.lat(), 6) + ", Lng: " + String(gps.location.lng(), 6);
  }

  gsmSerial.println("AT");
  delay(1000);
  gsmSerial.println("AT+CMGF=1");
  delay(1000);
  gsmSerial.println("AT+CMGS=\"+2349072480621\"");
  delay(1000);
  gsmSerial.print("\xF0\x9F\x9A\xA8 Accident Detected!\n");
  gsmSerial.print("Location: ");
  gsmSerial.print(location);
  gsmSerial.write(26); // End of SMS
  delay(5000);

  Serial.print("SMS Sent with Location: ");
  Serial.println(location);
}

float readUltrasonic() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  return (duration * 0.0343) / 2.0;
}
