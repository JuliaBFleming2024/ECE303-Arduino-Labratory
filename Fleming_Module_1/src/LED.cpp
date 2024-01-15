#include <Arduino.h>
#include "LED.h"

LED::LED(int pin) {
  pinNumber = pin;
  pinMode(pinNumber, OUTPUT); //initializing the LED in the class 
}

void LED::turnOn() {
  digitalWrite(pinNumber, HIGH); // turns LED HIGH when passes pinNumber by calling turnOn()
}

void LED::turnOff() {
  digitalWrite(pinNumber, LOW); // turns LED LOW  when passes pinNumber 
}

//void LED::setIntensity(int intensity) {
//  analogWrite(pinNumber, intensity); 
//}

void LED::blink(int times, int onDuration, int offDuration) { // defines blinking function 
  for (int i = 0; i < times; i++) { //makes sure dont excede the count paramarater 
    turnOn();  // use defined on function 
    delay(onDuration);   // keep on based on input 4th input parameter 
    turnOff();  // use defined off function 
    delay(offDuration); // keep off based on input 5th input parameter 
  }
}
