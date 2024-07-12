void setup() {
  // put your setup code here, to run once:
pinMode(2,OUTPUT);
pinMode(15,OUTPUT);
pinMode(4, OUTPUT);
pinMode(17,OUTPUT);
pinMode(18, OUTPUT);
pinMode(13, OUTPUT);
pinMode(14, OUTPUT);
pinMode(26, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(2, HIGH);
digitalWrite(15, HIGH);
digitalWrite(4, HIGH);
digitalWrite(17, HIGH);
digitalWrite(18, HIGH);
digitalWrite(13, LOW);
digitalWrite(14, LOW);
digitalWrite(26, LOW);
delay(1000);
digitalWrite(2, LOW);
digitalWrite(15, LOW);
digitalWrite(4, LOW);
digitalWrite(17, LOW);
digitalWrite(18, LOW);
digitalWrite(13, HIGH);
digitalWrite(14, HIGH);
digitalWrite(26, HIGH);
delay(1000);
}
