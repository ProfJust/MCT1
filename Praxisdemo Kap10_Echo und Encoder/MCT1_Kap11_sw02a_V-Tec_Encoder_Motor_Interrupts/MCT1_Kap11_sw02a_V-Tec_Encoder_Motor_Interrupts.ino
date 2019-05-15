//==========================================
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
// MCT1, Version vom 29.04.2019
//--------------------------------------
// MCT1_Kap11_sw01_Fischertechnik Encoder Motor.ino
//-----E-Blocks ------------------------
// Power-Board an J20 (D24-D31) + Steckernetzteil 6V
// Motor V-Tec 6V VT-E-G25A-06-177E  110-170 U/min
//
// (J5) Encoder an D18 D19 => Interner Pullup erforderlich
// D-Sub-Stecker obere Reihe, 1+2 von Rechts 
// int_3 und int_2
// D16 ist Vcc für den Encoder
//----------------------------------------------------
//Power-Board Kabel sind an folgende Pins gedrahtet 
// Schraubklemme 2 (weiß) und 3 (rot)
#define MO0 27
#define MO1 26
#define ENCODER_PINA 18  //gelb
#define ENCODER_PINB 19  //grün
#define ENCODER_VCC  16  //blau

int OutPins[2] = {MO0, MO1};
enum MotorDirTyp {LEFT, RIGHT, STOP};
volatile int MotorCnt = 0;
char str[40];

void ISR_Encoder(){  //Ausgelöst durch Ch A
  //Ch B bestimmt Richtung
  if(digitalRead(ENCODER_PINB)== HIGH)
    MotorCnt++;  //RIGHT
  else 
    MotorCnt--;  //LEFT
}
//--------------------------------------
void setup() {
  // SpeiseSpannung Encoder einschalten
    pinMode(ENCODER_VCC, OUTPUT);
    digitalWrite(ENCODER_VCC, HIGH);
  //Encoder Interrupt 
    pinMode(ENCODER_PINA, INPUT);
    pinMode(ENCODER_PINB, INPUT);
    //--- Fallende Flanke vom Encoder => ISR
    attachInterrupt(digitalPinToInterrupt(ENCODER_PINA), ISR_Encoder, FALLING);

  // Ports auf Ausgang setzen
  for (int i = 0; i < sizeof(OutPins); i++)  
    pinMode(OutPins[i], OUTPUT);

  Serial.begin(9600);
  delay(1000);
  Serial.println("Encodersignale vom Motor erfassen ");
  MotorCnt = 0;
  
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
 delay(2000);
 
 setMotor(STOP);  
 sprintf(str,"MotorCnt RIGHT: %04d time:%04d",MotorCnt,millis());
 Serial.println(str);
  Serial.println("-------------------");
 delay(5000); 
}
