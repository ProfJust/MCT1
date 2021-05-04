//= == == == == == == == == == == == == == == == == == == == == =
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
//****************************************************************/
// MCT1, SS2020 für TinkerCAD Tastenfeld
// Ziffernblock / Keypad einlesen 
//*****************************************************************/
/* TinkerCAD Tastenfeld
// Am Tastenfeld: Input Zeile, Output Spalte
// Am Arduino: OUTPUT Zeile, INPUT Spalte       
  Zeile 1 =>       1    2    3    A
  Zeile 2 =>       4    5    6    B
  Zeile 3 =>       7    8    9    C
  Zeile 4 =>       *    0    #    D
        => Spalte [1]  [2]  [3]  [4]
*/

#define ROWS 4 // Four rows
#define COLS 4 // Three columns

  // Define the Keymap
  char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };
  byte rowPin[ROWS] = { 9, 8, 7, 6 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
  byte colPin[COLS] = { 5, 4, 3, 2 }; // Connect keypad COL0, COL1 and COL2 to these Arduino pins.
   
//---- Einlesfkt  ----
char scanKeypad() {
  char readChar = '\0';
  digitalWrite(rowPin[0], HIGH);
  if (digitalRead(colPin[0]) == HIGH) readChar = '1';
  if (digitalRead(colPin[1]) == HIGH) readChar = '2';
  if (digitalRead(colPin[2]) == HIGH) readChar = '3';
  if (digitalRead(colPin[3]) == HIGH) readChar = 'A';
  digitalWrite(rowPin[0], LOW);
  if (readChar != '\0') return readChar;

  digitalWrite(rowPin[1], HIGH);
  if (digitalRead(colPin[0]) == HIGH) readChar = '4';
  if (digitalRead(colPin[1]) == HIGH) readChar = '5';
  if (digitalRead(colPin[2]) == HIGH) readChar = '6';
  if (digitalRead(colPin[3]) == HIGH) readChar = 'B';
  digitalWrite(rowPin[1], LOW);
  if (readChar != '\0') return readChar;

  digitalWrite(rowPin[2], HIGH);
  if (digitalRead(colPin[0]) == HIGH) readChar = '7';
  if (digitalRead(colPin[1]) == HIGH) readChar = '8';
  if (digitalRead(colPin[2]) == HIGH) readChar = '9';
  if (digitalRead(colPin[3]) == HIGH) readChar = 'C';
  digitalWrite(rowPin[2], LOW);
  if (readChar != '\0') return readChar;

  digitalWrite(rowPin[3], HIGH);
  if (digitalRead(colPin[0]) == HIGH) readChar = '*';
  if (digitalRead(colPin[1]) == HIGH) readChar = '0';
  if (digitalRead(colPin[2]) == HIGH) readChar = '#';
  if (digitalRead(colPin[3]) == HIGH) readChar = 'D';
  digitalWrite(rowPin[3], LOW);
  return readChar;
}

//=========== globale Variablen =======================
char key, keyOld; //Tasten vom KeyPad
//--------------------------------------
void setup() {
  Serial.begin(9600); // Ausgabe an PC mit Baudrate 9600
  Serial.println("clKeypad MCT1"); //Begrüßung

  // Ports auf Ein-/Ausgang setzen
  for (int i = 0; i <= 3; i++) {
    pinMode(rowPin[i], OUTPUT);
    pinMode(colPin[i], INPUT);
  }
}
void loop() {
  key = scanKeypad();  //Tasten abfragen  
  // Nur auf Serial ausgeben, wenn neues Zeichen kommt
  if (key != '\0' && key != keyOld) {
    Serial.print(key);
    Serial.print(" ");
    if (key == 'D') Serial.println(" Nextline ");
  }
  keyOld = key;
  delay(2); //Zeitliche Entprellung, kann später bei längerer loop() entfallen
}
