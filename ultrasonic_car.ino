// Arduino Uno Car with Ultrasonic Obstacle Avoidance
// Uses HC-SR04 ultrasonic sensor, L298N motor driver, and servo for sensor scanning

// Motor pins (L298N)
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define ENA 9  // PWM for left motors
#define ENB 10 // PWM for right motors

// Ultrasonic sensor pins
#define TRIG 6
#define ECHO 7

// Servo pin for ultrasonic sensor
#define SERVO_PIN 8

// Distance threshold (in cm)
#define OBSTACLE_DIST 20

#include <Servo.h>
Servo sensorServo;

// Servo angles for scanning
#define CENTER_ANGLE 90
#define LEFT_ANGLE 150
#define RIGHT_ANGLE 30

void setup() {
  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Ultrasonic sensor pins
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Servo setup
  sensorServo.attach(SERVO_PIN);
  sensorServo.write(CENTER_ANGLE);

  Serial.begin(9600);
}

long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long duration = pulseIn(ECHO, HIGH, 30000); // timeout for safety
  long distance = duration * 0.034 / 2;
  return distance;
}

long scanDirection(int angle) {
  sensorServo.write(angle);
  delay(400); // allow servo to reach position
  long d = getDistance();
  delay(100); // allow sensor to settle
  return d;
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void loop() {
  // Scan center, left, right
  long centerDist = scanDirection(CENTER_ANGLE);
  long leftDist = scanDirection(LEFT_ANGLE);
  long rightDist = scanDirection(RIGHT_ANGLE);

  Serial.print("Center: "); Serial.print(centerDist);
  Serial.print(" | Left: "); Serial.print(leftDist);
  Serial.print(" | Right: "); Serial.println(rightDist);

  if (centerDist > OBSTACLE_DIST) {
    moveForward();
  } else if (leftDist > OBSTACLE_DIST) {
    stopMotors();
    delay(200);
    turnLeft();
    delay(500);
    stopMotors();
    delay(200);
  } else if (rightDist > OBSTACLE_DIST) {
    stopMotors();
    delay(200);
    turnRight();
    delay(500);
    stopMotors();
    delay(200);
  } else {
    stopMotors();
    delay(200);
    moveBackward();
    delay(500);
    stopMotors();
    delay(200);
  }
}
