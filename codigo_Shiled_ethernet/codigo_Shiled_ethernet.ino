/*
 * Asterisk Controlling Arduino Example
 *
 * A basic example displaying the ability of Asterisk
 * open-source PBX to control an LED on an Arduino with
 * an ethernet shield.
 * 
 * Dan Wagoner
 * http://www.nerdybynature.com
 */

#include <Ethernet.h>

int LEDpin = 4; 
int luz ;
int lightPin = A0;
byte sensor = 3; 
int threshold = 640;  //LED set to pin 4
int x;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };    //must give WIZnet a MAC
byte ip[] = { 192, 168, 1, 160 }; 
byte server1[] = { 192, 168, 1, 129 };//must configure WIZnet IP
EthernetServer server = EthernetServer(23);               //TCP port the server is listening on
 EthernetClient client;                          //I'm using telnet, but you could use any
void setup()
{  Serial.begin(9600); 
  Ethernet.begin(mac, ip);
  server.begin();
    pinMode(3,INPUT);
  //Serial.begin(9600);   
   Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());//for troubleshooting purposes (not needed)
  pinMode(LEDpin, OUTPUT);
}

void loop () {
client = server.available();            //client connects to server

if (client){                   //if connection present
  x = client.read();                 //read information coming from server
  Serial.println(x);}                //print to serial (troublshooting only)
  
if (x == 0){                   //if information sent is a zero
  digitalWrite(LEDpin, LOW);}              //turn of LED
else if (x == 1){                      //if information sent is a one
  digitalWrite(LEDpin, HIGH);}             //turn on LED
else if (x == 2){                      //if information sent is a two
  digitalWrite(LEDpin, HIGH);              //blink the LED
  delay(500);
  digitalWrite(LEDpin, LOW);
  delay(500);}


 if (digitalRead(sensor) == HIGH){
  luz =1;
  if (client.connect(server1,80)) {
        /*
          Serial.println("Connected!");
          client.print("GET /call_sense.php?luz=");
          client.print(luz);
          client.println(" HTTP/1.1");
          client.println("User-Agent: Arduino 1.0");
          client.println("Host: 192.168.1.129");
          client.println();
          Serial.print("GET http://192.168.1.129/call_sense.php?luz=");
          Serial.print(luz);

*/
Serial.println("Connected!");
          client.print("GET /callsense.php?luz=");
    client.print(luz);    
    client.println(" HTTP/1.1");
    client.println("HOST: 192.168.1.129");
    client.println();
    Serial.print("GET /callsense.php?luz=");
    Serial.print(luz);
  





          
                                      }
           
           else 
           {
           Serial.println("Connection failed");
           client.stop();
           }
               
  }
  else {
    Serial.println("LOW");
    }
 
  delay(1000);
}
