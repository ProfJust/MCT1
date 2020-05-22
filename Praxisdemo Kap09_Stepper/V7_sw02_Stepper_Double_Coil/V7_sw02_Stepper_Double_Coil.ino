//==========================================
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
// ELS III - SS16
//--------------------------------------
// V7_sw01_Stepper_Single_Coil.ino
//-----E-Blocks ------------------------
// LCD - Board an J20 (D24-D31)
// LED - Board an J5  (D16-D23)
// Tast - Board an J3 (D8 -D15)

//--- Die Stepper Kabel sind an folgende Pins gedrahtet ---
#define BLAU   16
#define GELB   17
#define ORANGE 18
#define ROT    19

//=========== globale Variablen =======================
const int L[4] = {ORANGE, ROT, BLAU, GELB,}; // Die 4 Wicklungen des Schrittmotors
unsigned int state = 0; //der aktuelle Zustand des Automaten
//--------------------------------------
void setup() {
  // Ports auf Ausgang setzen
  for (int i = 0; i < 4; i++)  pinMode(L[i], OUTPUT);
  state = 0; //Start
}
//--------------------------------------
void statemachine() {
  switch (state) {
    case 0:
      digitalWrite(L[0], HIGH);
      digitalWrite(L[1], LOW);
      digitalWrite(L[2], LOW);
      digitalWrite(L[3], HIGH);
      state = 1;
      break;
    case 1:
      digitalWrite(L[0], LOW);
      digitalWrite(L[1], LOW);
      digitalWrite(L[2], HIGH);
      digitalWrite(L[3], HIGH);
      state = 2;
      break;
    case 2:
      digitalWrite(L[0], LOW);
      digitalWrite(L[1], HIGH);
      digitalWrite(L[2], HIGH);
      digitalWrite(L[3], LOW);
      state = 3;
      break;
    case 3:
      digitalWrite(L[0], HIGH);
      digitalWrite(L[1], HIGH);
      digitalWrite(L[2], LOW);
      digitalWrite(L[3], LOW);
      state = 0;
      break;
  }
}
//--------------------------------------
void loop() {
  statemachine();
  delay(500);
}
