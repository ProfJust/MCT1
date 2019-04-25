// MCT1 - MCT1_Kap08_sw01_StoppUhr_01_delay
//-------------------------------------
// Combo-Board an (A0-A7) und (D0-D7)
//-------------------------------------
#include "clKey.h"
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
  //     LCD Pins   RS EN D4 D5 D6 D7
  // D-SUB-Stecker Nr  5  6  1  2  3  4 
  // Arduino Pin Nr   D4 D5 D0 D1 D2 D3  (Stecker J2)
  LiquidCrystal lcd( 4, 5, 0, 1, 2, 3);  //Version für LCD an J2 
  //    Achtung!! Bei EB092 an Programm Schalter denken
  //LiquidCrystal lcd(28,29,24,25,26,27);  //Version für LCD an J20 PinNr.+24
  //LiquidCrystal lcd(15,14,19,18,17,16);  //Version für LCD an J5 
  //LiquidCrystal lcd(12,13, 8, 9,10,11);  //Version für LCD an J3 

  //=========== globale Variablen =======================
int time_ms = 0; //Zeit in ms
//--- Die Tasten sind an folgende Pins gedrahtet ---
clKey startKey(A0); // Taste SA0
clKey stoppKey(A1); // Taste SA1
clKey resetKey(A2); // Taste SA2

//--- Zustandsvariablen für die Tastenlogik ----
bool RunFlag   = false;  // Zustandsvariable Start/Stopp
bool ResetFlag = false;  // Zustandsvariable Reset

//-------------------Initialisierung-------------------------
void setup(){
   // LCD initialisieren
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.write("MCT1 - Stoppuhr");
}
//-------------------Tastenlogik-------------------
void TasteAbfragen(){
  if(startKey.readKey()) RunFlag = true;
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
  if(RunFlag){
   delay(1); //Die Uhr macht Tick Tack
   time_ms++;
  }
  if(ResetFlag) time_ms=0;
  
  //--- Ausgabe -----
  if(ResetFlag){
    lcd.setCursor(0, 1);
    lcd.print("      "); 
  }
  
  lcd.setCursor(0, 1);
  lcd.print(time_ms);
}
