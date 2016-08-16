#include <UIPEthernet.h> // Librería Ethernet usada con el módulo ENC28J60

byte direccion_mac[]={0x12,0x34,0x56,0x78,0x9a,0xbc}; // Dirección MAC inventada
IPAddress direccion_ip_fija(192,168,0,2); // Dirección IP elegida para el módulo
IPAddress servidor_dns(8,8,8,8); // Servidor OpenNIC (de Alejandro Bonet, http://opennic.alargador.org)
IPAddress puerta_enlace(192,168,0,1); // Dirección IP del router
IPAddress mascara_red(255,255,255,0); // Máscara de la red
IPAddress server(200,9,176,48); // Dirección IP del servidor web (en la intranet)
//char url_servidor_web[]="sleepmanager.onironauta.es"; // URL poético para un gestor de sueño (en Internet)
EthernetClient client;
byte estado_conexion;
byte contador;

void setup()
{
  contador=0;
  Serial.begin(9600);
  while(!Serial){;} // Esperar al puerto serie de la placa Leonardo
  Serial.println("Conectando con el servidor SleepManager...");
  Ethernet.begin(direccion_mac,direccion_ip_fija,servidor_dns,puerta_enlace,mascara_red);
  Serial.println(Ethernet.localIP());
}

void loop()
{
  contador++;
 if (client.connect(server, 80)>0) {  // Conexion con el servidor
    client.print("GET /arduino/lectura.php?valor="); // Enviamos los datos por GET
    client.print(contador);
    client.println(" HTTP/1.0");
    client.println("User-Agent: Arduino 1.0");
    client.println();
    Serial.println("Conectado");
  } else {
    Serial.println("Fallo en la conexion");
  }
}
