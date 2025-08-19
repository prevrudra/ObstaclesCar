// Arduino Uno Car with Ultrasonic Obstacle Avoidance
// Uses HC-SR04 ultrasonic sensor and L298N motor driver

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

// Distance threshold (in cm)
#define OBSTACLE_DIST 20

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

  Serial.begin(9600);
}

long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long duration = pulseIn(ECHO, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
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
  long distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > OBSTACLE_DIST) {
    moveForward();
  } else {
    stopMotors();
    delay(300);
    moveBackward();
    delay(500);
    stopMotors();
    delay(300);
    turnRight();
    delay(500);
    stopMotors();
    delay(300);
  }
}
