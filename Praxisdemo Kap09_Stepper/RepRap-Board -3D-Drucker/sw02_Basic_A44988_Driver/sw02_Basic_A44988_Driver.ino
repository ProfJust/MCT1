// sw02_Basic_A44988_Driver
//-----------------------------------------
// MCT1
// Version vom 30.4.2019
//-----------------------------------------
// Ramps Board mit Arduino Mega 2560
// Polulu-Treiber A4988
// Fischertechnik 3D-Druck-Motor Moons 14HS
// Ext. Spannungsversorgun 10V, 1,5A
// Reset -Knopf an der Seite des Ramps_Boards
//-----------------------------------------
// basiert auf
// https://github.com/laurb9/StepperDriver

#include <Arduino.h>
#include "A4988.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
// Target RPM for cruise speed
#define RPM 20  //default was 120
// Acceleration and deceleration values are always in FULL steps / s^2
#define MOTOR_ACCEL 2000
#define MOTOR_DECEL 1000

// Microstepping mode. If you hardwired it to save pins, set to the same value here.
// Alle Junper gesetzt => 1/16 Microsteps                            
#define MICROSTEPS 16  
#define X_STEP_PIN         A0   // entspricht 54
#define X_DIR_PIN          A1   //tested, entspricht 55
#define X_ENABLE_PIN       38
//!SLEEP und !RESET sind kurzgeschlossen und haben keine Verbindung zum µC 
// =>  Basic connections: only DIR, EN, STEP are connected.
 // Microstepping controls should be hardwired. => bunte Jumper => 1/16
  A4988 stepper(MOTOR_STEPS, X_DIR_PIN, X_STEP_PIN, X_ENABLE_PIN);

void setup() {
    Serial.begin(115200);
   // Stepper konfigurieren
    stepper.begin(RPM, MICROSTEPS);
    stepper.setEnableActiveState(LOW);
    stepper.enable();
    
    // Set LINEAR_SPEED (accelerated) profile
    stepper.setSpeedProfile(stepper.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);

    Serial.println("START");
    stepper.startRotate(360);  //Motor dreht 360° - tested
}

void loop() {
    static int step = 0;
    unsigned wait_time = stepper.nextAction();
    if (wait_time){
        Serial.print("  step="); Serial.print(step++);
        Serial.print("  dt=");   Serial.print(wait_time);
        Serial.print("  rpm=");  Serial.print(stepper.getCurrentRPM());
        Serial.println();
    } 
    else {
        stepper.disable();
        Serial.println("END");
        delay(3600000); //Ende Programm
    }
}
