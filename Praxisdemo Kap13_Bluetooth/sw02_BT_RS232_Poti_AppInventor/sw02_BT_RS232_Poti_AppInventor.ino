///==========================================
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
// MCT1, Version vom 18.6.2018
//--------------------------------------
// sw02_BT_RS232_Poti_AppInventor
//--------------------------------------
// Testet die Kommunikation über RS232 / Bluetooth
// Serial1-Port angeschlossene HC06 Modul
// Android Smarty sendet über Bluetooth
//----------------------------------------------
//-----E-Blocks ------------------------
// Combo - Board an J2 (D0-D7)
// Bluetooth - Board an J5 (D16 -D23)
// LED Board an D24-D31
//----------------------------------------------

// PC kein Bluetooth => use USB-Rx LogiLink BT0009
// oder Android Smartphoen mit Blueterm
//
// BlueTerm / HTERM auf 115200  81N
// => LED an (ohne Blinken)
/*
  # LCD an J2 (D0-D7) (Combo-Board)
  # => Schalter LCD auf ON
  # und Schalter PROGRAMM auf RUN
  # LDR-Sensor Combo Board an J1 (A0)=> Jumper umstecken
  # Poti-Sensor Combo Board an J1 (A1)=> Jumper umstecken
  # Bluetooth -Board an J5 (D16-DD23) +5V (Serial1)
  Serial1 liegt an D18 und D19
  LINVOR mit 1234 paaren
  # zugehöriges Projekt imApp-Inventor:
  BlueFish
  ------------------------------------------
*/
//----------------------------------------------
// Version vom 28.5.19
//----------------------------------------------


#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
//                RS EN D4 D5 D6 D7
LiquidCrystal lcd(4, 5, 0, 1, 2, 3); //J2

//=========== globale Variablen =======================
char str[17]; //String fuer LCD Ausgabe

// AD-Wandler- Eingaenge
const int sensorPinLDR  = A0;    // input pin for the LDR
const int sensorPinPoti = A1;    // input pin for the potentiometer
// variable to store the value coming from the sensor
int sensorValueLDR  = 0;
int sensorValuePoti = 0;
int incomingByte = 0;   // for incoming serial data
//==============================================
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.write("Bluetooth Sensor");
  lcd.setCursor(0, 1);
  lcd.print("28.Mai 2019");
  delay(1000);
  //lcd.clear();
  Serial1.begin(38500); //HC05 38500 / HC06 115200
  Serial1.println("ADC");
  for (int pinNr = 24; pinNr <= 31; pinNr++) {
    pinMode(pinNr, OUTPUT);
  }
}
//==============================================
void loop() {
  //-- Einlesen --
  // read the value from the sensor:
  sensorValuePoti = analogRead(sensorPinPoti);
  sensorValueLDR  = analogRead(sensorPinLDR);

  //-- Verarbeiten --
  if (incomingByte) {
    switch_led(incomingByte);
    incomingByte = 0;
  }
  //-- Ausgeben --
  sprintf(str, "Poti: %04d   ", sensorValuePoti);
  lcd.setCursor(0, 1);
  lcd.write(str);

  //Zeichen # zeigt beginn der Nachricht
  sprintf(str, "#%04d\n", sensorValuePoti);
  Serial1.println(str);
  delay(100);
}

void serialEvent1() {
  incomingByte = Serial1.read();
}

void switch_led(int byte) {
  static int LEDnr = 30;
  digitalWrite(LEDnr, LOW); //alte LED aus
  switch (byte) {
    case 'l':  if (LEDnr < 31)
        LEDnr++;
      break;
    case 'r': if (LEDnr > 24)
        LEDnr--;
      break;
  }
  digitalWrite(LEDnr, HIGH);
}


