#include <Arduino.h>

int redLED = 44;
int yellowLED = 12;
int greenLED = 6;
int blueLED = 5;

int secret1;
int secret2;
int secret3;
int secret4;


int attempts = 5;
int inputCode;

int flag1 = 1;  // initally unguesed 
int flag2 = 1;
int flag3 = 1;
int flag4 = 1;

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
unsigned long currentBaseDelay = 1000;  // Initial delay 1000 ms

void setup() {
  Serial.begin(9600);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);

  // Generate a random code
  randomSeed(analogRead(0));
  secret1 = random(0, 10);
  secret2 = random(0, 10);
  secret3 = random(0, 10);
  secret4 = random(0, 10);

  Serial.print("The secret code is ");
  Serial.print(secret1);
  Serial.print(secret2);
  Serial.print(secret3);
  Serial.println(secret4);
}

void failed() {
  Serial.println("FAIL");
  digitalWrite(redLED, HIGH);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(greenLED, HIGH);
  digitalWrite(blueLED, HIGH);
  while (1);
}

void loop() {
  unsigned long currentMillis = millis();

  if (attempts <= 0) {
    failed();
  }

  if (Serial.available() >= 4) {
    inputCode = Serial.parseInt();
    int input1 = inputCode / 1000 % 10; // get digit 1 
    int input2 = inputCode / 100 % 10; 
    int input3 = inputCode / 10 % 10;
    int input4 = inputCode % 10;

    if (flag1 == 1 && input1 == secret1) {
      flag1 = 0;
      digitalWrite(redLED, LOW);
    }
    if (flag2 == 1 && input2 == secret2) {
      flag2 = 0;
      digitalWrite(yellowLED, LOW);
    }
    if (flag3 == 1 && input3 == secret3) {
      flag3 = 0;
      digitalWrite(greenLED, LOW);
    }
    if (flag4 == 1 && input4 == secret4) {
      flag4 = 0;
      digitalWrite(blueLED, LOW);
    }

    if (flag1 == 0 && flag2 == 0 && flag3 == 0 && flag4 == 0) {
      Serial.println("SUCCESS");
      digitalWrite(redLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(greenLED, LOW);
      digitalWrite(blueLED, LOW);
      while (1);
    }

    attempts--;
    currentBaseDelay /= 2;  // Halve the delay
  }

  if (currentMillis - previousMillis >= currentBaseDelay) {
    previousMillis = currentMillis;
    
    if (flag1 == 1) {
      digitalWrite(redLED, !digitalRead(redLED));
    }
    if (flag2 == 1) {
      digitalWrite(yellowLED, !digitalRead(yellowLED));
    }
    if (flag3 == 1) {
      digitalWrite(greenLED, !digitalRead(greenLED));
    }
    if (flag4 == 1) {
      digitalWrite(blueLED, !digitalRead(blueLED));
    }
  }
}
