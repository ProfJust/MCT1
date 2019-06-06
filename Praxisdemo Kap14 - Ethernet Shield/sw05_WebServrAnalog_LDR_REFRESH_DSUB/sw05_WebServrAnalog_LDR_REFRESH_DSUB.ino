//==========================================
// Westfälische Hochschule - FB Maschinenbau
// Prof. Dr.-Ing. Olaf Just
// ELS III - SS16
//------------------------------------------
//sw04_WebServrAnalog_LDR_REFRESH.ino
// Zeigt Ziffernblock
// Liest Ziffernfolge ein
// Kontrollausgabe über Serial-Monitor
//-----E-Blocks ----------------------------
// Ethernet-Shield
// Sensor Board mit Poti an A8-A15 (J4) A8=> LDR
//------------------------------------------
#include <SPI.h>
#include <Ethernet.h>

byte MACAddress[] = { 0x90, 0xA2, 0xDA, 0x0F, 0xAD, 0xCA }; // MAC-Adresse Eth-Sh No.05
byte IPAddress[] = {192, 168, 1, 177}; // IP-Adresse des Shields
int const HTTPPORT = 80;                 // HTTP-Port 80 (Standardport), 9998 bei Portmapping für weltweiten Zugriff
String barColor[] = {"ff0000", "00ff00", "00ffff",
                     "ffff00", "ff00ff", "550055"}; // RGB-Farben für Color-Bars
#define HTML_TOP    "<html>\n<head><title>Arduino Web-Server</title></head>\n <meta http-equiv=\"refresh\" content=\"1\"> <body>"
#define HTML_BOTTOM "</body>\n</html>"
EthernetServer myServer(HTTPPORT); // Web-Server auf angegebenen Port starten

void setup() {
  Ethernet.begin(MACAddress, IPAddress); // Ethernet initialisieren
  myServer.begin();                      // Server starten
}

void loop() {
  EthernetClient myClient = myServer.available();
  if(myClient){
    myClient.println("HTTP/1.1 200 OK");
    myClient.println("Content-Type: text/html");
    myClient.println();    
    myClient.println(HTML_TOP);     // HTML-Top
    showValues(myClient);           // HTML-Content
    myClient.println(HTML_BOTTOM);  // HTML-Bottom  
  }
  delay(1);        // Kurze Pause für Web-Browser
  myClient.stop(); // Client-Verbindung schließen
}
#define POTI A1
void showValues(EthernetClient &myClient) {
  //for(int i = 0; i < 6; i++){
  int LDR_value = analogRead(POTI);
    myClient.print("POTI ");
    //myClient.print(i); 
    myClient.print(": "); 
    myClient.print(LDR_value ); 
    myClient.print("<div style=\"height: 15px; background-color: #");
    myClient.print(barColor[1]);
    myClient.print("; width:");
    myClient.print(LDR_value );
    myClient.println("px; border: 2px solid;\"></div>");
  //}
}
