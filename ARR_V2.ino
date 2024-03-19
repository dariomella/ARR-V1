#define DEBUG 1

#include "00instructions.h"
#include "00comments.h"
#include "00index.h"
#include <Preferences.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <nvs_flash.h>
#include <ESPping.h>

#ifdef DEBUG
#define DEBUG_PRINT(x)     Serial.print (x)
#define DEBUG_PRINTDEC(x)     Serial.print (x, DEC)
#define DEBUG_PRINTLN(x)  Serial.println (x)
#define DEBUG_PRINTF(x , y)  Serial.printf (x , y )
#define PRINTD(x) Serial.print("===>");Serial.print(F(#x"="));Serial.println(x);
#else
#define DEBUG_PRINT(x)   
#define DEBUG_PRINTDEC(x) 
#define DEBUG_PRINTLN(x)  
#define DEBUG_PRINTF(x , y)  
#define PRINTD(x) 
#endif

//** the following are the names used to store in preferences the parameters.
//** They can be any value but I have chosen to keep the same name as the variable used in the source with the limitation that it cannot exceed 15 characters
char ssid[32];
#define SSID_PARAM "ssid"
#define SSID_DEFAULT "WIFI NETWORK ID"

char password[64];
#define PASSWORD_PARAM "password"
#define PASSWORD_DEFAULT "WIFI PASSWORD"

char portalSSID[32];
#define SETUP_PORTAL_SSID_PARAM "portalSSID"
#define SETUP_PORTAL_SSID_DEFAULT "ARR_NET"

char portalPassword[64];
#define SETUP_PORTAL_PASSWORD_PARAM "portalPassword"
#define SETUP_PORTAL_PASSWORD_DEFAULT "password123"

char remoteHost1[50];
#define REMOTE_HOST1_PARAM "remoteHost1"
#define REMOTE_HOST1_DEFAULT "www.google.com"

char remoteHost2[50];
#define REMOTE_HOST2_PARAM "remoteHost2"
#define REMOTE_HOST2_DEFAULT "8.8.4.4"

char remoteHost3[50];
#define REMOTE_HOST3_PARAM "remoteHost3"
#define REMOTE_HOST3_DEFAULT "9.9.9.9"

char remoteHost4[50];
#define REMOTE_HOST4_PARAM "remoteHost4"
#define REMOTE_HOST4_DEFAULT "1.1.1.1"

unsigned long  wifiRstTimeout ; //how long to wait for a WIFI connection
char wifiRstTimeoutString[10];
#define WIFI_RESTART_TIMEOUT_PARAM  "wifiRstTimeout" //wifi restart tieout
#define WIFI_RESTART_TIMEOUT_DEFAULT 120UL

int  rebootDelay ; // time in seconds to allow router to reboot before restarting he ESP
char rebootDelayString[10];
#define REBOOT_DELAY_PARAM "rebootDelay"
#define REBOOT_DELAY_DEFAULT  180

unsigned long hostPingTimeout;
char hostPingTimeoutString[10];
#define HOST_PING_TIMEOUT_PARAM  "hostPingTimeout"
#define HOST_PING_TIMEOUT_DEFAULT  120UL

#define FACTORY_RESET_WAIT 15000 //button must be pressed for this time to do a factory reset

Preferences prefs;



//*********************************************************
//***** WiFi Variables
//*********************************************************

WiFiClient client;
unsigned long lastWifiOK = 0; //refers to last wifi restart command and also to last wifi succesful connection
unsigned long lastGatewayPingOk =0; // when internet connection to Gateway was last succesfully checked
unsigned long lastHostsPingOk =0; // when internet connection to hsto was last succesfully checked
bool WifiConnectedStatus = false;
IPAddress gatewayIP(0,0,0,0);
IPAddress remote_ip(0,0,0,0);

//*********************************************************
//* web portal variables
//*********************************************************
AsyncWebServer server(80);
bool webParametersSet = false;
char tableRows[2048]; //about 180 chars per row
bool tableRowsTruncated = false;
char trText [300];

//********************************************************
//* misc
//********************************************************
int WifiEspReboots = 0; //number of ESP reboots because no wifi connection
#define RESET_WIFI_SETTINGS_PIN 4
#define LED_1_PIN 16
#define LED_2_PIN 17
#define LED_3_PIN 18
#define RELAIS_PIN 19
char longString[1024] = {0};

//----------------------------------------------------------------------------------------------------
void setup()
{
  RunOnce();
}
void loop()
{
 // MainLoop();
 CheckInternet();
  delay(5000);
}
