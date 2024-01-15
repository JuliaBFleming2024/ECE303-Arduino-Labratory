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
    float photocellResistance;

    if (photocellCurrent != 0) {
      photocellResistance = photocellVoltage / photocellCurrent;
    } else {
      photocellResistance = 0.0; // Handle the case where photocellCurrent is zero
    }

    float photocellResistanceVsLEDCurrent;

    if (ledCurrent != 0) {
      photocellResistanceVsLEDCurrent = photocellResistance / ledCurrent;
    } else {
      photocellResistanceVsLEDCurrent = 0.0; // Handle the case where ledCurrent is zero
    }

    //  the values to be plotted
    Serial.print(dutyCycle);
    Serial.print(",");
    Serial.print(ledCurrent);
    Serial.print(",");
    Serial.print(ledResistance);
    Serial.print(",");
    Serial.print(photocellCurrent);
    Serial.print(",");
    Serial.print(photocellResistance);
    Serial.print(",");
    Serial.println(photocellResistanceVsLEDCurrent);

    delay(200);

    counter++;
  }
}
