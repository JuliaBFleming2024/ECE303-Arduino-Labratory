#ifndef LED_h
#define LED_h

class LED {
public:
  LED(int pin);        // constructor
  void turnOn();       // function to call turn off led 
  void turnOff();      // function to call turn off led 
// void setIntensity(int intensity); 
  void blink(int times, int onDuration, int offDuration); // function to set blink duration and speeds
private:
  int pinNumber;     // store pin 
};

#endif // LED_h
