//= == == == == == == == == == == == == == == == == == == == == =
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
//****************************************************************/
// MCT1, SS2020 für TinkerCAD Tastenfeld
// Ziffernblock / Keypad einlesen J20 D24-D31
//*****************************************************************/

//-----E-Blocks ------------------------
#include "clKeyPad.h"
// Ziffernblock an J20 D24-D31
clKeyPad myPad();

//=========== globale Variablen =======================
char key, keyOld; //Tasten vom KeyPad
//--------------------------------------
void setup() {
  Serial.begin(9600); // Ausgabe an PC mit Baudrate 9600
  Serial.println("clKeypad MCT1"); //Begrüßung
}
void loop() {
  key = myPad.scanKeypad();  //Tasten abfragen
  
  // Nur auf Serial ausgeben, wenn neues Zeichen kommt
  if (key != '\0' && key != keyOld) {
    Serial.print(key);
    Serial.print(" ");
    if (key == 'D') Serial.println(" Nextline ");
  }
  keyOld = key;
  delay(2); //Zeitliche Entprellung, kann später bei längerer loop() entfallen
}
