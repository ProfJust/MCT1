class clKeypad {

  public:
    /* TinkerCAD Tastenfeld
      // Am Tastenfeld: Input Zeile, Output Spalte
      // Am Arduino: OUTPUT Zeile, INPUT Spalte
      Zeile 1 =>       1    2    3    A
      Zeile 2 =>       4    5    6    B
      Zeile 3 =>       7    8    9    C
      Zeile 4 =>       *    0    #    D
            => Spalte [1]  [2]  [3]  [4]
    */

#define ZEILEN 4 // Four rows
#define SPALTEN 4 // Four columns

    byte zeilePin[ZEILEN] = { 9, 8, 7, 6 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
    byte spaltePin[SPALTEN] = { 5, 4, 3, 2 }; // Connect keypad COL0, COL1 and COL2 to these Arduino pins.

    //--- Konstruktor ----
    clKeypad () {
      // Ports auf Ein-/Ausgang setzen
      for (int i = 0; i < ZEILEN; i++) {
        pinMode(zeilePin[i], OUTPUT);
        pinMode(spaltePin[i], INPUT);
      }
    }

    //---- Einlesefkt  ----
    char scanKeypad() {
       char readChar = '\0';    
      
       digitalWrite(zeilePin[0], HIGH);
       if (digitalRead(spaltePin[0]) == HIGH) readChar = '1';
       if (digitalRead(spaltePin[1]) == HIGH) readChar = '2';
       if (digitalRead(spaltePin[2]) == HIGH) readChar = '3';
       if (digitalRead(spaltePin[3]) == HIGH) readChar = 'A';
       digitalWrite(zeilePin[0], LOW);
       if (readChar != '\0') return readChar;
      
       digitalWrite(zeilePin[1], HIGH);
       if (digitalRead(spaltePin[0]) == HIGH) readChar = '4';
       if (digitalRead(spaltePin[1]) == HIGH) readChar = '5';
       if (digitalRead(spaltePin[2]) == HIGH) readChar = '6';
       if (digitalRead(spaltePin[3]) == HIGH) readChar = 'B';
       digitalWrite(zeilePin[1], LOW);
       if (readChar != '\0') return readChar;
      
       digitalWrite(zeilePin[2], HIGH);
       if (digitalRead(spaltePin[0]) == HIGH) readChar = '7';
       if (digitalRead(spaltePin[1]) == HIGH) readChar = '8';
       if (digitalRead(spaltePin[2]) == HIGH) readChar = '9';
       if (digitalRead(spaltePin[3]) == HIGH) readChar = 'C';
       digitalWrite(zeilePin[2], LOW);
       if (readChar != '\0') return readChar;
      
       digitalWrite(zeilePin[3], HIGH);
       if (digitalRead(spaltePin[0]) == HIGH) readChar = '*';
       if (digitalRead(spaltePin[1]) == HIGH) readChar = '0';
       if (digitalRead(spaltePin[2]) == HIGH) readChar = '#';
       if (digitalRead(spaltePin[3]) == HIGH) readChar = 'D';    
       digitalWrite(zeilePin[3], LOW);
       
       return readChar;
    }
  
  //--- Dauerauslösung verhindern => Flankendetektion
  char getKey(){
    static char scanKeyOld;
    char scanKey = this->scanKeypad();
    
    if(scanKey != scanKeyOld){
      scanKeyOld = scanKey;
      return scanKey;
    }
    else {
      scanKeyOld = scanKey;
      return '\0';
    }   
  }
}; //ende clKeyPad


//=========== globale Variablen =======================
char key; //Tasten vom KeyPad

clKeypad myPad;
//--------------------------------------
void setup() {
  Serial.begin(9600); // Ausgabe an PC mit Baudrate 9600
  Serial.print("\n clKeypad MCT1 \n"); //Begrüßung
}

void loop() {
  //--- Eingabe -----
  key = myPad.getKey();  //Tasten abfragen
  
  //---- Ausgabe ----
  // Nur auf Serial ausgeben, wenn neues Zeichen kommt
  if (key != '\0') {
    Serial.print(key);
    Serial.print(" ");
    if (key == 'D') Serial.print(" Nextline \n");
  }
  //delay(2); //Zeitliche Entprellung, kann später bei längerer loop() entfallen
}
