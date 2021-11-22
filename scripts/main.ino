
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

void setup(){
    
    Serial.begin(115200);
    Serial.printf("\n[SETUP] Starting");
    WiFi.mode(WIFI_STA);
    
    
    WiFi.begin(ssid, pass);
    WiFi.config(ip, gw, sub, dns);
    Serial.printf("\n[SETUP] Waiting for Connect");
    while (WiFi.status() != WL_CONNECTED){
       Serial.printf(".");
       delay(500);
    };
    Serial.println(WiFi.localIP());
    Serial.print(WiFi.dnsIP());
    Serial.println();


   if (checkFwUpdate())
   {
       Serial.printf("\n[FWcheck] New Udate!!");
   } else {
       Serial.printf("\n[FWcheck] no update... ");
   };
   
    
};

void loop(){ 
};

bool checkFwUpdate(){
    /*Check for newest FW Version in the git repository (on fw Url)
    */
   // Set connection to "no https fingerprint needed"
   client.setInsecure();
   //connect to FW URL
   client.connect(fwUrl, 443);

   https.begin(client, fwPath);
   String payload;
   // Initiate the connection to the FW Server
   int httpCode = https.GET();
   if (httpCode == 200){
       // If connection is established get the newest FW number
       payload = https.getString();
       int fwNew = payload.toInt();

       // If the newest version is higher than the old one try to update the firmware
       if (fwNew > fwVersion) {
           // Update available
           Serial.printf("\n[fwCheck] New Update found: Versiaon %i", fwNew);
           return true;
       } else {
           // No update available
            Serial.printf("\n[fwCheck] No update. Version: %i", fwVersion);
           return false;
       };
   } else {
       // Error code here
       Serial.printf("\n[fwCheck] Connection error");
       return false;
   };
};