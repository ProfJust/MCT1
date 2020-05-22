//https://www.arduino-tutorial.de/arduino-a4988-nema17/
// Funktioniert mit 10V , 1,5A

#include <Arduino.h>
#define X_STEP_PIN         54
#define X_DIR_PIN          55   //tested
#define X_ENABLE_PIN       38


int stepCounter;
int steps = 2000;

void setup()
{
  pinMode(X_ENABLE_PIN, OUTPUT); // Enable
  pinMode(X_STEP_PIN, OUTPUT); // Step
  pinMode(X_DIR_PIN, OUTPUT); // Richtung

  digitalWrite(X_ENABLE_PIN, LOW); //LOW Aktiv
}

void loop()
{
  digitalWrite(X_DIR_PIN, HIGH); // im Uhrzeigersinn

  for (stepCounter = 0; stepCounter < steps; stepCounter++)
  {
    digitalWrite(X_STEP_PIN, HIGH);
    delayMicroseconds(500);
    digitalWrite(X_STEP_PIN, LOW);
    delayMicroseconds(500);
  }
  delay(1000);

  digitalWrite(X_DIR_PIN, LOW); // gegen den Uhrzeigersinn

  for (stepCounter = 0; stepCounter < steps; stepCounter++)
  {
    digitalWrite(X_STEP_PIN, HIGH);
    delayMicroseconds(500);
    digitalWrite(X_STEP_PIN, LOW);
    delayMicroseconds(500);
  }
  delay(1000);
}
