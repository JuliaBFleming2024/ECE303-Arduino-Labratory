#ifndef DigitalPin_h
#define DigitalPin_h

#include <Arduino.h>

class DigitalPin {
public:
  DigitalPin(byte pin);
  void setPinMode(byte mode);
  void setICR(uint16_t value); 
  void setDutyCycle(uint8_t percent);
  int read();
  void write(int value);

private:
  byte pinNumber;
};

#endif
