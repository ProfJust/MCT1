//================ clKeypad.h =====================
class clKeyPad {
  private:
    const byte ROWS = 4; // Four rows
    const byte COLS = 4; // Three columns

  // Define the Keymap
  char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };
  byte rowPin[ROWS] = { 0, 1, 2, 3 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
  byte colPin[COLS] = { 4, 5, 6, 7 }; // Connect keypad COL0, COL1 and COL2 to these Arduino pins.
 
  public:
    clKeyPad(); //Konstruktor
    char scanKeypad();
};

//---- Konstruktor ----
clKeyPad::clKeyPad() {
    // Ports auf Ein-/Ausgang setzen
  for (int i = 0; i <= 3; i++) {
    pinMode(rowPin[i], INPUT);
    pinMode(colPin[i], OUTPUT);
  }
}

char clKeyPad::scanKeypad() {
  char readChar = '\0';
  digitalWrite(colPin[0], HIGH);
  if (digitalRead(rowPin[0]) == HIGH) readChar = '1';
  if (digitalRead(rowPin[1]) == HIGH) readChar = '4';
  if (digitalRead(rowPin[2]) == HIGH) readChar = '7';
  if (digitalRead(rowPin[3]) == HIGH) readChar = '*';
  digitalWrite(colPin[0], LOW);
  if (readChar != '\0') return readChar;

  digitalWrite(colPin[1], HIGH);
  if (digitalRead(rowPin[0]) == HIGH) readChar = '2';
  if (digitalRead(rowPin[1]) == HIGH) readChar = '5';
  if (digitalRead(rowPin[2]) == HIGH) readChar = '8';
  if (digitalRead(rowPin[3]) == HIGH) readChar = '0';
  digitalWrite(colPin[1], LOW);
  if (readChar != '\0') return readChar;

  digitalWrite(colPin[2], HIGH);
  if (digitalRead(rowPin[0]) == HIGH) readChar = '3';
  if (digitalRead(rowPin[1]) == HIGH) readChar = '6';
  if (digitalRead(rowPin[2]) == HIGH) readChar = '9';
  if (digitalRead(rowPin[3]) == HIGH) readChar = '#';
  digitalWrite(colPin[2], LOW);
  if (readChar != '\0') return readChar;

  digitalWrite(colPin[3], HIGH);
  if (digitalRead(rowPin[0]) == HIGH) readChar = 'A';
  if (digitalRead(rowPin[1]) == HIGH) readChar = 'B';
  if (digitalRead(rowPin[2]) == HIGH) readChar = 'C';
  if (digitalRead(rowPin[3]) == HIGH) readChar = 'D';
  digitalWrite(colPin[3], LOW);
  return readChar;
}
