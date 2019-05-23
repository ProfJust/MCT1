//= == == == == == == == == == == == == == == == == == == ==
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
//***********************************************************/
// MCT1, 7.5.2018
// **********************************************************/
// sw01_I2C_DS1621.ino
// DS1621 auslesen
//========= Bibliotheken ===============
// Bib für I²C-Bus
#include <Wire.h>
#define DEV_ID 0x9e >> 1

//=========== globale Variablen =======================
uint8_t loopCnt = 0; // Zählt die Messungen
int tempC = 0;    // Tempertur in Celsius

void setup() {
  //Ausgabe über Serielle Schnitstelle => Monitor
  Serial.begin(115200);
  Serial.println("Arduino liest DS1621");

  //I2C initialisieren
  Wire.begin();
  Wire.beginTransmission(DEV_ID);           // connect to DS1621 (#0)
  Wire.write(0xAC);                   // Access Config  -> Datasheet
  Wire.write(0x02);                  // set for continuous conversion
  Wire.beginTransmission(DEV_ID);           // restart
  Wire.write(0xEE);                         // start conversions
  Wire.endTransmission();
}


void loop() {
  delay(1000);                          // give time for measurement

  //I2C-Messung abholen
  Wire.beginTransmission(DEV_ID);
  Wire.write(0xAA);                          // read temperature
  Wire.endTransmission();
  Wire.requestFrom(DEV_ID, 1);        // request one byte from DS1621
  tempC = Wire.read();                // get whole degrees reading

  //Ausgabe COM-Port
  Serial.print(loopCnt++, DEC);
  Serial.print(".Messung: ");
  Serial.print(tempC);
  Serial.println(" Grad Celsius ");
}

