#include <SPI.h>
#include <Ethernet.h>

byte MACAddress[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x4A, 0x60 }; // MAC-Adresse /*4*/ 
byte IPAddress[]= {192, 168, 1, 177}; // IP-Adresse, hier als Byte-Array !!
int const HTTPPORT = 80;                 // HTTP-Port 80 (Standardport), 9998 bei Portmapping für weltweiten Zugriff
String barColor[] = {"ff0000", "00ff00", "00ffff",
                     "ffff00", "ff00ff", "550055"}; // RGB-Farben für Color-Bars
// /*mit Refresh*/ #define HTML_TOP    "<html>\n<head><title>Arduino Web-Server</title></head>\n <meta http-equiv=\"refresh\" content=\"1\"> <body>"
#define HTML_TOP    "<html>\n<head><title>Arduino Web-Server</title></head>\n<body>"
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

void showValues(EthernetClient &myClient) {
  for(int i = 0; i < 6; i++){
    myClient.print("Analog Pin ");
    myClient.print(i); 
    myClient.print(": "); 
    myClient.print(analogRead(i)); //+ rand()%100); //incl. Zufall
    myClient.print("<div style=\"height: 15px; background-color: #");
    myClient.print(barColor[i]);
    myClient.print("; width:");
    myClient.print(analogRead(i));
    myClient.println("px; border: 2px solid;\"></div>");
  }
}
