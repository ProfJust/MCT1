//==========================================
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
// ELS III - SS16
//--------------------------------------
// V5_sw08_PWM_TimerOne_BSP.ino
//-----E-Blocks ------------------------
// Oszilloskop an D11 /D12

#include <TimerOne.h>
#define PinPWM 12   /* Timer 1 => Pin 11 oder 12 möglich*/
#define PWM_PERIOD 50 /* 50usec = 20 kHz */
int duty = 127;

void setup(){
  Serial.begin(9600);
  pinMode(PinPWM, OUTPUT);
  Timer1.initialize(1);            // Initialisierung auch für PWM, Wert ist dabei egal
  Timer1.pwm(PinPWM, duty, PWM_PERIOD);   // setup pwm on pin 9, 12,5% duty cycle 50usec = 20 kHz
}

void loop(){
  // Verändern des Tastverhätlnisses
 Timer1.setPwmDuty(PinPWM, 1000);
 delay(2000);
  Timer1.setPwmDuty(PinPWM, 1500);
   delay(2000);
// if(duty>=1023) 
Timer1.disablePwm(PinPWM); //Output auf LOW
 Serial.println(duty);
 delay(10);
}
