void setup() {
  Serial.begin(9600);
  pinMode (13, INPUT);
  pinMode (2, OUTPUT);

}

void loop() {
  delay(1000);
  if ( digitalRead(13) == LOW)
    {
      digitalWrite(2, HIGH);
      Serial.println(" FIRE DETECTED !!");
    }
  else 
    {
      digitalWrite(2, LOW);
      Serial.println(" NO FIRE DETECTED !! ");
  }

delay(1000);
}
