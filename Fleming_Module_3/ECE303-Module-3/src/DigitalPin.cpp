#include "Arduino.h"
#include "DigitalPin.h"

DigitalPin::DigitalPin(volatile uint8_t* port, uint8_t bit) {
  portRegister = port;
  bitNumber = bit;
  *portRegister |= (1 << bitNumber);
}

void DigitalPin::on() {
  *portRegister |= (1 << bitNumber);
}

void DigitalPin::off() {
  *portRegister &= ~(1 << bitNumber);
}

void DigitalPin::toggle() {
  *portRegister ^= (1 << bitNumber);
}
