// MCT1_Kap08_sw03_StoppUhr_03_TimerIR_clKEy_clLED.ino
//-------------------------------------
// Combo-Board an (A0-A7) und (D0-D7)
//-------------------------------------
#include "clKey.h"
#include "clLED.h"
#include "TimerOne.h"
#define TIMER_INTERVALL_mS  1000UL     //in Mikrosekunden µsec

#include <LiquidCrystal.h>
LiquidCrystal lcd( 4, 5, 0, 1, 2, 3);  //Version für LCD an J2

//--- Die Tasten sind an folgende Pins gedrahtet ---
clKey startKey(A0); // Taste SA0
clKey stoppKey(A1); // Taste SA1
clKey resetKey(A2); // Taste SA2


clLED LED1(A6);
//=========== globale Variablen =======================
volatile int time_ms = 0; //Zeit in ms
int timeStart = 0; //Merker für Systemzeit beim Start

//--- Zustandsvariablen für die Tastenlogik ----
bool RunFlag   = false;  // Zustandsvariable Start/Stopp
bool ResetFlag = false;  // Zustandsvariable Reset

//-------------------Initialisierung-------------------------
void setup() {
  LED1.on();

  // LCD initialisieren
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.write("MCT - Stoppuhr 3");

  //Timer-Intervall konfigurieren => 1ms
  Timer1.initialize(TIMER_INTERVALL_mS);
  //Callback zur IR-Service-Routine
  Timer1.attachInterrupt(Timer_IRS);
}

//--- Die vom Timer aufgerufene IRS -----
void Timer_IRS() {
  if(time_ms%1000==0) //jede Sekunde
      LED1.toggle(); //LED togglen
  if (RunFlag) {
    //Die Uhr macht Tick Tack
    time_ms++;
  }
}

//-------------------Tastenlogik-------------------
void TasteAbfragen(){
  if(startKey.readKey())      {
    RunFlag = true;
    timeStart = millis();
  }
  if(stoppKey.readKey())      RunFlag = false;

  if(resetKey.readKey() && (RunFlag == false)) 
      ResetFlag = true;
  else
      ResetFlag = false;
}

//---------------------------------------------------------
void loop()
{
  //-- Eingabe ---
  TasteAbfragen();

  //--- Verarbeitung ---
  //Tick Tack im Timer IR
  if (ResetFlag) time_ms = 0;

  //--- Ausgabe -----
  if (ResetFlag) { // Bei Reset die letze Anzeige überschreiben
    lcd.setCursor(0, 1);
    lcd.print("      ");
  }
  // Aktuelle Zeit ausgeben
  lcd.setCursor(0, 1);
  lcd.print(time_ms);
}
