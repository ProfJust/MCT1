/*
   Westfaelischer Hochschule Campus Bocholt
   MikroControllerTechnik 1 Tutorium
   Fischertechnik - Robotics in Industry
   Gerald Hebinck, Mai 2019

   Diese Klasse implementiert die Kommunikation mit einem Wii Nunchuck.
   Die Klasse Wire muss im rufenden Programm inkludiert und gestartet werden.

   Mit begin() wird die Kommunikation initialisiert und mit update() werden
   aktuelle Daten vom Nunchuck uebertragen.

   This Class is based on:
   https://github.com/timtro/wiinunchuck-h
   File  : wiinunchuk.h V0.9
   Author: Tim Teatro
*/


class clNunchuck {
  
  public:
    clNunchuck();
    void begin();
    int update();
    unsigned int button_z();
    unsigned int button_c();
    int ucjoy_x();
    int ucjoy_y();
    int cjoy_x();
    int cjoy_y();
    uint16_t ucaccel_x();
    uint16_t ucaccel_y();
    uint16_t ucaccel_z();
    int caccel_x();
    int caccel_y();
    int caccel_z();
    int joy_angle();
    int rollangle();
    int pitchangle();
    void calibrate_joy();
    void calibrate_accelx();
    void calibrate_accely();
    void calibrate_accelz();

  private:

    // Default Calibration Values
    const uint8_t def_centre_joy_x = 124;
    const uint8_t def_centre_joy_y = 132;
    const uint16_t def_accel_zero_x = 490;
    const uint16_t def_accel_zero_y = 500;
    const uint16_t def_accel_zero_z = 525;

    // Keeps data payload from nunchuk
    uint8_t nunchuk_buf[6];

    // Accelerometer values and callibration centres:
    uint16_t accel_zerox, accel_zeroy, accel_zeroz;

    // Joystick values and calibration centres:
    int joy_x, joy_y, joy_zerox, joy_zeroy;

    char nunchuk_decode_byte (char x);
};


// Constructor sets default calibration data
clNunchuck::clNunchuck() {
  joy_zerox = def_centre_joy_x;
  joy_zeroy = def_centre_joy_y;
  accel_zerox = def_accel_zero_x;
  accel_zeroy = def_accel_zero_y;
  accel_zeroz = def_accel_zero_z;
}

// Initialize and join the I2C bus, and tell the nunchuk we're
// talking to it. This function will work both with Nintendo
// nunchuks, or knockoffs.

void clNunchuck::begin()
{
  delay(1);
  Wire.beginTransmission(0x52);  // device address
  Wire.write((uint8_t)0xF0);  // 1st initialisation register
  Wire.write((uint8_t)0x55);  // 1st initialisation value
  Wire.endTransmission();
  delay(1);
  Wire.beginTransmission(0x52);
  Wire.write((uint8_t)0xFB);  // 2nd initialisation register
  Wire.write((uint8_t)0x00);  // 2nd initialisation value
  Wire.endTransmission();
  delay(1);
}

// Gets data from the nunchuk and packs it into the nunchuk_buff byte
// array. That array will be processed by other functions to extract
// the data from the sensors and analyse.

int clNunchuck::update() {
  int cnt = 0;
  Wire.beginTransmission(0x52);// transmit to device 0x52
  Wire.write((uint8_t)0x00);// sends one byte
  Wire.endTransmission();// stop transmitting
  delay(1);
  // Request six bytes from the chuck.
  Wire.requestFrom (0x52, 6);
  while (Wire.available ()) {
    nunchuk_buf[cnt] = Wire.read();
    cnt++;
  }
  if (cnt >= 5) {
    return 1;   // success
  }
  begin();
  return 0;     // failure
}

// Returns c and z button states: 1=pressed, 0=not
// The state is in the two least significant bits of the 6th byte.
// In the data, a 1 is unpressed and 0 is pressed, so this will be
// reversed. These functions use a bitwise AND to determine the value
// and then the () ? true : false; conditional structure to pass out
// the appropriate state.

unsigned int clNunchuck::button_z() {
  return ((nunchuk_buf[5] >> 0) & 1) ? 0 : 1;
}

unsigned int clNunchuck::button_c() {
  return ((nunchuk_buf[5] >> 1) & 1) ? 0 : 1;
}

// Returns the raw x and y values of the the joystick, cast as ints.

int clNunchuck::ucjoy_x() {
  return (int)nunchuk_buf[0];
}
int clNunchuck::ucjoy_y() {
  return (int)nunchuk_buf[1];
}

// Return calibrated x and y values of the joystick.

int clNunchuck::cjoy_x() {
  return (int)nunchuk_buf[0] - joy_zerox;
}

int clNunchuck::cjoy_y() {
  return (int)nunchuk_buf[1] - joy_zeroy;
}


