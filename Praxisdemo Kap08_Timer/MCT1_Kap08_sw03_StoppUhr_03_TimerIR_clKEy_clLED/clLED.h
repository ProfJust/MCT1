//****************************************************************/
/* Mikrocontrollertechnik MCT1                                   */
/* clLED.h                                                       */
/*****************************************************************/
//---- LED Output ----
class clLED {
  public:
    //--- Konstruktor ---
    clLED(int pin) {
      pinNr = pin;
      pinMode(pinNr, OUTPUT);
    }
    void on() {
      digitalWrite(pinNr, HIGH);
    }
    void off() {
      digitalWrite(pinNr, LOW);
    }
    void toggle() {
      digitalWrite(pinNr, !digitalRead(pinNr));
      if ( this->getState())
        this->on();  
      else
        this->off();
    }
    bool getState() {
      if (digitalRead(pinNr)) 
        return true;
      else
        return false;
    }
  private:
    int pinNr;
};
