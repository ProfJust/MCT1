// sw02_Basic_A44988_Driver_X_und_Y_Motor
//-----------------------------------------
// MCT1
// Version vom 3.5.2019
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
#define X_STEP_PIN         54  // entspricht A0
#define X_DIR_PIN          55   //tested, entspricht A1
#define X_ENABLE_PIN       38

#define Y_STEP_PIN         60   
#define Y_DIR_PIN          61   
#define Y_ENABLE_PIN       56

//!SLEEP und !RESET sind kurzgeschlossen und haben keine Verbindung zum µC 
// =>  Basic connections: only DIR, EN, STEP are connected.
 // Microstepping controls should be hardwired. => bunte Jumper => 1/16
  A4988 stepperX(MOTOR_STEPS, X_DIR_PIN, X_STEP_PIN, X_ENABLE_PIN);
  A4988 stepperY(MOTOR_STEPS, Y_DIR_PIN, Y_STEP_PIN, Y_ENABLE_PIN);

void setup() {
    Serial.begin(115200);
   // Stepper konfigurieren
    stepperX.begin(RPM, MICROSTEPS);
    stepperX.setEnableActiveState(LOW);
    stepperX.enable();
    
    stepperY.begin(RPM, MICROSTEPS);
    stepperY.setEnableActiveState(LOW);
    stepperY.enable();
    
    
    // Set LINEAR_SPEED (accelerated) profile
    stepperX.setSpeedProfile(stepperX.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
    stepperY.setSpeedProfile(stepperY.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);

    Serial.println("START");
    stepperX.startRotate(-180);  //Motor dreht 180° linksherum
    delay(200);
    stepperY.startRotate(360);  //Motor dreht 360°  rechtsherum
}

void loop() {
    static int step = 0;
    unsigned wait_timeX = stepperX.nextAction();
    unsigned wait_timeY = stepperY.nextAction();
    if (wait_timeX || wait_timeY){
        Serial.print("  step="); Serial.print(step++);
        Serial.print("  dt=");   Serial.print(wait_timeX);
        Serial.print("  rpmX=");  Serial.print(stepperX.getCurrentRPM());
        Serial.print("  rpmY=");  Serial.print(stepperY.getCurrentRPM());
        Serial.println();
    } 
    else {
        stepperX.disable();
        stepperY.disable();
        Serial.println("END");
        delay(3600000); //Ende Programm
    }
}