// Returns the raw 10-bit values from the 3-axis accelerometer sensor.
// Of the six bytes recieved in a data payload from the nunchuk, bytes
// 2, 3 and 4 are the most significant 8 bits of each 10-bit reading.
// The final two bits are stored in the 6th bit along with the states
// of the c and z button. These functions take the most significant
// 8-bits and stacks it into a 16 bit unsigned integer, and then tacks
// on the least significant bits from the 6th byte of the data
// payload.
//
// Load the most sig digits into a blank 16-bit unsigned int leaving
// two bits in the bottom ( via a 2-bit shift, << 2) for the least sig
// bits:
//  0x0000 | nunchuk_buff[*] << 2
// Add to the above, the least sig bits. The code for x:
//  nunchuk_buf[5] & B00001100
// for example selects the 3rd and 4th bits from the 6th byte of the
// payload to be concatinated with nunchuk_buff[2] to complete the 10-
// bit datum for a given axis.
//
uint16_t clNunchuck::ucaccel_x() {
  return (  0x0000 | ( nunchuk_buf[2] << 2 ) +
            ( ( nunchuk_buf[5] & B00001100 ) >> 2 )  );
}

uint16_t clNunchuck::ucaccel_y() {
  return (  0x0000 ^ ( nunchuk_buf[3] << 2 ) +
            ( ( nunchuk_buf[5] & B00110000 ) >> 4 )  );
}

uint16_t clNunchuck::ucaccel_z() {
  return (  0x0000 ^ ( nunchuk_buf[4] << 2 ) +
            ( ( nunchuk_buf[5] & B11000000 ) >> 6 )  );
}

// Returns the x,y and z accelerometer values with calibration values
// subtracted.
int clNunchuck::caccel_x() {
  return (int)(ucaccel_x() - accel_zerox);
}

int clNunchuck::caccel_y() {
  return (int)(ucaccel_y() - accel_zeroy);
}

int clNunchuck::caccel_z() {
  return (int)(ucaccel_z() - accel_zeroz);
}

// Returns joystick angle in degrees. It uses the ratio of calibrated
// x and y potentiometer readings to find the angle, zero being direct
// right (positive x) and measured counter-clockwise from there.
//
// If the atan2 function returns a negative angle, it is rotated back
// into a positive angle. For those unfamiliar, the atan2 function
// is a more intelligent atan function which quadrant the vector <x,y>
// is in, and returns the appropriate angle.
//
int clNunchuck::joy_angle() {
  double theta;
  theta = atan2( cjoy_y(), cjoy_x() );
  while (theta < 0) theta += 2 * M_PI;
  return (int)(theta * 180 / M_PI);
}

// Returns roll angle in degrees. Under the assumption that the
// only acceleration detected by the accelerometer is acceleration due
// to gravity, this function uses the ratio of the x and z
// accelerometer readings to gauge pitch. This only works while the
// nunchuk is being held still or at constant velocity with zero ext-
// ernal force.
//
int clNunchuck::rollangle() {
  return (int) (  atan2( (double) caccel_x(),
                         (double) caccel_z() ) * 180 / M_PI  );
}


// Returns pitch angle in degrees. Under the assumption that the
// only acceleration detected by the accelerometer is acceleration due
// to gravity, this function uses the ratio of the y and z
// accelerometer readings to gauge pitch.  This only works while the
// nunchuk is being held still or at constant velocity with zero ext-
// ernal force.
//
int clNunchuck::pitchangle() {
  return (int) (  atan2( (double) caccel_y(),
                         (double) caccel_z() ) * 180 / M_PI  );
}

// Calibrate joystick so that we read the centre position as (0,0).
// Otherwise, we use the default values from the header.

void clNunchuck::calibrate_joy()
{
  joy_zerox = joy_x;
  joy_zeroy = joy_y;
}

// Because gravity pulls down on the z-accelerometer while the nunchuk
// is upright, we need to calibrate {x,y} and {z} separately. Execute
// this function while the nunchuk is known to be upright and then
// execute nunchuk_calibrate_accelz() when the nunchuk is on its side.

void clNunchuck::calibrate_accelx() {
  accel_zerox = ucaccel_x();
}
void clNunchuck::calibrate_accely() {
  accel_zeroy = ucaccel_y();
}
void clNunchuck::calibrate_accelz() {
  accel_zeroz = ucaccel_z();
}

// Standard nunchuks use a byte-wise encryption using bit-wise XOR
// with 0x17. This function decodes a byte.
//
// This function is not needed since the way we initialize the nunchuk
// does not XOR encrypt the bits.
char clNunchuck::nunchuk_decode_byte (char x) {
  x = (x ^ 0x17) + 0x17;
  return x;
}

