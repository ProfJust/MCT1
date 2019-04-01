// MCT1_Kap06_Serial_Switch_LED.ino
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
// Auf Jumper für PORT_A digital /analog achten
//-------------------------------------------
#define PIN_LA1 A1
int incomingByte = 0;   // for incoming serial data

//--- Callback für Interruptservice von Serial --- 
void serialEvent() {
  incomingByte = Serial.read();
}
//---- Dekodieren des Empfangs --------
void switch_led(int byte) {
  //--- Empfang / Prefix prüfen ----
  //Zeichen für Befehl '#' empfangen
  static bool received_Cmd = false;
  //Zeichen für LED_A1 '1' empfangen
  static bool received_1 = false;

  //Prefix #1 prüfen
  if (byte == '#')
    received_Cmd = true;
  else if (received_Cmd && byte == '1')
    received_1 = true;
  else if (byte != 'a' && byte != 'e') { //Murks empfangen
    received_Cmd = false;
    received_1 = false;
  }

  //--- Schalten des LEDs
  if (received_Cmd && received_1 && byte == 'e' ) {
    digitalWrite(PIN_LA1, HIGH);
    Serial.println(" Schalte LED LA1 AN");
  }
  if (received_Cmd && received_1 && byte == 'a' ) {
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
  if (incomingByte) {
    // say what you got:
    Serial.print("Empfange ASCII-Code ");
    Serial.print (incomingByte);
    Serial.print("    Das ist Zeichen ");
    Serial.write (incomingByte);
    Serial.println();
    switch_led(incomingByte);
    incomingByte = 0;
  }
}

