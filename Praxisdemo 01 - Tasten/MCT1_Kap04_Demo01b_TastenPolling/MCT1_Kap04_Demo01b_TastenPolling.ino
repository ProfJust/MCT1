// MCT1
// MCT1_Kap04_Demo01b_TastenPolling.ino
// Version vom 28.3.2019
// gitHub Source Control Test2
//-------------------------------------
// LED - Board an J5 (D16 -D23)
// Tast - Board an J3 (D8-D15)
//-------------------------------------
const int LED_PIN = 23; // LED LA7 an D23
const int BTN_PIN = 20;   // pushbutton SB7 an D8

//--- Zustandsspeicher (kein bool da   int digitalRead() )
int btnState = HIGH;
int btnStateOld = 1;
int ledState = HIGH;

//--------------------------------------
void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);
}
//--------------------------------------
void loop() {
 // --- Eingabe erfassen ---
  btnState = digitalRead(BTN_PIN);   // Taste pollen

 // --- Verarbeitung ---
  // -- Nur bei steigender Flanke wird Zustand der LED geaendert
  //    LOW   Flanke  HIGH
  //           |------------
  //    -------|

  // Rising Edge ?
  if ( btnStateOld == LOW && btnState == HIGH) {
    // Toogeln des LED-Zustands
    if (ledState == HIGH) 
      ledState = LOW;
    else
      ledState = HIGH;
  }
  //alten Zustand setzen
  btnStateOld = btnState; 
  
 // --- Ausgabe ---
  digitalWrite(LED_PIN, ledState);
  delay(2); //zeitliche Entprellung
}
