//= == == == == == == == == == == == == == == == == == == ==
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
//***********************************************************/
// MCT1, 22.5.2019
// **********************************************************/
// sw04_I2C_DS1621_EEPROM.ino
//------------------------------------------
// DS1621 auslesen
// Speichern der Max-Werte im EEPROM
//========= Bibliotheken ===============
// Bib für I²C-Bus
#include <Wire.h>
#define DEV_ID 0x9e >> 1
#include <EEPROM.h>
//=========== globale Variablen =======================
uint8_t loopCnt = 0; // Zählt die Messungen
int tempC = 0;       // Tempertur in Celsius
int tempC_max;       // Variable to store in EEPROM.
int eeAddress = 5;   // Location we want the data to be put.

// ----   EEPROM und Integer -----------
//vgl. https://forum.arduino.cc/index.php?topic=100231.0
//This function will write a 2 byte integer to the eeprom at the specified address and address + 1
void EEPROMWriteInt(int p_address, int p_value){
  byte lowByte = ((p_value >> 0) & 0xFF);
  byte highByte = ((p_value >> 8) & 0xFF);

  EEPROM.write(p_address, lowByte);
  EEPROM.write(p_address + 1, highByte);
}

//This function will read a 2 byte integer from the eeprom at the specified address and address + 1
unsigned int EEPROMReadInt(int p_address){
  byte lowByte = EEPROM.read(p_address);
  byte highByte = EEPROM.read(p_address + 1);
  return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
}


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
  tempC_max = EEPROMReadInt( eeAddress); // Liest das EEPROM aus
  Serial.print("Maximalwert aus dem EEPROM ");
  Serial.println(tempC_max);
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

  if (tempC > tempC_max) {
    tempC_max = tempC;
    Serial.print("Neuer Maximalwert ins EEPROM ");
    Serial.println(tempC_max);
    EEPROMWriteInt(eeAddress, tempC_max); //Beschreibt das EEPROM
  }
}

