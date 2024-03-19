/******************************************************************
 * manages wifi connection;
 * Connect or reconnect to WiFi
 ******************************************************************/
void CheckInternet() {
  DEBUG_PRINTLN("\n\rChecking connectivity");
  wl_status_t WifiStatus;
  WifiStatus = WiFi.status();
  if (WifiStatus != WL_CONNECTED) {
    WifiConnectedStatus = false;
    snprintf(longString, sizeof(longString), "\n\rWIFI error %s while attempting connection to SSID=%s using password %s for %i seconds. %i seconds left before timeout", wl_status_to_string(WifiStatus), ssid, password, ((millis() - lastWifiOK) / 1000), wifiRstTimeout - ((millis() - lastWifiOK) / 1000) );
    digitalWrite(LED_2_PIN, LOW);
    digitalWrite(LED_3_PIN, LOW);
    Serial.println(longString);
    if ((unsigned long)(millis() - lastWifiOK) >= wifiRstTimeout*1000UL) {
      snprintf(longString, sizeof(longString), "Timeout for Wifi connection. Event number %i", WifiEspReboots);
      Serial.println(longString);
      WifiEspReboots++;
      prefs.putInt("WifiEspReboots", WifiEspReboots);
      if (WifiEspReboots >= 3) {
        rebootRouter();

        WifiEspReboots = 0;
        prefs.putInt("WifiEspReboots", WifiEspReboots);
      }
      DEBUG_PRINTLN("**** REBOOTING ESP .... ");
      ESP.restart();
    }
  }
  else {  //wifi is connected
    lastWifiOK = millis();
    if (WifiEspReboots != 0) {
      WifiEspReboots = 0;
      prefs.putInt("WifiEspReboots", WifiEspReboots);
    }
    snprintf(longString, sizeof(longString), "\n\rWIFI SSID %s Connected", ssid);
    Serial.println(longString);
    if (!WifiConnectedStatus) {  //if statement inserted to perform the display only when the status changes
      displayWifiStatus();
    }
    WifiConnectedStatus = true;
    digitalWrite(LED_1_PIN, HIGH);
    if (gatewayPingOK()) {
      digitalWrite(LED_2_PIN, HIGH);
    } else {
      digitalWrite(LED_2_PIN, LOW);
      digitalWrite(LED_3_PIN, LOW);
    }
    if (HostsPingOK()) {
      lastHostsPingOk = millis();
      digitalWrite(LED_3_PIN, HIGH);
    } else {
      digitalWrite(LED_3_PIN, LOW);
      snprintf(longString, sizeof(longString), "No Internet connection for %i seconds. %i seconds left before timeout.", ((millis() - lastHostsPingOk) / 1000), hostPingTimeout - ((millis() - lastHostsPingOk)/1000));
      Serial.println(longString);
    }
    if ((unsigned long)(millis() - lastHostsPingOk) >= hostPingTimeout*1000UL) {
      rebootRouter();
      DEBUG_PRINTLN("**** REBOOTING ESP .... ");
      ESP.restart();
    }
  }
}
/************************************************************************
 * shows the status of wifi connection
 ************************************************************************/
void displayWifiStatus() {
  if ((WiFi.status() == WL_CONNECTED)) {
    Serial.println("");
    //snprintf(longString, sizeof(longString), " WiFi SSID %s  connected", ssid);
    //Serial.println(longString);
    Serial.println("**TCPIP connection status");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("ESP Mac Address: ");
    Serial.println(WiFi.macAddress());
    Serial.print("Subnet Mask: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("Gateway IP: ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("DNS: ");
    Serial.println(WiFi.dnsIP());
    Serial.println("**");
  } else {
    snprintf(longString, sizeof(longString), " WiFi SSID %s not connected", ssid);
    Serial.println(longString);
  }
}

//***************************************************************
//* ping a group of remote hosts. Returns true if at least one is reached
//***************************************************************
bool HostsPingOK() {
  bool result = false;
  if (HostPing(remoteHost1)) result = true;
  if (HostPing(remoteHost2)) result = true;
  if (HostPing(remoteHost3)) result = true;
  if (HostPing(remoteHost4)) result = true;
  return result;
}

//****************************************************************
//* ping a host passed as a string parameter.
//* returns true if PING returns a response
//****************************************************************
bool HostPing(const char* remote_host) {
  if (Ping.ping(remote_host, 1) > 0) {
    Serial.printf("Ping %s response time: %.0f ms\n\r", remote_host, Ping.averageTime());
    return true;
  } else {
    Serial.printf("Ping %s Error !\n\r", remote_host);
    return false;
  }
}

//*******************************************************************
//* ping the LAN gateway and retrieve the connection status
//*******************************************************************
bool gatewayPingOK() {
  bool result = false;
  IPAddress gatewayIP;
  gatewayIP = WiFi.gatewayIP();
  if (Ping.ping(gatewayIP, 1) > 0) {
    Serial.printf("Gateway %u.%u.%u.%u Ping response time: %.0f ms\n\r", gatewayIP[0], gatewayIP[1], gatewayIP[2], gatewayIP[3], Ping.averageTime());
    result = true;
  } else {
    Serial.printf("Gateway Ping %u.%u.%u.%u Ping Error !\n\r", gatewayIP[0], gatewayIP[1], gatewayIP[2], gatewayIP[3]);
  }
  return result;
}

/********************************************************
* function to return the error code from the  WiFi.status() command
*********************************************************/
const char* wl_status_to_string(wl_status_t status) {
  switch (status) {
    case WL_NO_SHIELD: return "WL_NO_SHIELD";
    case WL_IDLE_STATUS: return "WL_IDLE_STATUS";
    case WL_NO_SSID_AVAIL: return "WL_NO_SSID_AVAIL";
    case WL_SCAN_COMPLETED: return "WL_SCAN_COMPLETED";
    case WL_CONNECTED: return "WL_CONNECTED";
    case WL_CONNECT_FAILED: return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST: return "WL_CONNECTION_LOST";
    case WL_DISCONNECTED: return "WL_DISCONNECTED";
  }
}