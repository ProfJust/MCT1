///==========================================
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
// MCT1, Version vom 8.6.2018
//--------------------------------------
// P4_sw01_I2C_Nunchuk_Class.ino
// Klasse zum lesen aus dem WII-Nunchuk nutzen
//-----E-Blocks ------------------------
// Nunchuk an J3 (D8-D15) wegen I2C
//----------------------------------------------------
 #include "clNunchuk.h"
 #define BAUD_RATE 115200
 char comStr[50];
  
  //Klasse instanzieren
 Nunchuk mychuk;
 
 void setup() {
	 Serial.begin(BAUD_RATE);
	 mychuk.initializeI2C();
 }

 void loop() {
	 mychuk.request_data(); // Bitte um Bereitstellung der Daten
	 mychuk.getdata();      // Daten abholen
	 
	 //Daten auswerten und ausgeben
		sprintf(comStr,"\n Joy %+04d %+04d",mychuk.joy_x(),mychuk.joy_y());
		Serial.print(comStr);
		sprintf(comStr,"  Acc %+04d %+04d %+04d",mychuk.acc_x(),mychuk.acc_y(),mychuk.acc_z());
		Serial.print(comStr);		
		sprintf(comStr,"  Button z %d c %d ",mychuk.butt_z(),mychuk.butt_c());
		Serial.print(comStr);
		
	 delay(200);
 }
