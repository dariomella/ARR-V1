/**************************************************************
 * procedure triggered by the WiFi.onEvent(WiFiEvent) interrupt
 **************************************************************/
void WiFiEvent(WiFiEvent_t event) {
  DEBUG_PRINTF("------->[WiFi-event] event: %d: ", event);

  switch (event) {
    case ARDUINO_EVENT_WIFI_READY:
      DEBUG_PRINTLN("WiFi interface ready");
      break;
    case ARDUINO_EVENT_WIFI_SCAN_DONE:
      DEBUG_PRINTLN("Completed scan for access points");
      break;
    case ARDUINO_EVENT_WIFI_STA_START:
      DEBUG_PRINTLN("WiFi client started");
      break;
    case ARDUINO_EVENT_WIFI_STA_STOP:
      DEBUG_PRINTLN("WiFi clients stopped");
      break;
    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
      DEBUG_PRINTLN("Connected to access point");
      digitalWrite(LED_1_PIN,HIGH);
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      DEBUG_PRINTLN("Disconnected from WiFi access point");
        digitalWrite(LED_1_PIN,LOW);
      break;
    case ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE:
      DEBUG_PRINTLN("Authentication mode of access point has changed");
      break;
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      DEBUG_PRINTLN("Obtained IP address: ");
      //DEBUG_PRINTLN(WiFi.localIP());
      digitalWrite(LED_2_PIN,HIGH);
      break;
    case ARDUINO_EVENT_WIFI_STA_LOST_IP:
      DEBUG_PRINTLN("Lost IP address and IP address is reset to 0");
      break;
    case ARDUINO_EVENT_WPS_ER_SUCCESS:
      DEBUG_PRINTLN("WiFi Protected Setup (WPS): succeeded in enrollee mode");
      break;
    case ARDUINO_EVENT_WPS_ER_FAILED:
      DEBUG_PRINTLN("WiFi Protected Setup (WPS): failed in enrollee mode");
      break;
    case ARDUINO_EVENT_WPS_ER_TIMEOUT:
      DEBUG_PRINTLN("WiFi Protected Setup (WPS): timeout in enrollee mode");
      break;
    case ARDUINO_EVENT_WPS_ER_PIN:
      DEBUG_PRINTLN("WiFi Protected Setup (WPS): pin code in enrollee mode");
      break;
    case ARDUINO_EVENT_WIFI_AP_START:
      DEBUG_PRINTLN("WiFi access point started");
      break;
    case ARDUINO_EVENT_WIFI_AP_STOP:
      DEBUG_PRINTLN("WiFi access point  stopped");
      break;
    case ARDUINO_EVENT_WIFI_AP_STACONNECTED:
      DEBUG_PRINTLN("Client connected");
      break;
    case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED:
      DEBUG_PRINTLN("Client disconnected");
      break;
    case ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED:
      DEBUG_PRINTLN("Assigned IP address to client");
      break;
    case ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED:
      DEBUG_PRINTLN("Received probe request");
      break;
    case ARDUINO_EVENT_WIFI_AP_GOT_IP6:
      DEBUG_PRINTLN("AP IPv6 is preferred");
      break;
    case ARDUINO_EVENT_WIFI_STA_GOT_IP6:
      DEBUG_PRINTLN("STA IPv6 is preferred");
      break;
    case ARDUINO_EVENT_ETH_GOT_IP6:
      DEBUG_PRINTLN("Ethernet IPv6 is preferred");
      break;
    case ARDUINO_EVENT_ETH_START:
      DEBUG_PRINTLN("Ethernet started");
      break;
    case ARDUINO_EVENT_ETH_STOP:
      DEBUG_PRINTLN("Ethernet stopped");
      break;
    case ARDUINO_EVENT_ETH_CONNECTED:
      DEBUG_PRINTLN("Ethernet connected");
      break;
    case ARDUINO_EVENT_ETH_DISCONNECTED:
      DEBUG_PRINTLN("Ethernet disconnected");
      break;
    case ARDUINO_EVENT_ETH_GOT_IP:
      DEBUG_PRINTLN("Obtained IP address");
      break;
    default: break;
  }
}