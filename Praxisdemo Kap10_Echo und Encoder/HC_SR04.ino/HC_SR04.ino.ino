//= == == == == == == == == == == == == == == == == == == =
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
//********************************************************/
// MCT1, 15.5.2019
// 
// Testprogramm für den HC-SR04 - Echo-Sensor
//********************************************************/
// HC_SR04.ino
//-----E-Blocks ----------------------------------------
// Echo Sensor an Pin 24 und 25
//-------------------------------------------------------
const int trigPin = 24; //D-SUB J20 Buchse 1
const int echoPin = 25; //D-SUB J20 Buchse 2

long int duration, cm, mm;
//-----------------------------------------------------
void setup() {
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
}
//-----------------------------------------------------
//--- Erzeugen eines Start-Pulses für den Echo_Sensor ---
void startPulse(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); 
}
//-----------------------------------------------------
void loop(){
  startPulse(); // Schall senden
  duration = pulseIn(echoPin, HIGH); // Pulsdauer messen

  // convert the time into a distance
  // The speed of sound is 340 m/s or 29 microseconds per centimeter
  cm = duration / 29 / 2;
  mm = duration * 10000 / 29155 /2;
  
  Serial.print(cm);
  Serial.print("cm ");
  Serial.print(mm);
  Serial.print("mm");
  Serial.println();  
  delay(100);
}
