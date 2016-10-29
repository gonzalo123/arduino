int buzzPin = 8;

void setup() {
  pinMode(buzzPin, OUTPUT);
}

void loop() {
  digitalWrite(buzzPin, HIGH);
  delay(50);
  digitalWrite(buzzPin, LOW);
  delay(100);

}
