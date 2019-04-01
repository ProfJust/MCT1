// MCT1_Kap06_2_Serial_Switch_LED_String.ino
//----------------------------------------------
// Mikorcontrollertechnik  - MCT1
// WHS - Campus Bocholt
// Prof. Dr.-Ing. O. Just
//----------------------------------------------
// * LED LA1 vom PC ansteuern
// * über Eingabe in Serial Monitor
// * #1e => LA1 ein
// * #1a => LA1 aus
// ---------------------------------------------
// Version vom 1.4.19
// für Combo-Board EB083 an A0-A7 und D0-D7
// für Arduino Mega Shield EB092
//-------------------------------------------
#define PIN_LA1 A1
String incomingString = " ";   // for incoming serial data

//--- Callback für Interruptservice von Serial --- 
void serialEvent() {
  incomingString = Serial.readString();
}
//---- Dekodieren des Empfangs --------
void switch_led(String str) {
  //--- Empfang / Prefix prüfen ----
   //--- Schalten des LEDs
  if (str =="#1e" ) {
    digitalWrite(PIN_LA1, HIGH);
    Serial.println(" Schalte LED LA1 AN");
  }
  if (str =="#1a" ) {
    digitalWrite(PIN_LA1, LOW);
    Serial.println(" Schalte LED LA1 aus");
  }
}


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("MCT1_Kap06_Serial_Switch_LED");
  Serial.println("#1e => LA1 einschalten, #1a =>LA1 ausschalten ");
  pinMode(PIN_LA1, OUTPUT);
}

void loop() {
  if (incomingString != " ") {
    // say what you got:
    Serial.print("Empfange String  ");
    Serial.print (incomingString);
    Serial.println();
    switch_led(incomingString);
    incomingString = " ";
  }
}

