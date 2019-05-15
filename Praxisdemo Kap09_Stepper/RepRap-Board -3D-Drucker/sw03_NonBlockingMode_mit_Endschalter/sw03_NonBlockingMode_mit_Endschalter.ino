// sw03_NonBlockingMode mit Endschalter.no
// 30.4.2019
/*
 * Example using non-blocking mode to move until a switch is triggered.
 *
 * Copyright (C)2015-2017 Laurentiu Badea
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include <Arduino.h>
 #include "A4988.h"

//--- Endschalter Fischertechnik Schließer
//#define X_MIN_PIN           3  //D3
//#define X_MAX_PIN           2
// this pin should connect to Ground when want to stop the motor
#define STOPPER_PIN 3

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
// Target RPM for cruise speed
#define RPM 20  //deafult was 120
// Acceleration and deceleration values are always in FULL steps / s^2
#define MOTOR_ACCEL 2000
#define MOTOR_DECEL 1000
// Microstepping mode. If you hardwired it to save pins, set to the same value here.
#define MICROSTEPS 16
#define X_STEP_PIN         54
#define X_DIR_PIN          55   //tested
#define X_ENABLE_PIN       38
volatile unsigned wait_time_micros;

 A4988 stepper(MOTOR_STEPS, X_DIR_PIN, X_STEP_PIN, X_ENABLE_PIN);

void setup() {
    Serial.begin(115200);
    // Configure stopper pin to read HIGH unless grounded
    pinMode(STOPPER_PIN, INPUT_PULLUP);
    stepper.begin(RPM, MICROSTEPS);
    stepper.setEnableActiveState(LOW);
    stepper.enable();
   
    Serial.println("START");
    // set the motor to move continuously for a reasonable time to hit the stopper
    // let's say 100 complete revolutions (arbitrary number)
    //stepper.startMove(100 * MOTOR_STEPS * MICROSTEPS);     // in microsteps Funktioniert nicht
     stepper.startRotate(100 * 360);                     // or in degrees
}

void loop() {
    // first, check if stopper was hit
    if (digitalRead(STOPPER_PIN) == LOW){
        Serial.println("STOPPER REACHED");

        // * Choosing stop() vs startBrake():
        // *
        // * constant speed mode, they are the same (stop immediately)
        // * linear (accelerated) mode with brake, the motor will go past the stopper a bit
           stepper.stop();
        // stepper.startBrake();
    }
    // motor control loop - send pulse and return how long to wait until next pulse
    wait_time_micros = stepper.nextAction();

    // 0 wait time indicates the motor has stopped
    if (wait_time_micros <= 0) {
      Serial.print("DISABLE ");
      Serial.println(wait_time_micros);
        stepper.disable();       // comment out to keep motor powered
        delay(3600000);
    }
    // (optional) execute other code if we have enough time
    
    if (wait_time_micros > 100){
        // other code here
        Serial.println(wait_time_micros);
    }
}
