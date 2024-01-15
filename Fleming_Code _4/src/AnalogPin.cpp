#include "AnalogPin.h"

AnalogPin::AnalogPin(byte pin) {
  pinNumber = pin;
}

int AnalogPin::read() {
  return analogRead(pinNumber);
}
