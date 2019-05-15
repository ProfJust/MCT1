//===============================================
// ELS III - SS16
// V5_sw06_PWM_Lüfter
//---------------------------------------------
// LED/POWER-Board an D0-D7
// Zeigt LED-Dimmen durch PWM
//---------------------------------------------

//-------- Angeschlossen Hardware --------
 #define  PWM_PIN 8 //PWM_PIN an D8
 // On the Arduino Mega, PWM works on pins 2 - 13 and 44 - 46.
 
//---- Variablen  ----
   unsigned int  fade=50; // Duty-Cycle 0..255
   
//---- Initialisierung -----------------------
void setup(){
  //--- COM init ---
  Serial.begin(9600);
  //--- Ausgangspins -------
   pinMode(PWM_PIN,OUTPUT); //Nicht notwendig
}

void loop(){
  // -- neuen Duty-Cycle setzen --
   fade++;
   if(fade >=255) {
    fade = 50;   
    analogWrite(PWM_PIN, fade);   
    delay(3000); 
   }
 
  //-- LED - Ausgabe --
    analogWrite(PWM_PIN, fade);     
  // -- LCD Ausgabe ---
  Serial.println(fade); 
  delay(200);   
}

