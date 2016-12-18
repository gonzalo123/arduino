#include <Servo.h>
Servo miServo;
int trigPin = 7;
int echoPin = 6;
long duration, distance_cm;

void setup() {
  Serial.begin(9600);
  miServo.attach(9);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}
int value = 50;
void loop() {
  value = value + 10;
  Serial.println("move");
  miServo.write(value);
  
  delay(2000);
  Serial.println("detect");
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH) / 2;
  distance_cm = duration / 29;

  Serial.print("Position: ");
  Serial.print(value);
  Serial.print(" cm ");
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm ");
  
  if (value >= 180) {
    value = 50;
  }
  delay(500);
}
