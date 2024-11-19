/**
 * @file 01_DigitalWrite_Example.ino
 *
 * Description: This program demonstrates controlling an LED using a button.
 * When the button is pressed, the LED turns on. Otherwise, it remains off.
 *
 */

#include <Arduino.h> 

#define LED_PIN 4      // Define the pin connected to the LED.
#define BUTTON_PIN 5   // Define the pin connected to the button.

void setup() {
  pinMode(LED_PIN, OUTPUT);  // Set LED pin as output to control the LED.
  pinMode(BUTTON_PIN, INPUT); // Set button pin as input to read its state.
}

void loop() {
  if (!digitalRead(BUTTON_PIN)) {  // Check if the button is pressed (LOW state).
    digitalWrite(LED_PIN, HIGH);  // Turn the LED on if the button is pressed.
  }
  else {
    digitalWrite(LED_PIN, LOW);  // Turn the LED off if the button is not pressed
  }
}
