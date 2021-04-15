// MCT1
// MCT1_Kap04_Demo01_TastenPolling.ino
// Version vom 28.3.2019
//-------------------------------------
// LED - Board an J5 (D16 -D23)
// Tast - Board an J3 (D8-D15)
//-------------------------------------
const int LED_PIN = 23; // LED LA7 an D23
const int BTN_PIN = 15;   // pushbutton SB7 an D8

//--- Zustandsspeicher (kein bool da   int digitalRead() )
int btnState = HIGH;
int ledState = HIGH;

void setup()
{
  pinMode(LED_PIN, OUTPUT);      // sets the digital pin 13 as output
  pinMode(BTN_PIN, INPUT);      // sets the digital pin 7 as input
}

void loop()
{
  // --- Eingabe erfassen ---
  btnState = digitalRead(BTN_PIN);   // read the input pin
  
  // --- Verarbeitung ---
  // Eingabe = Ausgabe
  ledState = btnState; 

  // --- Ausgabe ---
  digitalWrite(LED_PIN, ledState);
  delay(2); //zeitliche Entprellung
}
