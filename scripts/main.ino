
// Include Libaries
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
// #include <ESP8266httpUpdate.h>


// Setup Wifi Objects
WiFiClientSecure client;
HTTPClient https;

// Declare global variables
const int fwVersion = 1;
const String fwUrl = "https://raw.githubusercontent.com";
const String fwPath = "https://raw.githubusercontent.com/PA0DEV/7_Segment_Clock/main/scripts/latest.version";
const char* ssid = "PATH to Internet";
const char* pass = "WLANphtasBUDE";
IPAddress ip(192, 168, 178, 200);
IPAddress sub(255, 255, 255, 0);
IPAddress gw(192, 168 ,178, 1);
IPAddress dns(8, 8, 8, 8);
IPAddress dns2(8, 8, 4, 4);

void setup(){
    
    Serial.begin(115200);
    Serial.println("Starting");
    WiFi.mode(WIFI_STA);
    
    
    WiFi.begin(ssid, pass);
    WiFi.config(ip, gw, sub, dns);
    Serial.printf("Waiting for Connect");
    while (WiFi.status() != WL_CONNECTED){
       Serial.printf(".");
       delay(500);
    };
    Serial.println(WiFi.localIP());
    Serial.print(WiFi.dnsIP());
   Serial.println();
    
};

void loop(){
    
    Serial.print("\nChecking Updates...");
    checkFwUpdate(); 
    delay(5000);   
};

void checkFwUpdate(){
    /*Check for newest FW Version in the git repository (on fw Url)
    */
   client.setInsecure();
   client.connect(fwUrl, 443);

   https.begin(client, fwPath);
   String payload;
   if (https.GET() == 200){
       int fwNew = StringToInt(https.getString());
       Serial.printf("\nPayload: %i", fwNew);
       Serial.printf("\n Old Version: %s", fwVersion);
       if (fwNew != fwVersion) {
           Serial.printf("New Update!!");
       } else {
           Serial.printf("No new update.");
       };
   } else {
       
   };
};