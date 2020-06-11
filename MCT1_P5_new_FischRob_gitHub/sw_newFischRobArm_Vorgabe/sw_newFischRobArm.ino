/*
 * Westfaelischer Hochschule Campus Bocholt
 * MikroControllerTechnik 1 Tutorium 
 * Fischertechnik - Robotics in Industry
 * Gerald Hebinck, Mai 2019
 * 
 * Dieses Programm ermöglicht die Ansteuerung Greif-Roboters mit einem Nunchuck. 
 * Die Werte des Nunchuck werden per I2C ausgelesen und dann an die Roboterklasse weitergegeben
 * Des Weiteren werden die Encoderwerte über ISRs erfasst und die Encoder durch Endschalter
 * initialisiert. 
 * 
 */
#include "FischRob.h"

//Initialisierung
void setup() {
  Serial.begin(74880);
  Wire.begin();
  myNun.begin();
  myRobo.refDrive();
  attachInterrupt(digitalPinToInterrupt(ENC_1), isr_rot, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_2), isr_lift, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_3), isr_pick, CHANGE);
}

void loop() {
  //---- Einlesen -----
  myNun.update();
  //Joystick-Werte holen
  rot = myNun.cjoy_x();
  lift = myNun.cjoy_y();
  //Nunchuck - Buttons 
  button_1 = myNun.button_c();
  button_2 = myNun.button_z();
  //Endschalter
  s1 = digitalRead(S1);
  s2 = digitalRead(S2);
  s3 = digitalRead(S3);

 //---- Verarbeiten -----
 // Button des Nunchuck zum Greifen
  if (button_1) { //Buttons des Nunchuck zum Greifen
    pick = 100;
  }
  else if (button_2) {
    pick = -100;
  }
  else {
    pick = 0;
  }

// PWM der Achsen starten mit Joystick-Werten
  rot_run = myRobo.drive_rot(rot, 110);
  lift_run = myRobo.drive_lift(lift, 110);
  pick_run = myRobo.drive_pick(pick, 100);

 // Endschalter 
  if (s1) {
    rot_cnt = 0;
  }
  if (s2) {
    lift_cnt = 0;
  }
  if (s3) {
    pick_cnt = 0;
  }

//--- Ausgabe Serial ----
  if (timestamp + 1000 < millis()) {
    timestamp = millis();
    Serial.print("Encoder:");
    Serial.print(" Rot = ");
    Serial.print(rot_cnt);
    Serial.print(" Lift = ");
    Serial.print(lift_cnt);
    Serial.print(" Pick = ");
    Serial.println(pick_cnt);
    Serial.print("Nunchuck:");
    Serial.print(" Rot = ");
    Serial.print(rot);
    Serial.print(" Lift = ");
    Serial.print(lift);
    Serial.print(" Pick = ");
    Serial.println(pick);
    Serial.println("   -----------------------  ");
  }
}
