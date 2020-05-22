//==========================================
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
// MCT1
//--------------------------------------
//MCT1_Kap08_sw05a_StoppUhr_04_Scheduler.ino
// Combo-Board an (A0-A7) und (D0-D7)

//--- Die Tasten sind an folgende Pins gedrahtet ---
const int StartPin =  A0; // Taste SA0
const int StoppPin =  A1; // Taste SA1
const int ResetPin = A2; // Taste SA2

//=========== globale Variablen =======================
volatile unsigned long int time_ms = 0; //Zeit in ms

//=========== L C D =======================
#include <LiquidCrystal.h>
//LiquidCrystal lcd(28, 29, 24, 25, 26, 27); //Version für LCD an J20 PinNr.+24
LiquidCrystal lcd( 4, 5, 0, 1, 2, 3);  //Version für LCD an J2
//===================================================
//------------S C H E D U L E R ---------------------
//===================================================
#include <TaskScheduler.h>
Scheduler myScheduler;

//***********  I.) Prototypen der Task-Callbacks bekannt geben  *****************
void Task1_TickTack_Callback();
void Task2_TastePollen_Callback();
void Task3_LCD_Callback();
void Task4_LCD_clear_Callback();

//***********  II.) Tasks - Aufrufe  **************
Task Task1_TickTack    (  1, TASK_FOREVER, &Task1_TickTack_Callback);
Task Task2_TastePollen ( 10, TASK_FOREVER, &Task2_TastePollen_Callback);
Task Task3_LCD         (100, TASK_FOREVER, &Task3_LCD_Callback);
Task Task4_LCD_clear   (100, TASK_FOREVER, &Task4_LCD_clear_Callback);

//***********  III.) Tasks - definieren  **************
void Task1_TickTack_Callback() {
  //Die Uhr macht Tick Tack
  time_ms++;
}
//-------------------Tasten abfragen ---------------
void Task2_TastePollen_Callback() {
  if (Task2_TastePollen.isFirstIteration()) {
    // Tasten als Eingang setzen
    pinMode(StartPin, INPUT);
    pinMode(StoppPin, INPUT);
    pinMode(ResetPin, INPUT);
  }
  if (digitalRead(StartPin))     {
      Task1_TickTack.enable();    // Uhr einschalten
  }
  if (digitalRead(StoppPin))   {
     Task1_TickTack.disable();  // Uhr ausschalten
  }
  if (digitalRead(ResetPin) && (Task1_TickTack.isEnabled() == false)){
    time_ms = 0;
    Task4_LCD_clear.enable();
    Task3_LCD.delay(1000); // Feature: LCD Verzögerung
  }
}
//------------------- Ausgabe LCD -----------------
void Task3_LCD_Callback() {
  if (Task3_LCD.isFirstIteration()) {
    // LCD initialisieren
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.write("MCT-Scheduler ");
  }
  
  // Aktuelle Zeit ausgeben
  lcd.setCursor(0, 1);
  lcd.print(time_ms);
}

void Task4_LCD_clear_Callback() {
 lcd.setCursor(0, 1);
 lcd.print("          ");
 Task4_LCD_clear.disable();
}

//***********  IV.) Tasks - Initialisieren und teilweise enablen ***********
void setup() {
  myScheduler.init();   // Initialisieren des Schedulers

  myScheduler.addTask(Task1_TickTack);  // Task anmelden
  myScheduler.addTask(Task2_TastePollen);
  myScheduler.addTask(Task3_LCD);
  myScheduler.addTask(Task4_LCD_clear);
 
  Task2_TastePollen.enable();
  Task3_LCD.enable();
}

//***********  V.) Scheduler triggern *************
void loop() {
  myScheduler.execute();
}
