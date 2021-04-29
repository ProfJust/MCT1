//= == == == == == == == == == == == == == == == == == == == == =
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
//****************************************************************/
// MCT1
// Nutze clKey - Klasse für Tasten mit Flankenevent
//*****************************************************************/
//-----E-Blocks ------------------------
//Combo-Board an A0-A7 und D0-D7

#include "clKey.h"

//Instanziierung des Objektes Taste1 der Klasse clKey mit Übergabe des Anschluss-Pins
clKey Taste_SA2(A2); 
clKey Taste_SA3(A3); 
clKey Taste_Hugo(A4); 
clKey BertaKey(A5); 

//--------------------------------------
void setup() {
  Serial.begin(9600); // zu Debug-Zwecken
  Serial.println("class clKey MCT1 - Tasten SA2-SA5");
}

//--------------------------------------
void loop() {
  if(Taste_SA2.readKey()== HIGH) Serial.println("Taste SA2");
  if(Taste_SA3.readKey()== HIGH) Serial.println("Taste SA3");
  if(Taste_Hugo.readKey()== HIGH) Serial.println("Hugo Taste");
  if(BertaKey.readKey()== HIGH) Serial.println("BertaKEy");
  delay(2);
}

