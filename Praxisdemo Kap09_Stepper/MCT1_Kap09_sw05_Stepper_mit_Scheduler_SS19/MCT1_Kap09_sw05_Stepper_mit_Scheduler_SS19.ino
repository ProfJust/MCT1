//==========================================
// WestfÃ¤lische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
// MCT1
//--------------------------------------
// MCT1_Kap09_sw05_Stepper_mit_Scheduler_SS19.ino
//
//-----E-Blocks ------------------------
// LED - Board an J5  (D16-D23) + Power-Board + Stepper-Motor
// 6V Steckernetzteil für Motor in Hohlstecker Arduino
// GND wird über Pin 9 S-Sub zurückgeführt - kein Kabel notw.
// 6V vom Vin-Schraubkl. am EB092 mit Schalter auf Sammelklemme  
// Sammelklemme mit schwarz, weiß vom Stepper
// MOSFETS D0..D3  => Pin 16..19
//----------------------------------------------

//--- Die Stepper Kabel sind an folgende Pins gedrahtet ---
#define BLAU   16
#define GELB   17
#define ORANGE 18
#define ROT    19

//=========== globale Variablen =======================
const int L[4] = {ORANGE, ROT, BLAU, GELB,}; // Die 4 Wicklungen des Schrittmotors
//unsigned int state = 0; //der aktuelle Zustand des Automaten

//=========== L C D =======================
/*#include <LiquidCrystal.h>
LiquidCrystal lcd( 4, 5, 0, 1, 2, 3);  //Version fÃ¼r LCD an J2
*/

//===================================================
//------------S C H E D U L E R ---------------------
//===================================================
#include <TaskScheduler.h>
Scheduler myScheduler;

//Zeit zwischen zwei Stepps
#define STEP_TIME 50  
#define NUMB_STEPS 4

//***********  I.) Prototypen der Task-Callbacks bekannt geben  *****************
void Task0_Callback();
void Task1_Callback();
void Task2_Callback();
void Task3_Callback();

//***********  II.) Tasks - Aufrufe  **************
// Objekte instanziieren
Task task0 (STEP_TIME*NUMB_STEPS, TASK_FOREVER, &Task0_Callback);
Task task1 (STEP_TIME*NUMB_STEPS, TASK_FOREVER, &Task1_Callback);
Task task2 (STEP_TIME*NUMB_STEPS, TASK_FOREVER, &Task2_Callback);
Task task3 (STEP_TIME*NUMB_STEPS, TASK_FOREVER, &Task3_Callback);

//***********  III.) Tasks - definieren  **************
void Task0_Callback() {
  String str = "Task0 " +String(millis());
  Serial.println(str);
   digitalWrite(L[0], HIGH);
   digitalWrite(L[1], LOW);
   digitalWrite(L[2], LOW);
   digitalWrite(L[3], LOW);
}
void Task1_Callback() {
   String str = "Task1 " +String(millis());
  Serial.println(str);
   digitalWrite(L[0], LOW);
   digitalWrite(L[1], HIGH);
   digitalWrite(L[2], LOW);
   digitalWrite(L[3], LOW);
}
void Task2_Callback() {
   String str = "Task2 " +String(millis());
  Serial.println(str);
  digitalWrite(L[0], LOW);
  digitalWrite(L[1], LOW);
  digitalWrite(L[2], HIGH);
  digitalWrite(L[3], LOW);
}
void Task3_Callback() {
   String str = "Task3 " +String(millis());
  Serial.println(str);
   digitalWrite(L[0], LOW);
   digitalWrite(L[1], LOW);
   digitalWrite(L[2], LOW);
   digitalWrite(L[3], HIGH);
}

//***********  IV.) Tasks - Initialisieren und teilweise enablen ***********
void setup() {
 // Ports auf Ausgang setzen
  for (int i = 0; i < 4; i++)  pinMode(L[i], OUTPUT);
 //Debug Ausgabe
  Serial.begin(115200);
 // Scheduler initialisieren
  myScheduler.init();   // Initialisieren des Schedulers
  myScheduler.addTask(task0);  // Task anmelden
  myScheduler.addTask(task1);
  myScheduler.addTask(task2);
  myScheduler.addTask(task3);
  //--- Tasks nacheinander starten ---
  task0.enable();
  task1.enableDelayed(1*STEP_TIME);
  task2.enableDelayed(2*STEP_TIME);
  task3.enableDelayed(3*STEP_TIME); 
}

//***********  V.) Scheduler triggern *************
void loop() {
  myScheduler.execute();
}

