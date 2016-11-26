void setup() {
  Serial.begin(9600);
}

void loop() {
  muestreo();
}

void muestreo() {
  int a = analogRead(A0);
  float v = float(a) * 5 / 1023;

  Serial.print("Read: ");
  Serial.print(a);
  Serial.print(" V: ");
  Serial.println(v, 3);

  delay(1000);
}