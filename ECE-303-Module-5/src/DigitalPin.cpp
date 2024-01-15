#include "DigitalPin.h"

DigitalPin::DigitalPin(byte pin) {
  pinNumber = pin;
  pinMode(pinNumber, INPUT);
}

void DigitalPin::setPinMode(byte mode) {
  pinMode(pinNumber, mode);
}

void DigitalPin::setDutyCycle(uint8_t percent) {
  uint16_t dutyCycleValue = (percent * ICR1) / 100;
  OCR1A = dutyCycleValue;
}

int DigitalPin::read() {
  return digitalRead(pinNumber);
}

void DigitalPin::write(int value) {
  digitalWrite(pinNumber, value);
}
