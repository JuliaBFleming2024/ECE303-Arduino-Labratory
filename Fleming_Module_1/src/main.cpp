#include <Arduino.h>
#include "LED.h" // My created library

int redPin = 8;   // Storing pin 8 in redPin to set as an output pin
int yellowPin = 9; // Maps the rest of the LED colors to selected pins
int bluePin = 10;
int greenPin = 11;

LED redLED(redPin);       // Create an instance of the LED class for the red LED
LED yellowLED(yellowPin);
LED blueLED(bluePin);
LED greenLED(greenPin);

LED* activeLED = nullptr; // activeLED is a pointer used to track the current LED state, begins off

void setup() {
  Serial.begin(9600);    // Sets up the serial monitor at 9600 baud

  pinMode(redPin, OUTPUT);    // Set each pin variable as an output
  pinMode(yellowPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) { // While there's input entered
    String command = Serial.readStringUntil('\n'); // Store input as command
    command.trim(); // Remove input whitespace

    int commaIndex = command.indexOf(','); // Find the location of the commas, if any

    if (commaIndex != -1) { // If there's a comma, and theres stuff after it
      String ledColor = command.substring(0, commaIndex); // Store anything before that comma as ledColor
      String action = command.substring(commaIndex + 1); // Store the info after the second comma as the action (on/off/blink)

      if (activeLED != nullptr)
      {
        activeLED->turnOff(); // If we receive a new action, turn off the last LED
        activeLED = nullptr; // Clear the activeLED to prepare for the next assignment
      }

      if (ledColor.equalsIgnoreCase("red"))
      {
        activeLED = &redLED;
      }
      else if (ledColor.equalsIgnoreCase("yellow"))
      {
        activeLED = &yellowLED;
      }
      else if (ledColor.equalsIgnoreCase("blue"))
      {
        activeLED = &blueLED;
      }
      else if (ledColor.equalsIgnoreCase("green"))
      {
        activeLED = &greenLED;
      }

      if (activeLED != nullptr) {
        if (action.equalsIgnoreCase("on"))
        {
          activeLED->turnOn(); }
        else if (action.equalsIgnoreCase("off"))
        {
          activeLED->turnOff();}
        else if (action.equalsIgnoreCase("blink"))
        {  // only if blink do we check last parameters
          char* token =  strtok(const_cast<char*>(action.c_str()), ",");
          int times = atoi(token); // Pass the third parameter as the number of times to blink the LED
          token = strtok(NULL,","); // seperate the string by its commas
          int onDuration =  atoi(token); // Pass the fourth parameter as the on duration for each blink
          token = strtok(NULL,",");
          int offDuration = atoi(token); // Pass the fifth parameter as the off duration for each blink
          activeLED->blink(times, onDuration, offDuration);
        }

      }
    }
  }
}

