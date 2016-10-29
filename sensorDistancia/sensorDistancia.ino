int trigPin = 13;
int echoPin = 12;
int redPin = 8;
int alert = 0;
int alertThreshold = 50;
long duration, distance_cm;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH) / 2;
  distance_cm = duration / 29;

  if (distance_cm <= alertThreshold && alert == 0) {
      alert = 1;
      Serial.println("Alert!");
      digitalWrite(redPin, HIGH);
  } else if(distance_cm > alertThreshold && alert == 1) {
    alert = 0;
    Serial.println("No alert");
    digitalWrite(redPin, LOW);
  }

  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm ");

  delay(500);
}

