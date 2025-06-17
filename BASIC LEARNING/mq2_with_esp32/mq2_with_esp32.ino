#define MQ2_AO_PIN 36  // Analog output pin from MQ-2 to GPIO36 (VP)
#define GAS_THRESHOLD 1700  // Adjust this value based on calibration

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);  // ESP32 default is 12-bit ADC (0–4095)
  Serial.println("MQ-2 Gas/Smoke Level Monitor");
}

void loop() {
  int analogValue = analogRead(MQ2_AO_PIN);
  float voltage = analogValue * (3.3 / 4095.0);

  Serial.print("Analog Value: ");
  Serial.print(analogValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2);
  Serial.print(" V");

  if (analogValue > GAS_THRESHOLD) {
    Serial.println(" 🚨 Gas/Smoke Detected!");
  } else {
    Serial.println(" ✅ Air is Clean");
  }

  delay(1000);
}
