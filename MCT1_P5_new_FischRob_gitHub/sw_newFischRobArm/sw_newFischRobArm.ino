/*
   Westfaelischer Hochschule Campus Bocholt
   MikroControllerTechnik 1 Tutorium
   Fischertechnik - Robotics in Industry
   Gerald Hebinck, Mai 2019
   Olaf Just, Juni 2020

   Dieses Programm ermöglicht die Ansteuerung Greif-Roboters mit einem Nunchuck.
   Die Werte des Nunchuck werden per I2C ausgelesen und dann an die Roboterklasse weitergegeben
   Des Weiteren werden die Encoderwerte über ISRs erfasst und die Encoder durch Endschalter
   initialisiert.
*/
//-------------------------------------------------------------------
// Speichert Position mit "#M1" und "#M2"-Befehlen im Serial-Monitor
// Fährt Position an mit "#R1" bzw. "#R2"
//-------------------------------------------------------------------
// verbleibende Probleme beim newFischRob
//-------------------------------------------------------------------
// 12.06.2019
// Priorisierung der Achsen bei Memory-Fahrt: erst hoch dann drehen dann Picker
// Picker-Encoder sehr ungenau => immer komplett öffnen bis Endschalter
// Aufräuhmen im loop()
//-------------------------------------------------------------------
#include "FischRob.h"
//--- globals ---
int mem_rot1, mem_lift1, mem_pick1;  //Positionsspeicher 1
int mem_rot2, mem_lift2, mem_pick2;  //Positionsspeicher 2
int memRunNr = 0; //aktuelle Memoryfahrt
String incomingString = " ";   // for incoming serial data
void AusgabeSerial(); //Debug-Ausgabe
void checkSerialIncoming(); //Prüfe ob Befehl auf Serial vorliegt
void goToMemPosition(int memNr); //gespeicherte position anfahren
//--- Callback für Interruptservice von Serial ---
void serialEvent() {
  incomingString = Serial.readString();
}

// ---- Initialisierung -----
void setup() {
  Serial.begin(74880);
  Wire.begin();
  myNun.begin();
  myRobo.refDrive();
  attachInterrupt(digitalPinToInterrupt(ENC_1), isr_rot, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_2), isr_lift, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_3), isr_pick, CHANGE);
}
//--- Hauptschleife ----
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
  //--- Serial checken ---
  if (incomingString != " ") {
    // say what you got:
    Serial.print("\nEmpfange String  ");
    Serial.print (incomingString);
    checkSerialIncoming();
  }
  // --- Endschalter ckecken => Counterwerte auf Null ---
  if (s1) rot_cnt = 0;
  if (s2) lift_cnt = 0;
  if (s3) pick_cnt = 0;

  //--- FischRob in Bewegung setzen ---
  if (memRunNr) {
    goToMemPosition(memRunNr); // Fahrt zur gespeicherten Position
  }
  else {
    //---  Handsteuerung: PWM der Achsen mit Joystick-Werten
    rot_run = myRobo.drive_rot(rot);
    lift_run = myRobo.drive_lift(lift);
    pick_run = myRobo.drive_pick(pick, 100);
  }



  //--- Ausgabe Serial jede Sekunde ----
  if ( millis() > timestamp + 1000 ) {
    timestamp = millis();
    AusgabeSerial();
  }
}

void AusgabeSerial() {
  Serial.println("   ----- Encoder Cntr:  Aktuell und Memory --------  ");
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
  Serial.print("Memory M1:");
  Serial.print(" Rot = ");
  Serial.print(mem_rot1);
  Serial.print(" Lift = ");
  Serial.print(mem_lift1);
  Serial.print(" Pick = ");
  Serial.println(mem_pick1);
  Serial.print("Memory M2:");
  Serial.print(" Rot = ");
  Serial.print(mem_rot2);
  Serial.print(" Lift = ");
  Serial.print(mem_lift2);
  Serial.print(" Pick = ");
  Serial.println(mem_pick2);
}
void checkSerialIncoming() {
  if (incomingString == "#M1") {

   //... Hier Code einfügen ..
    Serial.println("\n Speichere Position M1");
  }
  
  //... Hier Code einfügen ..
  
  incomingString = " "; //alten Inhalt löschen
}
void goToMemPosition(int memNr) {
  // Positioniergenauigkeit
  const int epsilon = 10;
  const int epsilonPick = 20;
  switch (memNr) {
    case 1:
      if (mem_rot1 > rot_cnt)
        rot_run = myRobo.drive_rot(+90);
    //... Hier Code einfügen .. 



    
      if ( abs(mem_rot1 - rot_cnt) < epsilon && abs(mem_lift1 - lift_cnt) < epsilon &&  abs(mem_pick1 - pick_cnt) < epsilonPick)
        memRunNr = 0;
      break;
    case 2:
    //... Hier Code einfügen ..
      break;
  } //switch
}

