///==========================================
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
// MCT1, Version vom 18.6.2018
//--------------------------------------
// sw01_BT_RS232_Callback_LEDon
//--------------------------------------
// Testet die Kommunikation über RS232 / Bluetooth 
// Serial1-Port angeschlossene HC06 Modul
// Android Smarty sendet über Bluetooth
//----------------------------------------------
//-----E-Blocks ------------------------
// LED - Board an J20 (D24-D31) insb. D18/D19
// Bluetooth - Board an J5 (D16 -D23)
//----------------------------------------------
// Serial1 liegt an D18 und D19
//  LINVOR mit 1234 paaren
// PC kein Bluetooth => use USB-Rx LogiLink BT0009
// oder Android Smartphone mit 
// "Serial Bluetooth Terminal"
//
// auf 115200  81N
// => LED an (ohne Blinken)
//----------------------------------------------
// Version vom 18.3.18
//----------------------------------------------
int incomingByte = 0;   // for incoming serial data

void setup() {
  pinMode(24, OUTPUT); //LED D0
  pinMode(25, OUTPUT); //LED D1 blinken
  
  // initialize serial communication 
  //!!!!!!!!!! Achtung verschiedene Boards mit unterschiedlichen Baudraten
  //======================================================================
  //Serial1.begin(115200); //HC06 an Serial1
    Serial1.begin(38400); //HC05 an Serial1
    Serial1.println("sw01 Bluetooth RS232 mit Callback-Funtkion");
}

void loop() {  
  if(incomingByte){
     // say what you got:
     Serial1.print("I received: ASCII-Code ");
    Serial1.println (incomingByte);
    switch_led(incomingByte);
    incomingByte = 0;
  }
  //--Blinken an D1 ---
  if (millis()%1000 ==0)
    digitalWrite(25,!digitalRead(25));
}
void serialEvent1(){
 incomingByte = Serial1.read();
}

void switch_led(int byte){
  switch(byte){
    case '1': digitalWrite(24,HIGH);
              Serial1.println(" LED AN");
              break;
    case '2': digitalWrite(24,LOW); 
              Serial1.println(" LED AUS");
              break;
  }
}

