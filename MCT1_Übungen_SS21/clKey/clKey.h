//= == == == == == == == == == == == == == == == == == == == == =
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
//****************************************************************/
// MCT1
// Klasse für Tasten mit Flankenevent
// clKey.h
// github MCT1 
//*****************************************************************/

class clKey {
  public:
    //Konstruktor => keyPin
    clKey(const uint8_t pin) {
      keyPin = pin;
      pinMode(keyPin, INPUT);
    }
    bool readKey();

  private:
    uint8_t keyPin;  //im Konstruktor setzen
    int keyState;
    bool keyEdgeFlag;
};

bool clKey::readKey() {
  keyState = digitalRead(keyPin);
  if (keyState == LOW) keyEdgeFlag  = false;
  if (keyState == HIGH && keyEdgeFlag == false) {
    keyEdgeFlag = true; //Verriegeln
    return true;
  }
  return false;
}
