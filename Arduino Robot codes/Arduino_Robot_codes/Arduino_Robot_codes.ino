#include <SPI.h>
#include <Ethernet.h>
#include "DHT.h"

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10,0,2,199);
IPAddress gateway(10,0,0,1);
IPAddress subnet(255, 255, 240, 0);
IPAddress mydns(8,8,8,8);

//variable for send data
int sunval;
int frameval;
int tempval;
int humival;
int soilval;

// initialize the library instance:
EthernetClient client;

char server[] = "10.0.2.165";

int sunlight = 0;
int frame = 1;
int led = 3;
int beep = 2;
int soil = 3;
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

boolean lastConnected = false;                 // state of the connection last time through the main loop

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
    dht.begin();
    pinMode(led,OUTPUT);
    pinMode(beep,OUTPUT);
  
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip, mydns);
  //server.begin();
  Serial.print("server local ip is ");
  Serial.println(Ethernet.localIP());
}

void alert()
{
  for(int i=0;i<75;i++)
  {
  digitalWrite(led,HIGH);
  digitalWrite(beep,HIGH);
  delay(100);
  digitalWrite(led,LOW);
  digitalWrite(beep,LOW);
  delay(100);
  }
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  if (client.available()) {
    char c = client.read();
    Serial.println(c);
    Serial.println("Message from debugging 1");
  }
  // if there's no net connection, but there was one last time
  // through the loop, then stop the client:
  if (!client.connected() && lastConnected)
   {
    Serial.println();
    Serial.println("disconnecting as client.");
    client.stop();
  }
    delay(10000);
    httpRequest();

  // store the state of the connection for next time through
  // the loop:
  lastConnected = client.connected();
}

void httpRequest()
 {
      //assign variable
      sunval = analogRead(sunlight);
      frameval = analogRead(frame);
      //tempval = (125*analogRead(temp))>>8;
      soilval = analogRead(soil);
      int h = dht.readHumidity();
      int t = dht.readTemperature();
  
      if (client.connect(server,80))
       {

        client.print("GET /receive.php?sunval=");
        client.print(sunval);
        client.print("&frameval=");
        client.print(frameval);
        client.print("&tempval=");
        client.print(t);
        client.print("&humival=");
        client.print(h);
        client.print("&soil=");
        client.print(soilval);
        client.println(" HTTP/1.1");
        client.print("Host: ");
        client.println(server);
        client.println("User-Agent: Arduino-Ethernet");
        client.println("Connection: close");
        client.println();
        //Serial.println("Data sent!");
  
        //Loop alert warning
        if(sunval<10 || frameval>=500 || t>=42 || h<=3 || soilval <= 100 )
          alert(); 
      }
    else
    {
      // if you couldn't make a connection:
      //Serial.println("connection failed");
      client.stop();
    }
}


