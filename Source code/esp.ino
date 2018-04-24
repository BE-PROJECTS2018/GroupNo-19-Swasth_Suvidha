#include <ESP8266WiFi.h>
#include "SoftwareSerial.h"


#include <OneWire.h>
#include <DallasTemperature.h>



#define ONE_WIRE_BUS 5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

String apiKey = "channels_write_api_key";

const char* ssid = "wifi_ssid";
const char* password = "wifi_password";

const char* server = "api.thingspeak.com";

SoftwareSerial port(14, 12, false, 256);

SoftwareSerial port2(13, 15, false, 256);



WiFiClient client;
void setup() 
{   
    Serial.begin(115200);              
    port.begin(115200);          //This serial port for Pulse sensor
     port2.begin(115200);          //This serial port for SPO2  
    sensors.begin(); 
    
    delay(2000);    
    Serial.println("========================================================>>>> ");
     WiFi.begin(ssid, password);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {

  String tmp = "0",pul = "0",spo = "0";

  tmp = getTemperatures();
   sendToThingspeak(1, tmp);
  Serial.println("1.Temperature = " + tmp );
  if( port.available() > 0 )
  {

    pul =  getMessageFromPulse();
    //pul = pul.substring(0,4);
    sendToThingspeak(2,pul.substring(0,4));
 
    Serial.println("                                     2.Pulse Rate = " + pul);    
  }

  if( port2.available() > 0 )
  {
    spo =  getMessageFromSPO2();
     sendToThingspeak(3, spo);
    Serial.println("                                                                                 3.SPO2 Rate = " + spo );    
  }


}

String getTemperatures()
{
  sensors.requestTemperatures();                // Send the command to get temperatures
  return String(sensors.getTempCByIndex(0));    
}




String getMessageFromSPO2()
{
  String str = "";
  boolean f = 0;

  while(true)
  {
   while(  port2.available() ) 
   {    
    char rc =  port2.read();  

       if( rc == '?' )
        {
        //Serial.print(str);   
         port2.flush(); 
        f = 1;   
        break;    
        } 
        
    str += rc;
   } 

     yield();
   if(f == 1)
   break;
  }   str.trim();
return str;  
}

String getMessageFromPulse()
{
  String str = "";
  boolean f = 0;

  while(true)
  {
   while( port.available() ) 
   {    
    char rc = port.read();  

       if( rc == '?' )
        {
        //Serial.print(str);   
        port.flush(); 
        f = 1;   
        break;    
        } 
        
    str += rc;
   } 
   yield();
   if(f == 1)
   break;
  }   str.trim();
return str;  
}






void sendToThingspeak(int ch, String val)
{
  switch(ch)
  {
    case 1:
    {
                                                                  if (client.connect(server,80))       // "184.106.153.149" or api.thingspeak.com
                                                { 
                                                   
                                                          val.trim();
                                                            
                                                    String postStr = apiKey;
                                                    
                                                    postStr += "&field4=";
                                                    
                                                    postStr += val;
                                                    
                                                    postStr += "\r\n\r\n";
                                                      
                                                      client.print("POST /update HTTP/1.1\n");
                                                      client.print("Host: api.thingspeak.com\n");
                                                      client.print("Connection: close\n");
                                                      client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                                                      client.print("Content-Type: application/x-www-form-urlencoded\n");
                                                      client.print("Content-Length: ");
                                                      client.print(postStr.length());
                                                      client.print("\n\n");
                                                      client.print(postStr);
                                                     client.stop();
                                                     
                                                     
                                                  
                                                }
    }
    break;

    case 2:
    {

                                             if (client.connect(server,80))       // "184.106.153.149" or api.thingspeak.com
                                              { 
                                                 
                                                   
                                                    val.trim();
                                                       
                                                    String postStr = apiKey;
                                                    
                                                    postStr += "&field2=";
                                                    
                                                    postStr += val;
                                                    
                                                    postStr += "\r\n\r\n";
                                                    
                                                    client.print("POST /update HTTP/1.1\n");
                                                    client.print("Host: api.thingspeak.com\n");
                                                    client.print("Connection: close\n");
                                                    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                                                    client.print("Content-Type: application/x-www-form-urlencoded\n");
                                                    client.print("Content-Length: ");
                                                    client.print(postStr.length());
                                                    client.print("\n\n");
                                                    client.print(postStr);
                                                   client.stop();
                                                   
                                                   
                                                
                                              }
      
    }
    break;

    case 3:
    {

                                          
                                            if (client.connect(server,80))       // "184.106.153.149" or api.thingspeak.com
                                            { 
                                                
                                                  
                                                          
                                                     val.trim();

                                                   
                                                            
                                                    String postStr = apiKey;
                                                    
                                                    postStr += "&field3=";
                                                    
                                                    postStr += val;
                                                    
                                                    postStr += "\r\n\r\n";
                                                  
                                                  client.print("POST /update HTTP/1.1\n");
                                                  client.print("Host: api.thingspeak.com\n");
                                                  client.print("Connection: close\n");
                                                  client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                                                  client.print("Content-Type: application/x-www-form-urlencoded\n");
                                                  client.print("Content-Length: ");
                                                  client.print(postStr.length());
                                                  client.print("\n\n");
                                                  client.print(postStr);
                                                 client.stop();
                                                 
                                                 
                                            }
      
    }
    break;

       
    
  }
  
}
