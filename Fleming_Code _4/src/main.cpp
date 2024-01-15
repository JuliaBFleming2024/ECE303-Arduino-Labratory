#include <Arduino.h>
#include <AnalogPin.h>
#include <DigitalPin.h>

int ledPin = 8;
unsigned int counter = 0;
int val1 = 0;
AnalogPin photocell(A0);
DigitalPin ledControlPin(ledPin);

void adc_init() {
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  ADMUX |= (1 << REFS0);
  ADCSRA |= (1 << ADEN);
  ADCSRA |= (1 << ADSC);
}

void setup() {
  Serial.begin(9600);
  ledControlPin.setPinMode(OUTPUT);
  adc_init();
}

float measureLEDCurrent() {
  int ledCurrentReading = analogRead(A0); // Read current sensor on A0
  float ledCurrent_mA = ledCurrentReading * 5.0 / 1023.0; // Convert to mA
  return ledCurrent_mA;
}

float measurePhotocellCurrent() {
  int photocellCurrentReading = analogRead(A0); // Read current sensor on A0
  float photocellCurrent_mA = photocellCurrentReading * 5.0 / 1023.0; // Convert to mA 
}


void loop() {
  if (counter <= 20) {
    int dutyCycle = 5 + counter * 5; 

    analogWrite(ledPin, (dutyCycle * 255) / 100); 

    delay(2000); 
    val1 = photocell.read(); 

    // Calculate LED current (mA)
    float ledCurrent = measureLEDCurrent(); 

    // Calculate LED resistance (Ohms)
    float ledVoltage = (dutyCycle / 100.0) * 5.0;
    float ledResistance = ledVoltage / ledCurrent;

    // Calculate photocell current (mA)
    float photocellCurrent = measurePhotocellCurrent();

    // Calculate photocell resistance (Ohms)
    float photocellVoltage = 5.0 - (val1 * 5.0 / 1023.0);
    float photocellResistance = photocellVoltage / photocellCurrent;

    float photocellResistanceVsLEDCurrent = photocellResistance / ledCurrent;

    //Serial.print("Duty Cycle (%): ");
    Serial.print(dutyCycle);
    //Serial.print(", LED Current (mA): ");
    //Serial.print(ledCurrent);
    //Serial.print(", LED Resistance (Ohms): ");
    //Serial.print(ledResistance);
    Serial.print(" ");
    //Serial.print(", Photocell Current (mA): ");
    //Serial.print(photocellCurrent);
    //Serial.print(", Photocell Resistance (Ohms): ");
    //Serial.print(photocellResistance);
    //Serial.print(",  LED  Voltage ");
    //Serial.println(ledvoltage);
    //Serial.print(",  Photocell  Voltage ");
    //Serial.println(photovolts);

    counter++;
  }
}
