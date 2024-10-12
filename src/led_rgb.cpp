#include <Arduino.h>
#include "led_rgb.h"

const int pinRed = 18;  // Pin para el color Rojo
const int pinGreen = 19; // Pin para el color Verde
const int pinBlue = 21; // Pin para el color Azul

void configRGBLeds(){
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
}

void updateRGBLed(int red, int green, int blue) {
  
  red = constrain(red, 0, 255);
  green = constrain(green, 0, 255);
  blue = constrain(blue, 0, 255);

  digitalWrite(pinRed, red);
  digitalWrite(pinGreen, green);
  digitalWrite(pinBlue, blue);
}

void leds(){
  digitalWrite(pinRed, HIGH);
  digitalWrite(pinGreen, LOW);
  digitalWrite(pinBlue, LOW);
  delay(1000);

  // Encender LED verde
  digitalWrite(pinRed, LOW);
  digitalWrite(pinGreen, HIGH);
  digitalWrite(pinBlue, LOW);
  delay(1000);

  // Encender LED azul
  digitalWrite(pinRed, LOW);
  digitalWrite(pinGreen, LOW);
  digitalWrite(pinBlue, HIGH);
  delay(1000);

  // Encender todos los colores (blanco)
  digitalWrite(pinRed, HIGH);
  digitalWrite(pinGreen, HIGH);
  digitalWrite(pinBlue, HIGH);
  delay(1000);
}