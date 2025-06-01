#include <Servo.h>

// Pin definitions
const int trigPin = 7;
const int echoPin = 6;
const int servoPin = 3;

Servo gateServo;

long duration;
int distance;
int currentPos = -1;  // Unknown at start

// Threshold for car detection (adjust as needed)
const int carDistanceThreshold = 15;  // cm

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Trigger ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // Convert to cm

  Serial.print("Distance: ");
  Serial.println(distance);

  // Car detected: open gate
  if (distance > 0 && distance <= carDistanceThreshold && currentPos != 90) {
    gateServo.attach(servoPin);
    gateServo.write(90);
    delay(500);         // Allow movement
    gateServo.detach();
    delay(5000);
    currentPos = 90;
  }

  // No car: close gate
  else if ((distance > carDistanceThreshold || distance == 0) && currentPos != 0) {
    gateServo.attach(servoPin);
    gateServo.write(0);
    delay(500);
    gateServo.detach();
    currentPos = 0;
  }

  delay(200);  // Slow down loop
}
