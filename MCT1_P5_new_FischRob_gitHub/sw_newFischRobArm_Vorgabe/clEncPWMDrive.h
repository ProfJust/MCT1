/*
 * Westfaelischer Hochschule Campus Bocholt
 * MikroControllerTechnik 1 Tutorium 
 * Fischertechnik - Robotics in Industry
 * Gerald Hebinck, Mai 2019
 * 
 * Diese Klasse dient zur Ansteuerung eines einzelnen Antriebes mittels PWM.
 * ZusÃ¤tzlich kann ein Endschalter und Encoderwerte mit Limits zur Begrenzung verwendet werden. 
 * Die Encoderwerte mÃ¼ssen als Pointer Ã¼bergeben werden.
 * Des Weiteren ist es nÃ¶tig, setInit() zu rufen, damit der Antrieb in beide Richtungen gefahren werden kann.
 */

class clEncPWMDrive {
  private:
    int pin_plus;
    int pin_minus;
    int pin_enc;
    int pin_end;
    int pin_en;
    int limit_high;
    int limit_low;
    volatile int* enc_val;
    bool limits;
    bool init;

  public:
    clEncPWMDrive(int ipin[5], int ilimit[2], bool xlimits,  volatile int* penc_val);
    int directDrive(int value, int scale);
    void refDrive();
    void setInit() {
      init = HIGH;
    }
};

clEncPWMDrive::clEncPWMDrive(int ipin[5], int ilimit[2], bool xlimits,  volatile int* penc_val) {
  pin_plus = ipin[0];
  pin_minus = ipin[1];
  pin_enc = ipin[2];
  pin_end = ipin[3];
  pin_en = ipin[4];
  limit_high = ilimit[1];
  limit_low = ilimit[0];
  limits = xlimits;
  enc_val = penc_val;

  pinMode(pin_plus, OUTPUT);
  pinMode(pin_minus, OUTPUT);
  pinMode(pin_enc, INPUT_PULLUP);
  pinMode(pin_end, INPUT_PULLUP);

  digitalWrite( pin_plus, LOW);
  digitalWrite( pin_minus, LOW);
}

void clEncPWMDrive::refDrive() {
  digitalWrite(pin_minus, HIGH);
  digitalWrite(pin_plus, LOW);
  digitalWrite(pin_en, HIGH);
  while (!digitalRead(pin_end)) {
  }
  digitalWrite(pin_minus, LOW);
  digitalWrite(pin_plus, LOW);
  digitalWrite(pin_en, LOW);
}

int clEncPWMDrive::directDrive(int value, int scale ) {
  if (value > 15 && *enc_val < limit_high && init) {
    digitalWrite(pin_minus, LOW);
    analogWrite(pin_plus, (value * 255) / scale);
    digitalWrite(pin_en, HIGH);
    return 1;
  }
  else if (value < -15 && !digitalRead(pin_end) && (*enc_val > limit_low || init)) {
    digitalWrite(pin_plus, LOW);
    analogWrite(pin_minus, (-value * 255) / scale);
    digitalWrite(pin_en, HIGH);
    return -1;
  }
  else {
    digitalWrite(pin_plus, LOW);
    digitalWrite(pin_minus, LOW);
    digitalWrite(pin_en, LOW);
    return 0;
  }
}

