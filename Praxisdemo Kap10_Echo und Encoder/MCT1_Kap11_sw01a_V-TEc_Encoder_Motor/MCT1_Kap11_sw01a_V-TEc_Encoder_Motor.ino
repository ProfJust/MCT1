//==========================================
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
// MCT1, Version vom 27.4.2018
//--------------------------------------
// MCT1_Kap11_sw01a_V-TEC_Encoder Motor.ino
//-----E-Blocks ------------------------
// LED - Board an Jx  (D8-D15) +
// Power-Board an J20 (D24-D31) + Steckernetzteil 6V
// Motor V-Tec 6V VT-E-G25A-06-177E  110-170 U/min
//-------------------------------------------------------------
//--- Die Power-Board Kabel sind an folgende Pins gedrahtet ---
#define MO0 25
#define MO1 26
int OutPins[2] = {MO0, MO1};
enum MotorDirTyp {LEFT, RIGHT, STOP};
//--------------------------------------
void setup() {
  // Ports auf Ausgang setzen
  for (int i = 0; i < sizeof(OutPins); i++)  
    pinMode(OutPins[i], OUTPUT);
}
//--------------------------------------
void setMotor( MotorDirTyp dir){
  if ( dir == LEFT){
    digitalWrite(MO0, LOW);
    digitalWrite(MO1, HIGH);
  }
  else if ( dir == RIGHT){
    digitalWrite(MO0, HIGH);
    digitalWrite(MO1, LOW);
  }
  else{
    digitalWrite(MO0, LOW);
    digitalWrite(MO1, LOW);
  }
}
//--------------------------------------
void loop() {
 setMotor(LEFT);  
 delay(2000);
 setMotor(STOP);  
 delay(1000); 
 setMotor(RIGHT);  
 delay(3000);
 setMotor(STOP);  
 delay(5000); 
}
