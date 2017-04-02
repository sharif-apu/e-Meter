// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3
#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;             // Create an instance
float use = 0;
int time=0;
float totalUse=0;
#define RELAY1  7 
#define RELAY2  6
String readString;
 int divStatus=0;
String data="";
//Lan Config
#include <SPI.h>
#include <Regexp.h>
//change the following line to #include <Ethernet.h> to use the eithent shield
#include <UIPEthernet.h> 
float x_use;
// Enter a MAC address for your controller below.
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//thingspeak server
char server[] = "192.168.1.107";

//if DHCP fails, use a static IP
IPAddress ip(192,168,1,105);

// Initialize the Ethernet client library
EthernetClient client;





void setup()
{  
  Serial.begin(9600);
  
  emon1.voltage(2, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon1.current(1, 111.1);       // Current: input pin, calibration.
  pinMode(RELAY1, OUTPUT);        // Relay config
  pinMode(RELAY2, OUTPUT);        // Relay config

  //set up Ethernet:
  setupEthernet();
  
  //send the sms
  Serial.println("Sending data...");
  
  sendSMS();
}

void loop()
{
  emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  emon1.serialprint();           // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)
  
  float realPower       = emon1.realPower;        //extract Real Power into variable
  float apparentPower   = emon1.apparentPower;    //extract Apparent Power into variable
  float powerFactor     = emon1.powerFactor;      //extract Power Factor into Variable
  float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
  float Irms            = emon1.Irms;  //extract Irms into Variable

        use=realPower*60;
        Serial.println(use);
       // Serial.println(x);
     
      if(x_use<=350000){

  Serial.println("enter");
     //   for(x=0; x<15;x++){
     
          //Serial.print("status=");
           device();
   //  Serial.println(divStatus);
   //  Serial.println(x);
        delay(2000);
         if(divStatus==11){
    
         digitalWrite(RELAY1,1);           // Turns ON Relays 1
         Serial.println("Light no:1 ON");
         digitalWrite(RELAY2,1);           // Turns ON Relays 1
         Serial.println("Light no:2 ON");
    
        }

        else if(divStatus==10){
          digitalWrite(RELAY1,1);           // Turns ON Relays 1
          Serial.println("Light no:1 ON");
          digitalWrite(RELAY2,0);          // Turns Relay Off
          Serial.println("Light no: 2 OFF");
        }

        else if(divStatus==01){
          digitalWrite(RELAY1,0);           // Turns ON Relays 1
          Serial.println("Light no:1 OFF");
          digitalWrite(RELAY2,1);          // Turns Relay Off
          Serial.println("Light no: 2 OM");
        }

        else{
         digitalWrite(RELAY1,0);           // Turns ON Relays 1
         Serial.println("Light no:1 OFF");
         digitalWrite(RELAY2,0);          // Turns Relay Off
         Serial.println("Light no: 2 OFF");
        }
    
       // delay(2000);// Wait 2 seconds
   // }
  sendSMS();
    }   



    else{

      //for(x=0; x<15;x++){
      
        device();
        delay(2000);
        //Serial.println(status);
        if(divStatus==10){
            digitalWrite(RELAY1,1);           // Turns ON Relays 1
            Serial.println("Light no:1 ON");
            digitalWrite(RELAY2,0);          // Turns Relay Off
            Serial.println("Light no: 2 OFF");
        }
        else{
            digitalWrite(RELAY1,0);           // Turns ON Relays 1
            Serial.println("Light no:1 OFF");
            digitalWrite(RELAY2,0);          // Turns Relay Off
            Serial.println("Light no: 2 OFF");
        }
   // }
   // delay(2000);
    }
        
        sendSMS();
       // Serial.println(cs);
         //Serial.println (readString);


}


// Send and retrive data from the server

void sendSMS()
{
  // Make a TCP connection to remote host
  if (client.connect(server, 80))
  {
    client.print("GET /slim-rest/public/arddata/");
    //client.print("watt=");
    client.print(use);
   client.print("/");
    client.print(time);
    client.print("/");
  client.print("1");
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
  }
  else
  {
    Serial.println(F("Connection failed"));
  } 

  // Check for a response from the server, and route it
  // out the serial port.
  while (client.connected())
  {
    if ( client.available() )
    {
      char c = client.read();
      String cs(c);
    
       data.concat(cs);
    
     //Serial.print(c);
    }      
  }
  Serial.println(data);

      int firstClosingBracket = data.indexOf('*');
      //Serial.println (firstClosingBracket);
      int secondClosingBracket = data.indexOf('$');
      //Serial.println (secondClosingBracket);
      
      for (int i = firstClosingBracket+1; i <= secondClosingBracket-1; i++) { 
        readString.concat(data.charAt(i));
      }

  Serial.print("Used data: ");
  Serial.println (readString);
  x_use=readString.toFloat();
   Serial.println ();
  Serial.println(x_use);
  readString = "";
  
  client.stop();
}

void device()
{
  // Make a TCP connection to remote host
  if (client.connect(server, 80))
  {
    client.print("GET /slim-rest/public/sensorData/");
    //client.print("watt=");
//    client.print(use);
//   client.print("/");
//    client.print(time);
//    client.print("/");
//  client.print("1");
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
  }
  else
  {
    Serial.println(F("Connection failed"));
  } 

  // Check for a response from the server, and route it
  // out the serial port.
  while (client.connected())
  {
    if ( client.available() )
    {
      char c = client.read();
      String cs(c);
    
       data.concat(cs);
    
     //Serial.print(c);
    }      
  }
  Serial.println(data);

      int firstClosingBracket = data.indexOf('*');
      //Serial.println (firstClosingBracket);
      int secondClosingBracket = data.indexOf('$');
      //Serial.println (secondClosingBracket);
      
      for (int i = firstClosingBracket+1; i <= secondClosingBracket-1; i++) { 
        readString.concat(data.charAt(i));
      }

  Serial.print("Device Status: ");
  Serial.println (readString);
 // divStatus=readString.toFloat();
   Serial.println ();
  //Serial.println(x_use);
  readString = "";
  
  client.stop();
}


void setupEthernet()
{
  Serial.println("Setting up Ethernet...");
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("Failed to configure Ethernet using DHCP"));
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  // give the Ethernet shield a second to initialize:
  delay(1000);
}

String URLEncode(const char* msg)
{
  const char *hex = "0123456789abcdef";
  String encodedMsg = "";

  while (*msg!='\0'){
    if( ('a' <= *msg && *msg <= 'z')
      || ('A' <= *msg && *msg <= 'Z')
      || ('0' <= *msg && *msg <= '9') ) {
      encodedMsg += *msg;
    } 
    else {
      encodedMsg += '%';
      encodedMsg += hex[*msg >> 4];
      encodedMsg += hex[*msg & 15];
    }
    msg++;
  }
  return encodedMsg;
}

