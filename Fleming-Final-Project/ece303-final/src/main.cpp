#include <Arduino.h>
#include <SPI.h>

const int trigPin = 11;
const int echoPin = 12;
const int motorEnablePin = 4;
const int motorDirectionPin = 3;
const int temperatureSensorPin = A0;
const int waterLevelSensorPin = 7;
const int greenLEDPin = 5;
const int yellowLEDPin = 6;
const int redLEDPin = 8;

const int initialAngle = 90;
const int angleStep = 5;
const int maxAngle = 180;

int unsuccessfulAttempts = 0;
int count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorEnablePin, OUTPUT);
  pinMode(motorDirectionPin, OUTPUT);
  pinMode(temperatureSensorPin, INPUT);
  pinMode(waterLevelSensorPin, INPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  Serial.println("System startup...");
  while (count < 5) {
    Serial.println("Show Key");
    delay(1000);
    count++;
  }
}

int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

float readTemperature() {
  int sensorValue = analogRead(temperatureSensorPin);
  float temperature = (sensorValue * 0.48876);
  return temperature;
}

int readWaterLevel() {
  return digitalRead(waterLevelSensorPin);
}

void unlockSystem() {
  Serial.println("System unlocked!");
}

void updateLEDs(bool systemLocked) {
  digitalWrite(greenLEDPin, systemLocked ? HIGH : LOW);
  digitalWrite(yellowLEDPin, HIGH);
  float temperature = readTemperature();
  int waterLevel = readWaterLevel();
  digitalWrite(redLEDPin, (temperature > 40.0 || waterLevel == LOW) ? HIGH : LOW);
}

void loop() {
  bool isRFIDCardPresent = true;

  if (isRFIDCardPresent) {
    Serial.println("RFID Card detected. System unlocked!");
    unlockSystem();
    unsuccessfulAttempts = 0;
  } else {
    Serial.println("Place RFID Card to unlock the system.");
    delay(500);
    unsuccessfulAttempts++;
  }

  float temperature = readTemperature();
  int waterLevel = readWaterLevel();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °F");

  Serial.print("Water Level: ");
  Serial.println((waterLevel == LOW) ? "Water detected" : "No water");

  updateLEDs(!isRFIDCardPresent);

  Serial.println("Angle,Distance");
  for (int angle = initialAngle; angle <= maxAngle; angle += angleStep) {
    int distance = getDistance(trigPin, echoPin);
    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);

    if (distance < 10) {
      digitalWrite(motorEnablePin, LOW);
      digitalWrite(redLEDPin, HIGH);
      digitalWrite(yellowLEDPin, LOW);
      digitalWrite(greenLEDPin, LOW);
    }
    if (distance < 20) {
      digitalWrite(motorEnablePin, HIGH);
      analogWrite(motorEnablePin, 75);
      digitalWrite(redLEDPin, HIGH);
      digitalWrite(yellowLEDPin, LOW);
      digitalWrite(greenLEDPin, LOW);
    }
     else {
      analogWrite(motorEnablePin, 150);
      digitalWrite(redLEDPin, LOW);
      digitalWrite(yellowLEDPin, LOW);
      digitalWrite(greenLEDPin, HIGH);
    }

    delay(500);
  }
  digitalWrite(motorEnablePin, LOW);
}
