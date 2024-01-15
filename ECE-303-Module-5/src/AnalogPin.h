#ifndef AnalogPin_h
#define AnalogPin_h

#include <Arduino.h>

class AnalogPin {
public:
  AnalogPin(byte pin);
  int read();

private:
  byte pinNumber;
};

#endif
