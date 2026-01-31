#include <Servo.h>

Servo servo;

// Ultrasonic Sensor Pins
const int trigPin = 13;
const int echoPin = 12;

// Servo Pin
const int servoPin = 11;

// L298N Motor Driver Pins
const int enAPin = 6, in1Pin = 7, in2Pin = 5;  // Left motor
const int in3Pin = 4, in4Pin = 2, enBPin = 3;  // Right motor

enum Motor { LEFT, RIGHT };

// Sweep Configuration
const byte NUM_ANGLES = 7;
const byte sensorAngles[NUM_ANGLES] = {60, 70, 80, 90, 100, 110, 120};
unsigned int distanceArr[NUM_ANGLES];

// Movement function
void go(Motor m, int speed) {
  bool forward = speed > 0;
  int pwm = abs(speed);

  if (m == LEFT) {
    digitalWrite(in1Pin, forward);
    digitalWrite(in2Pin, !forward);
    analogWrite(enAPin, pwm);
  } else {
    digitalWrite(in3Pin, forward);
    digitalWrite(in4Pin, !forward);
    analogWrite(enBPin, pwm);
  }
}

// Motor Test Routine
void testMotors() {
  int speeds[] = {128, 255, 128, 0, -128, -255, -128, 0};

  for (int speed : speeds) {
    go(LEFT, speed);
    go(RIGHT, 0);
    delay(200);
  }
  for (int speed : speeds) {
    go(LEFT, 0);
    go(RIGHT, speed);
    delay(200);
  }
}

// Ultrasonic Read Function (in mm)
unsigned int readDistance() {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long duration = pulseIn(echoPin, HIGH, 30000);
  return duration == 0 ? 4000 : (duration * 343) / 2000;
}

// Sweep Distance Collection
void readNextDistance() {
  static byte angleIndex = 0;
  static int8_t step = 1;

  distanceArr[angleIndex] = readDistance();
  angleIndex += step;

  if (angleIndex == NUM_ANGLES - 1) step = -1;
  else if (angleIndex == 0) step = 1;

  servo.write(sensorAngles[angleIndex]);
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);

  pinMode(enAPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  pinMode(enBPin, OUTPUT);

  servo.attach(servoPin);
  servo.write(90);
  delay(300);

  go(LEFT, 0);
  go(RIGHT, 0);

  testMotors();

  // Initial sweep
  servo.write(sensorAngles[0]);
  delay(200);
  for (byte i = 0; i < NUM_ANGLES; i++) {
    readNextDistance();
    delay(150);
  }
}

void loop() {
  readNextDistance();

  // Detect obstacle within 30 cm
  bool tooClose = false;
  for (unsigned int d : distanceArr) {
    if (d < 300) {
      tooClose = true;
      break;
    }
  }

  if (tooClose) {
    go(LEFT, -180);
    go(RIGHT, -100);
  } else {
    go(LEFT, 255);
    go(RIGHT, 255);
  }

  delay(50);
}
