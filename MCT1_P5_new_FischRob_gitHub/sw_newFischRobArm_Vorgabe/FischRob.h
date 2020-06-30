/* FischRob.h
 * Westfaelischer Hochschule Campus Bocholt
 * MikroControllerTechnik 1 Tutorium 
 * Fischertechnik - Robotics in Industry
 * Gerald Hebinck, Mai 2019
 * 
 * Auslagerung der Definitionen und Instanzierungen
 * 
 */
#include <Wire.h>
#include "clNunchuck.h"
#include "clRoboter.h"

// Enable Pin zum L293D
#define U1_EN12 4
#define U1_EN34 5
#define U2_EN12 6

#define U1_1A 8
#define U1_2A 9
#define U1_3A 10
#define U1_4A 11
#define U2_1A 12
#define U2_2A 13
#define S1 14
#define S2 15
#define S3 16
// Encoder 
#define ENC_1 18
#define ENC_2 19
#define ENC_3 2
#define ROT_LIMIT 2500
#define LIFT_LIMIT 2500
#define PICK_LIMIT 500

// Array zur Uebergabe der Pins an die Roboterklasse
int pin[3][5] = {
  {U1_1A, U1_2A, ENC_1, S1, U1_EN12},
  {U1_4A, U1_3A, ENC_2, S2, U1_EN34},
  {U2_1A, U2_2A, ENC_3, S3, U2_EN12}
};

// Array zur Uebergabe der unteren und oberen Limits an die Roboterklasse
int limit[3][2] = {
  {0, ROT_LIMIT},
  {0, LIFT_LIMIT},
  {0, PICK_LIMIT}
};

// Zaehlvariablen, volatile wegen Zugriff aus ISR
volatile int rot_cnt = 0, lift_cnt = 0, pick_cnt = 0;

// Pointerarray auf die Zaehlvariablen zur Uebergabe an die Roboterklasse
volatile int* enc_val[3] = {&rot_cnt, &lift_cnt, &pick_cnt};

// Array zum Aktivieren der Limits zur Uebergabe an die Roboterklasse
bool limits[3] = { HIGH, HIGH, HIGH };

// Instanzierung von Nunchuck und Roboter
clNunchuck myNun;
clRoboter myRobo(pin, limit, limits, enc_val);

// Variablen zur Steuerung
int rot = 0, lift = 0, pick = 0, button_1 = 0, button_2 = 0;

// Variablen für Drehrichtung
int rot_run = 0, lift_run = 0, pick_run = 0;

// Variablen fuer die Eingaenge
bool s1 = LOW, s2 = LOW, s3 = LOW;

// Variable fuer die Zeiterfassung
unsigned long int timestamp = 0;

// ISRs fuer Encoderwerte
void isr_rot() {
  rot_cnt += rot_run;
}
void isr_lift() {
  lift_cnt += lift_run;
}
void isr_pick() {
  pick_cnt += pick_run;
}
