/*
 * Praxisdemo 04 ADC Poti LDR_fast.ino
 *
 * Created: 10/2/2014 4:13:55 PM
 * Author: olafj_000
 -------------------------------------------
 # LCD an J3 (D0-D7)
 # Sensor Board EB003 an J1 (A0-A7)
 ------------------------------------------
 */ 

#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
	//                RS EN D4 D5 D6 D7
		LiquidCrystal lcd(4, 5, 0, 1, 2, 3); //J2
	
//=========== globale Variablen =======================
	char str[17]; //String fuer LCD Ausgabe

// AD-Wandler- Eingaenge
	const int sensorPinLDR  = A0;    // input pin for the LDR
	const int sensorPinPoti = A1;    // input pin for the potentiometer
// variable to store the value coming from the sensor
	int sensorValueLDR  = 0;
	int sensorValuePoti = 0;

//==============================================
void setup() {
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
	lcd.setCursor(0, 0);
	lcd.write("ELS - Sensor");
	lcd.setCursor(0, 1);
	lcd.print("25.April 2019");
	delay(1000);
  lcd.clear();
  Serial.begin(115200);
  Serial.println("ADC");
}
//==============================================
void loop() {
	//-- Einlesen --
		// read the value from the sensor:
		sensorValuePoti = analogRead(sensorPinPoti);
		sensorValueLDR  = analogRead(sensorPinLDR);
	//-- Verarbeiten --
		
	//-- Ausgeben --
   //----- Print auf der seriellen Schnittstelle ----
   // Schnelle Version mit wenig Zeichen
  String strTx; //String fuer LCD Ausgabe
  strTx = "Time: "+String(millis())+ " LDR: " + String(sensorValueLDR);
   
   //sprintf(strTx,"Time: %06d LDR: %04d", millis(),sensorValuePoti);
  Serial.println(strTx);
  
}



