#ifndef DigitalPin_h
#define DigitalPin_h

class DigitalPin {
public:
  DigitalPin(volatile uint8_t* port, uint8_t bit);
  void on();
  void off();
  void toggle();
  
private:
  volatile uint8_t* portRegister;
  uint8_t bitNumber;
};

#endif
