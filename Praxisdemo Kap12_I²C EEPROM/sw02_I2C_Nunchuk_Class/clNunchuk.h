//==========================================
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
// MCT1, Version vom 8.6.2018
//--------------------------------------
// clNunchuk.h
// Klasse zum lesen aus dem WII-Nunchuk
//-----E-Blocks ------------------------
// Nunchuk an J3 (D8-D15) wegen I2C
//----------------------------------------------------
#include "Arduino.h"
#include <Wire.h>
#define NUNCHUK_DEVICE_ID 0x52   //I�C-Bus Adresse des Nunchuk
#define NUNCHUK_BUFFER_SIZE 6    //Nunchuk Daten/Anzahl der Bytes 
//--- Offsets f�r die Daten ---
#define JOY_X_OFFSET -128
#define JOY_Y_OFFSET -131
#define ACC_X_OFFSET -500
#define ACC_Y_OFFSET -488
#define ACC_Z_OFFSET -724
//--- Klasse zum lesen aus dem WII-Nunchuk -------
class Nunchuk {
  public:
    //Konstruktor
    Nunchuk() {
      //I2C im Konstruktor Initialisieren funktioniert nicht
//      Wire.begin();
//      Wire.beginTransmission(NUNCHUK_DEVICE_ID);
//      Wire.write(0x40);
//      Wire.write(0x00);
//      Wire.endTransmission();
//      this->getdata();
    }
    void initializeI2C();    // Initialisieren I2C
    void request_data();  // Nunchuk startet Messung
    bool getdata();		  // Daten vom Nunchuk holen
    int joy_x();          // Joystick X-Achse -128...127
    int joy_y();		  // Joystick Y-Achse -128...127
    int acc_x();		  // Beschleunigung X,Y,Z-Achse
    int acc_y();	      // 10-Bit Werte -512...+512
    int acc_z();
    bool butt_z();        // Taste Z bzw. C bet�tigt?
    bool butt_c();

  private:
    // Rohdaten vom Nunchuk entschl�sseln
    unsigned char decode_byte(const char);
    // privater Speicher f�r die Bytes
    unsigned char buffer[NUNCHUK_BUFFER_SIZE];
};

//--- Die Methoden der Klasse -------
int Nunchuk::acc_x()  {
  int acc_x = (int)(this->buffer[2] << 2) | ((this->buffer[5] >> 2) & 0x03);
  return (ACC_X_OFFSET + acc_x);
}
int Nunchuk::acc_y()  {
  int acc_y = (int)(this->buffer[3] << 2) | ((this->buffer[5] >> 4) & 0x03);
  return (ACC_Y_OFFSET + acc_y);
}
int Nunchuk::acc_z()  {
  int acc_z = (int)(this->buffer[4] << 2) | ((this->buffer[5] >> 6) & 0x03);
  return (ACC_Z_OFFSET + acc_z);
}

int Nunchuk::joy_x() {
  return (int) this->buffer[0] + JOY_X_OFFSET;
}
int Nunchuk::joy_y() {
  return (int) this->buffer[1] + JOY_Y_OFFSET;
}

bool Nunchuk::butt_z() {
  return !(this->buffer[5] & 0x01);
}
bool Nunchuk::butt_c() {
  return !(this->buffer[5] & 0x02);
}

void Nunchuk::initializeI2C() {
  Wire.begin();
  Wire.beginTransmission(NUNCHUK_DEVICE_ID);
  Wire.write(0x40);
  Wire.write(0x00);
  Wire.endTransmission();
  this->getdata();
}

bool Nunchuk::getdata() {
  int cnt = 0;
  delay(1);
  Wire.requestFrom(NUNCHUK_DEVICE_ID, NUNCHUK_BUFFER_SIZE);
  while (Wire.available()) {
    if (cnt < NUNCHUK_BUFFER_SIZE) {
      this->buffer[cnt] = decode_byte(Wire.read());
    }
    cnt++;
  }
  if (cnt == NUNCHUK_BUFFER_SIZE)
    return true;
  else
    return false;
}

void Nunchuk::request_data() {
  Wire.beginTransmission(NUNCHUK_DEVICE_ID);
  Wire.write(0x00);
  Wire.endTransmission();
}

// Rohdaten vom Nunchuk entschl�sseln
// vgl.  http://www.cc-zwei.de/wiki/index.php?title=Wii-Nunchuk_Hintergrundwissen&redirect=no

unsigned char Nunchuk::decode_byte(const char byte) {
  return (byte ^ 0x17) + 0x17;
}
