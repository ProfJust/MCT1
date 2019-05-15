//==========================================
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
// MCT1, Version vom 7.5.2018
//--------------------------------------
// MCT1_Kap11_sw01_Fischertechnik Encoder Motor.ino
//-----E-Blocks ------------------------
// LED - Board an Jx  (D8-D15) + Power-Board + Motor
// Encoder an D18 => Interner Pullup erforderlich
// D-Sub-Stecker obere Reihe, 2 von Rechts
//----------------------------------------------------
//Power-Board Kabel sind an folgende Pins gedrahtet 
#define MO0 10
#define MO1 11
#define ENCODER_PIN0 18   //D-Sub obere Reihe Mitte
int OutPins[2] = {MO0, MO1};
enum MotorDirTyp {LEFT, RIGHT, STOP};
volatile int MotorCnt = 0;
char str[40];

void ISR_Encoder(){
  MotorCnt++;
}
//--------------------------------------
void setup() {
    pinMode(ENCODER_PIN0, INPUT_PULLUP);
    //--- Fallende Flanke vom Encoder => ISR
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN0), ISR_Encoder, FALLING);

  // Ports auf Ausgang setzen
  for (int i = 0; i < sizeof(OutPins); i++)  
    pinMode(OutPins[i], OUTPUT);

  Serial.begin(9600);
  Serial.println("Encodersignale vom Motor erfassen ");
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
 sprintf(str,"MotorCnt LEFT: %04d time:%04d",MotorCnt,millis());
 Serial.println(str);
 delay(1000); 
 
 setMotor(RIGHT);  
 delay(3000);
 
 setMotor(STOP);  
 sprintf(str,"MotorCnt RIGHT: %04d",MotorCnt);
 Serial.println(str);
 delay(5000); 
}
