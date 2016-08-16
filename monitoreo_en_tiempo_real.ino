#include <enc28j60.h>
#include <EtherCard.h>
#include <net.h>



// This is a demo of the RBBB running as webserver with the Ether Card
// 2010-05-28 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php



//EthernetClient client;
char server[] = "192.168.0.101";


// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
//int led = 13;
int pinLed1 = 2;
int pinLed2 = 3;
int pinLed3 = 4;
int pinLDR = 0;
int valorLDR = 0; 

//static byte server[]= {192, 168, 1, 140};



// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
static byte myip[] = { 192,168,0,150 };
//EthernetClient client;

byte Ethernet::buffer[500];
BufferFiller bfill;

void setup () {

// initialize the digital pin as an output.
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinLed3, OUTPUT);
  Serial.begin(9600);
  
  //pinMode(led, OUTPUT);


  
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
    Serial.println(F("Failed to access Ethernet controller"));
  ether.staticSetup(myip);
}

static word homePage() {


  digitalWrite(pinLed1, LOW);
  digitalWrite(pinLed2, LOW);
  digitalWrite(pinLed3, LOW);
  valorLDR= analogRead(pinLDR)/7;
  Serial.println(valorLDR);  
  
//  if (client.connect(server, 80)) {
  //  Serial.println("connected");
    // Make a HTTP request:
   // client.print("GET /user/mysql.php?valor=");
  //  client.print(valorLDR);
   // client.println(" HTTP/1.0");
     
   // client.println();
  //} 
  //else {
    // kf you didn't get a connection to the server:
    //Serial.println("connection failed");
  //}
//}
 
  


  
  //long t = millis() / 1000;
  //word h = t / 3600;
  //byte m = (t / 60) % 60;
  //byte s = t % 60;
  bfill = ether.tcpOffset();
  bfill.emit_p(PSTR(
    "HTTP/1.0 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Pragma: no-cache\r\n"
    "\r\n"
    "<meta http-equiv='refresh' content='1'/>"
    "<h1>SISTEMA DE MONITOREO v1.0</h1> <h1>$D</h1>"),  valorLDR);
  
  return bfill.position();

}

void loop () {
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
  
  delay(100);  
   
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  
  if (pos)  // check if valid tcp data is received

    ether.httpServerReply(homePage()); // send web page data

}
