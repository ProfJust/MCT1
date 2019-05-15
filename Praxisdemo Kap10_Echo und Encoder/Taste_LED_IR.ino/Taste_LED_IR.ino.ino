//= == == == == == == == == == == == == == == == == == == =
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
//********************************************************/
// MCT1, 15.5.2019
// 
// Taste_LED_IR.ino
//-------------------------------------
// LED - Board an J20 (D24-D31)
// Tast - Board an J5 (D16 -D23)
// oder Combo Board 
//----------------------------------
const int ledPin = 29;
const int btnPin = 21; //SB5 an J5
volatile int state = HIGH;

//--- Initialisierung -----
void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  //--- externen IR bekannt geben ---
  attachInterrupt(digitalPinToInterrupt(btnPin), IRS_sw0, RISING);
}

// --- Dauerschleife ------
void loop() {
  digitalWrite(ledPin, state);
  delay(100);
}

//--- Die Interrupt-Service Routine ----
void IRS_sw0() {
  if (state == HIGH)
    state = LOW;
  else
    state = HIGH;
  }

