#define TRIG_PIN 18
#define ECHO_PIN 19
#define DISTANCE_MIN_CM 0
#define DISTANCE_MAX_CM 30

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  long duration;
  float distanceCm;

  // Send trigger pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo pulse
  duration = pulseIn(ECHO_PIN, HIGH);

  // Convert time to distance
  distanceCm = (duration * 0.0343) / 2;

  // Print only if object is within 0–30 cm
  if (distanceCm >= DISTANCE_MIN_CM && distanceCm <= DISTANCE_MAX_CM) {
    Serial.print("🚨 Object in front at ");
    Serial.print(distanceCm);
    Serial.println(" cm");
  }

  delay(500);
}
