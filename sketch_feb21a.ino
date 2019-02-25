/*change the SSID and Password according to your wifi(it has to be a 2.4ghz wifi. Has various serial prints to track the code in serial monitor. To Test a new website, you'll need to repower the esp32*/
#include <WebServer.h>
#include <HTTP_Method.h>

#include <WiFiAP.h>
#include <WiFiMulti.h>
#include <WiFiUdp.h>
#include <WiFiScan.h>
#include <ETH.h>
#include <WiFiClient.h>
#include <WiFiSTA.h>
#include <WiFiServer.h>
#include <WiFiType.h>
#include <WiFiGeneric.h>


#include <WiFiClient.h>

// constant declaration
const char* ssid = "2.5AksharPremKe";
const char* password = "darthtimber@18";
const char* newssid = "darthcapn";
const char* newpassword = "";
  String urll;

WebServer server(80);

void Root() {}

void NotFound()
{ 
  int counter = 0;
 char str[100];
 
 if(server.uri()!= '\0')
  urll = server.uri();

 urll.toCharArray(str,100);
  
    // Returns first token  
    char *token = strtok(str, "/"); 
    char *urlArray[100];
       memset(urlArray, '\0', sizeof(urlArray));

    // Keep printing tokens while one of the 
    // delimiters present in str[]. 
    int i = 0;
    while (token != NULL || token != '\0') 
    { 
        urlArray[i] = token;
        
        Serial.println("Printing the tokens");
        
        Serial.println(token);
        token = strtok(NULL, "/"); 
        i++;
    } 
  String urlMain = urlArray[1];
  
        Serial.println(urlArray[0]);
  //const char* host="esqsoft.com";
  //const char* url="/examples/troubleshooting-http-using-telnet.htm";
 char* host;
host=urlArray[1];

Serial.println("Printing Host");
        Serial.println(host);
   char url[100];
  int j = 2;
  
  strcpy(url, "/");
          Serial.println("Printing URL");
          Serial.println(url);

  while(urlArray[j]!= '\0' || urlArray[j]!= NULL  ){
        Serial.println("Entered the loop");

    if(j>=3){
      strcat(url,"/");
    }
    
    strcat(url,urlArray[j]);
    Serial.println("Printing URL from inside loop");
          Serial.println(url);

        Serial.println("Printing URL");
        Serial.println(url);
    j++;
  }

        Serial.println("Printing FInal URL");  

  WiFiClient client;
        Serial.println("client init over");  
bool cool = client.connect(host, 80);
        Serial.println("cool bool");
                Serial.println(cool);  
 int in = 0;
  while (!client.connect(host, 80)) 
  {
    Serial.println("Connection Failed");  
    in++;
    if(in>500){
      return;
      }
  }
        Serial.println("Below connection paradigm");

  client.print(String("GET ") + url);
        Serial.println("Below printstring on client");

  client.print(String(" HTTP/1.1\r\n") + "Host: " + host + "\r\n" +  "Connection: close\r\n\r\n");
                   Serial.println("Below printstring on client showing host");
  while(!client.available())
  {
    yield();
            Serial.println("Yielding connection");

  }

  String l;
  while(client.available())
  {
            Serial.println("Client available");

    l = client.readStringUntil('\r');
    l.replace("HTTP", "WHAT-IS-THIS");
    l.replace("http","WHAT-IS-THIS");
        Serial.println("replaces string");

  }
          Serial.println("about to resend");

  server.send(200, "text/html", l);
        Serial.println("resend");
  client.stop();
}

void setup(void)
{
  Serial.begin(115200);
  WiFi.softAP(newssid, newpassword);
  server.on("/", Root);
  server.onNotFound(NotFound);

  server.begin();
  Serial.println("HTTP Server connected");
  WiFi.begin(ssid, password);
}

void loop(void)
{
  server.handleClient();
}
