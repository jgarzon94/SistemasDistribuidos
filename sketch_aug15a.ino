#include <b64.h>
#include <HttpClient.h>

#include <UIPEthernet.h> // Used for Ethernet

// **** ETHERNET SETTING ****
// Arduino Uno pins: 10 = CS, 11 = MOSI, 12 = MISO, 13 = SCK
// Ethernet MAC address - must be unique on your network - MAC Reads T4A001 in hex (unique in your network)
byte mac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };                                       
// For the rest we use DHCP (IP address and such)

//EthernetClient client;
int pinLed1 = 2;
int pinLed2 = 3;
int pinLed3 = 4;
int pinLDR = 0;
int valorLDR = 0; 
char server[] = { 192,168,0,101 }; // IP Adres (or name) of server to dump data to
int  interval = 5000; // Wait between dumps

void setup() {
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinLed3, OUTPUT);
  Serial.begin(9600);
  Ethernet.begin(mac);
  

 
}

void loop() {
 HttpClient client;
  
  
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("-> Connected");
   
  valorLDR= analogRead(pinLDR)/7;
  Serial.println(valorLDR);
   if(valorLDR > 80)
  {
    digitalWrite(pinLed1, HIGH);
  }
  if(valorLDR > 100)
  {
    digitalWrite(pinLed2, HIGH);
  }
  if(valorLDR > 120)
  {
    digitalWrite(pinLed3, HIGH);
  }
    // Make a HTTP request:
    client.get("http://192.168.0.101/user/mysql.php?valor=");
    client.get(valorLDR);
    client.get( " HTTP/1.1");
    client.stop();
  }
  else {
    // you didn't get a connection to the server:
    Serial.println("--> connection failed/n");
  }

  delay(interval);
}
