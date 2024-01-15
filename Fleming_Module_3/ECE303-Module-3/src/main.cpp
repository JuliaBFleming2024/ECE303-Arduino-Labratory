#include <Arduino.h>
#include "DigitalPin.h"

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

int flag1 = 1;
int flag2 = 1;
int flag3 = 1;
int flag4 = 1;

volatile uint8_t* redPort = &PORTL;
uint8_t redBit = 3;

volatile uint8_t* yellowPort = &PORTB;
uint8_t yellowBit = 4;

volatile uint8_t* greenPort = &PORTH;
uint8_t greenBit = 3;

volatile uint8_t* bluePort = &PORTH;
uint8_t blueBit = 4;

DigitalPin redPin(redPort, redBit);
DigitalPin yellowPin(yellowPort, yellowBit);
DigitalPin greenPin(greenPort, greenBit);
DigitalPin bluePin(bluePort, blueBit);

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
unsigned long currentBaseDelay = 1000;

void setup() {
  Serial.begin(9600);
  redPin.off();
  yellowPin.off();
  greenPin.off();
  bluePin.off();
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
  redPin.on();
  yellowPin.on();
  greenPin.on();
  bluePin.on();
  while (1);
}

void loop() {
  unsigned long currentMillis = millis();

  if (attempts <= 0) {
    failed();
  }

  if (Serial.available() >= 4) {
    inputCode = Serial.parseInt();
    int input1 = inputCode / 1000 % 10;
    int input2 = inputCode / 100 % 10;
    int input3 = inputCode / 10 % 10;
    int input4 = inputCode % 10;

    if (flag1 == 1 && input1 == secret1) {
      flag1 = 0;
      redPin.off();
    }
    if (flag2 == 1 && input2 == secret2) {
      flag2 = 0;
      yellowPin.off();
    }
    if (flag3 == 1 && input3 == secret3) {
      flag3 = 0;
      greenPin.off();
    }
    if (flag4 == 1 && input4 == secret4) {
      flag4 = 0;
      bluePin.off();
    }

    if (flag1 == 0 && flag2 == 0 && flag3 == 0 && flag4 == 0) {
      Serial.println("SUCCESS");
      redPin.off();
      yellowPin.off();
      greenPin.off();
      bluePin.off();
      while (1);
    }

    attempts--;
    currentBaseDelay /= 2;
  }

  if (currentMillis - previousMillis >= currentBaseDelay) {
    previousMillis = currentMillis;
    
    if (flag1 == 1) {
      redPin.toggle();
    }
    if (flag2 == 1) {
      yellowPin.toggle();
    }
    if (flag3 == 1) {
      greenPin.toggle();
    }
    if (flag4 == 1) {
      bluePin.toggle();
    }
  }
}
