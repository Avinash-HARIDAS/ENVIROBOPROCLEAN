#include <Servo.h>
void waste();
void ultrasonic();
Servo servo1;
Servo servo2;
Servo servo3;
const int IN1 = 7;
const int IN2 = 6;
const int IN3 = 5;
const int IN4 = 4;
int led=A1;
#define trigPin 2
#define echoPin 3
#define trig 9
#define echo 8

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  servo1.attach(A0);
  servo2.attach(0);
  servo3.attach(1);
}
void loop() {
   servo1.write(0);
    servo2.write(0);
    servo3.write(0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(10);
    servo1.write(180);
    servo2.write(180);
    servo3.write(180);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(10);
    ultrasonic();
    waste();
}
void waste() {
  float duration, distance;
  //distance=velocity*time
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the pulse on the echoPin
  duration = pulseIn(echoPin, HIGH);
  //distance=velocity*time
  //velocity of ulrasound 340 in air m/s *10^2for convert to cm/s
  //time=duration/2 *10^6 (microsecond to second)*velocity
  // Calculate the distance in centimeters
  distance = (duration / 2) *0.034;

  // Display the distance on the Serial Monitor
  if (distance < 20) {
    Serial.print("Storage full: ");
    digitalWrite(led, HIGH);
    Serial.print(distance);
    Serial.println(" cm");
    delay(500);
  }
}
void ultrasonic()
{
  Serial.print("no obstacle ");
}
