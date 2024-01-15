#include <Arduino.h>

// Ultrasonic sensor pins
#define TRIG_PIN 2
#define ECHO_PIN 3

// DC motor pins
#define MOTOR_PWM_PIN 9
#define MOTOR_IN1_PIN 10
#define MOTOR_IN2_PIN 11

// LEDs pins
#define LED1_PIN 6  // Red LED
#define LED2_PIN 5  // Yellow LED
#define LED3_PIN 7  // Green LED

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  pinMode(MOTOR_IN1_PIN, OUTPUT);
  pinMode(MOTOR_IN2_PIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
}

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  float duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration * 0.0343) / 2;

  return distance;
}

void controlMotor(float distance) {
  if (distance > 30) {
    analogWrite(MOTOR_PWM_PIN, 255);  // Full speed
    digitalWrite(MOTOR_IN1_PIN, HIGH);
    digitalWrite(MOTOR_IN2_PIN, LOW);
  } else if (distance >= 10 && distance <= 30) {
    int speed = map(distance, 10, 30, 128, 255);
    analogWrite(MOTOR_PWM_PIN, speed);  // Adjust speed based on distance
    digitalWrite(MOTOR_IN1_PIN, HIGH);
    digitalWrite(MOTOR_IN2_PIN, LOW);
  } else {
    analogWrite(MOTOR_PWM_PIN, 0);  // Stop the motor
    digitalWrite(MOTOR_IN1_PIN, LOW);
    digitalWrite(MOTOR_IN2_PIN, LOW);
  }
}

void controlLEDs(float distance) {
  if (distance > 30) {
    digitalWrite(LED1_PIN, LOW);  // Red LED off
    digitalWrite(LED2_PIN, LOW);  // Yellow LED off
    digitalWrite(LED3_PIN, LOW);  // Green LED off
  } else if (distance >= 20 && distance <= 30) {
    digitalWrite(LED1_PIN, HIGH);  // Red LED on
    digitalWrite(LED2_PIN, LOW);   // Yellow LED off
    digitalWrite(LED3_PIN, LOW);   // Green LED off
  } else if (distance >= 10 && distance < 20) {
    digitalWrite(LED1_PIN, HIGH);  // Red LED on
    digitalWrite(LED2_PIN, HIGH);  // Yellow LED on
    digitalWrite(LED3_PIN, LOW);   // Green LED off
  } else {
    digitalWrite(LED1_PIN, HIGH);  // Red LED on
    digitalWrite(LED2_PIN, HIGH);  // Yellow LED on
    digitalWrite(LED3_PIN, HIGH);  // Green LED on
  }
}

void loop() {
  float distance = getDistance();

  controlMotor(distance);
  controlLEDs(distance);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(1000);
}
