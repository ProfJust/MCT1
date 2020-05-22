//==========================================
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
// ELS III - SS16
//--------------------------------------
// V7_sw03_Stepper_Double_Coi_Halbschrittl.ino
//-----E-Blocks ------------------------
// LCD - Board an J20 (D24-D31)
// POWER - Board an J5  (D16-D23)
// Externes Netzteil 7,5V
// Tast - Board an J3 (D8 -D15)

//--- Die Stepper Kabel sind an folgende Pins gedrahtet ---
#define BLAU   16
#define GELB   17
#define ORANGE 18
#define ROT    19

//=========== globale Variablen =======================
const int L[4] = {ORANGE, ROT, BLAU, GELB,}; // Die 4 Wicklungen des Schrittmotors
unsigned int state = 0; //der aktuelle Zustand des Automaten

//---- Die Tasten-Zustände -----
#define TAST_PIN_AUS     8
#define TAST_PIN_FEST    9
#define TAST_PIN_RECHTS 10
#define TAST_PIN_LINKS  11
#define TAST_PIN_STEP_RECHTS  12

#define AUS    0
#define FEST   1
#define RECHTS 2
#define LINKS  3
#define KEINE  4
#define STEP_RECHTS 5

int dir = AUS;
//--------------------------------------
void setup() {
  Serial.begin(9600);
  Serial.print("State: ");
  Serial.print(state);
  Serial.print(" Taste: ");
  Serial.println(dir);
  // Ports auf Ausgang setzen
  for (int i = 0; i < 4; i++)  pinMode(L[i], OUTPUT);

  // Tasten auf Eingang
  pinMode(TAST_PIN_AUS, INPUT);
  pinMode(TAST_PIN_FEST, INPUT);
  pinMode(TAST_PIN_LINKS, INPUT);
  pinMode(TAST_PIN_RECHTS, INPUT);
  pinMode(TAST_PIN_STEP_RECHTS, INPUT);

  state = 0; //Start
}

int getTaste() {
  if (digitalRead(TAST_PIN_AUS)   == HIGH) return AUS;
  if (digitalRead(TAST_PIN_FEST)  == HIGH) return FEST;
  if (digitalRead(TAST_PIN_RECHTS) == HIGH) return RECHTS;
  if (digitalRead(TAST_PIN_LINKS) == HIGH) return LINKS;
  if (digitalRead(TAST_PIN_STEP_RECHTS) == HIGH) return STEP_RECHTS;
  return KEINE;
}
//--------------------------------------
void statemachine() {
  switch (state) {
    case 0:
      digitalWrite(L[0], HIGH);
      digitalWrite(L[1], LOW);
      digitalWrite(L[2], LOW);
      digitalWrite(L[3], LOW);
      if (dir == RECHTS) state = 1;
      if (dir == LINKS)  state = 7;
      if (dir == FEST)   state = state;
      if (dir == STEP_RECHTS) { state++; dir = FEST;}
      if (dir == AUS)    state = 8;
      break;
    case 1:
      digitalWrite(L[0], HIGH);
      digitalWrite(L[1], LOW);
      digitalWrite(L[2], LOW);
      digitalWrite(L[3], HIGH);
      if (dir == RECHTS) state = 2;
      if (dir == LINKS)  state = 0;
      if (dir == FEST)   state = state;
      if (dir == STEP_RECHTS) { state++; dir = FEST;}
      if (dir == AUS)    state = 8;
      break;
    case 2:
      digitalWrite(L[0], LOW);
      digitalWrite(L[1], LOW);
      digitalWrite(L[2], LOW);
      digitalWrite(L[3], HIGH);
      if (dir == RECHTS) state = 3;
      if (dir == LINKS)  state = 1;
      if (dir == FEST)   state = state;
      if (dir == STEP_RECHTS) { state++; dir = FEST;}
      if (dir == AUS)    state = 8;
      break;
    case 3:
      digitalWrite(L[0], LOW);
      digitalWrite(L[1], LOW);
      digitalWrite(L[2], HIGH);
      digitalWrite(L[3], HIGH);
      if (dir == RECHTS) state = 4;
      if (dir == LINKS)  state = 2;
      if (dir == FEST)   state = state;
      if (dir == STEP_RECHTS) { state++; dir = FEST;}
      if (dir == AUS)    state = 8;
      break;
    case 4:
      digitalWrite(L[0], LOW);
      digitalWrite(L[1], LOW);
      digitalWrite(L[2], HIGH);
      digitalWrite(L[3], LOW);
      if (dir == RECHTS) state = 5;
      if (dir == LINKS)  state = 3;
      if (dir == FEST)   state = state;
      if (dir == STEP_RECHTS) { state++; dir = FEST;}
      if (dir == AUS)    state = 8;
      break;
    case 5:
      digitalWrite(L[0], LOW);
      digitalWrite(L[1], HIGH);
      digitalWrite(L[2], HIGH);
      digitalWrite(L[3], LOW);
      if (dir == RECHTS) state = 6;
      if (dir == LINKS)  state = 4;
      if (dir == FEST)   state = state;
      if (dir == STEP_RECHTS) { state ++; dir = FEST;}
      if (dir == AUS)    state = 8;
      break;
    case 6:
      digitalWrite(L[0], LOW);
      digitalWrite(L[1], HIGH);
      digitalWrite(L[2], LOW);
      digitalWrite(L[3], LOW);
      if (dir == RECHTS) state = 7;
      if (dir == LINKS)  state = 5;
      if (dir == FEST)   state = state;
      if (dir == STEP_RECHTS) { state++; dir = FEST;}
      if (dir == AUS)    state = 8;
      break;
    case 7:
      digitalWrite(L[0], HIGH);
      digitalWrite(L[1], HIGH);
      digitalWrite(L[2], LOW);
      digitalWrite(L[3], LOW);
      if (dir == RECHTS) state = 0;
      if (dir == LINKS)  state = 6;
      if (dir == FEST)   state = state;
      if (dir == STEP_RECHTS) { state=0; dir = FEST;}
      if (dir == AUS)    state = 8;
      break;
    case 8: //++++ AUS +++++
      digitalWrite(L[0], LOW);
      digitalWrite(L[1], LOW);
      digitalWrite(L[2], LOW);
      digitalWrite(L[3], LOW);
      if (dir == RECHTS) state = 0;
      if (dir == LINKS)  state = 7;
      if (dir == FEST)   state = 7;
      if (dir == STEP_RECHTS) { state=0; dir = FEST;}
      if (dir == AUS)    state = 8;
      break;
  }
}
//--------------------------------------
void loop() {
  int taste = getTaste();
 
  if (taste != KEINE ) {
    if(taste != dir){  // && !(taste == STEP_RECHTS && dir == FEST)
    dir = taste;
    Serial.print("State: ");
    Serial.print(state);
    Serial.print(" Taste: ");
    Serial.print(taste);
    Serial.print(" Richtung: ");
    Serial.println(dir);
   }
  }
  statemachine();
  if(taste == STEP_RECHTS) delay(500); //Schritte zählen: 100 Stepps /90°
  delay(10);
}
