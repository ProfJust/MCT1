/*
  Repeating WiFi Web Client

 This sketch connects to a a web server and makes a request
 using a WiFi equipped Arduino board.

 created 23 April 2012
 modified 31 May 2012
 by Tom Igoe
 modified 13 Jan 2014
 by Federico Vanzati

 http://www.arduino.cc/en/Tutorial/WifiWebClientRepeating
 This code is in the public domain.
 */
//-----------------------------------------------------------------------------------------------
 // changed to connect Arduino-Wifi with MySQL-DB
 // by OJ 18.3.2021

#include <SPI.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key index number (needed only for WEP)

int status = WL_IDLE_STATUS;

// Initialize the WiFi client library
WiFiClient client;

// server address:
//IP-Adress of XAMPP-Server in local network
IPAddress server(192,168,1,142);  

// The Data to put in meineDB
float humidity=0, temperature=111;            

// Timing Control
unsigned long lastConnectionTime = 0;   // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds

//-----------------------------------------------------------------------------------------------
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // check if WiFi module is there:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.print("Please upgrade the firmware from ");
    Serial.print(fv);
    Serial.print(" to Version ") ;
    Serial.println(WIFI_FIRMWARE_LATEST_VERSION);
  }
  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  // you're connected now, so print out the status:
  printWifiStatus();
}
//-----------------------------------------------------------------------------------------------
void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
  // ------ Every 10sec => send Reguest ------------
  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }
}

//-----------------------------------------------------------------------------------------------
// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the NINA module
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println(" ");
    Serial.println("-> connection established -  sending values to DB");
    Serial.println(" ");
  // Browserzeile funktionier so: http://192.168.1.142/myPage4SQL/meineDB_write.php?hum=0.00&temp=112.3

  // HTTP request  call certain url and send data using GET
  // vgl. https://www.php-einfach.de/php-tutorial/_get-und-_post/
  
    client.print("GET /myPage4SQL/meineDB_write.php?hum=");  // HTTP request  call certain url and send data using GET
    Serial.print("GET /myPage4SQL/meineDB_write.php?hum="); 
    client.print(humidity);  // HTTP request  send humidity
    Serial.print(humidity); 
    client.print("&temp=");                
    Serial.print("&temp=");                
    client.print(temperature);  // HTTP request  send temperature
    Serial.print(temperature++);  
    client.println(" HTTP/1.1");
    Serial.println(" HTTP/1.1");
    client.println("Host: 192.168.1.142");  // Server auf dem XAMPP PC

    //============ WICHTIG ! 2 x  Connection Close ===========
    client.println("Connection: close");   // HTTP request  close connection      
    client.println();                      // HTTP request  clear
    client.println("Connection: close");          
    client.println();          
    //============ WICHTIG ! 2 x  Connection Close ===========
    
    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("Arduino's IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
