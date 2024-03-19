/*************************************************************
 * reads the wifi parameters from the EEPROM
 *************************************************************/
void readPrefs() {
  DEBUG_PRINTLN("******** WIFI PARMS READ BEGIN");
  prefs.getString(SSID_PARAM, ssid, sizeof(ssid));
  prefs.getString(PASSWORD_PARAM, password, sizeof(password));
  prefs.getString(SETUP_PORTAL_SSID_PARAM, portalSSID, sizeof(portalSSID));
  prefs.getString(SETUP_PORTAL_PASSWORD_PARAM, portalPassword, sizeof(portalPassword));
  prefs.getString(REMOTE_HOST1_PARAM, remoteHost1, sizeof(remoteHost1));
  prefs.getString(REMOTE_HOST2_PARAM, remoteHost2, sizeof(remoteHost2));
  prefs.getString(REMOTE_HOST3_PARAM, remoteHost3, sizeof(remoteHost3));
  prefs.getString(REMOTE_HOST4_PARAM, remoteHost4, sizeof(remoteHost4));

  wifiRstTimeout = prefs.getULong(WIFI_RESTART_TIMEOUT_PARAM);
  rebootDelay = prefs.getInt(REBOOT_DELAY_PARAM);
  hostPingTimeout = prefs.getULong(HOST_PING_TIMEOUT_PARAM);

  WifiEspReboots = prefs.getInt("WifiEspReboots");

  DEBUG_PRINT(SSID_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(ssid);
  DEBUG_PRINT(PASSWORD_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(password);
  DEBUG_PRINT(SETUP_PORTAL_SSID_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(portalSSID);
  DEBUG_PRINT(SETUP_PORTAL_PASSWORD_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(portalPassword);
  DEBUG_PRINT(REMOTE_HOST1_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(remoteHost1);
  DEBUG_PRINT(REMOTE_HOST2_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(remoteHost2);
  DEBUG_PRINT(REMOTE_HOST3_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(remoteHost3);
  DEBUG_PRINT(REMOTE_HOST4_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(remoteHost4);

  DEBUG_PRINT(WIFI_RESTART_TIMEOUT_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(wifiRstTimeout);
  DEBUG_PRINT(REBOOT_DELAY_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(rebootDelay);
  DEBUG_PRINT(HOST_PING_TIMEOUT_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(hostPingTimeout);

  DEBUG_PRINT("WifiEspReboots");
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(WifiEspReboots);
  DEBUG_PRINTLN("******** WIFIPARMS READ END");
}

/*************************************************************
 * writes the wifi parameters to the EEPROM
 *************************************************************/
void writePrefs() {
  DEBUG_PRINTLN("******** WIFI PARMS WRITE BEGIN");
  prefs.putString(SSID_PARAM, ssid);
  prefs.putString(PASSWORD_PARAM, password);
  prefs.putString(SETUP_PORTAL_SSID_PARAM, portalSSID);
  prefs.putString(SETUP_PORTAL_PASSWORD_PARAM, portalPassword);
  prefs.putString(REMOTE_HOST1_PARAM, remoteHost1);
  prefs.putString(REMOTE_HOST2_PARAM, remoteHost2);
  prefs.putString(REMOTE_HOST3_PARAM, remoteHost3);
  prefs.putString(REMOTE_HOST4_PARAM, remoteHost4);

  prefs.putULong(WIFI_RESTART_TIMEOUT_PARAM, wifiRstTimeout);
  prefs.putInt(REBOOT_DELAY_PARAM, rebootDelay);
  prefs.putULong(HOST_PING_TIMEOUT_PARAM, hostPingTimeout);

  prefs.putInt("WifiEspReboots", WifiEspReboots);

  DEBUG_PRINT(SSID_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(ssid);
  DEBUG_PRINT(PASSWORD_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(password);
  DEBUG_PRINT(SETUP_PORTAL_SSID_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(portalSSID);
  DEBUG_PRINT(SETUP_PORTAL_PASSWORD_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(portalPassword);
  DEBUG_PRINT(REMOTE_HOST1_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(remoteHost1);
  DEBUG_PRINT(REMOTE_HOST2_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(remoteHost2);
  DEBUG_PRINT(REMOTE_HOST3_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(remoteHost3);
  DEBUG_PRINT(REMOTE_HOST4_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(remoteHost4);

  DEBUG_PRINT(WIFI_RESTART_TIMEOUT_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(wifiRstTimeout);
  DEBUG_PRINT(REBOOT_DELAY_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(rebootDelay);
  DEBUG_PRINT(HOST_PING_TIMEOUT_PARAM);
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(hostPingTimeout);

  DEBUG_PRINT("WifiEspReboots");
  DEBUG_PRINT("=");
  DEBUG_PRINTLN(WifiEspReboots);
  DEBUG_PRINTLN("******** WIFIPARMS WRITE END");
}

/*******************************************************************
* Reset the default values
********************************************************************/
void factoryReset() {
  prefs.end();
  nvs_flash_erase();  // erase the NVS partition and...
  nvs_flash_init();   // initialize the NVS partition.
  prefs.begin("WIFIParms", false);  // il primo parametro da' un nome all'area di memoria per i parametri secondo parametro indica readonly
  
  strlcpy(ssid, SSID_DEFAULT, sizeof(ssid));
  strlcpy(password, PASSWORD_DEFAULT, sizeof(password));
  strlcpy(portalSSID, SETUP_PORTAL_SSID_DEFAULT, sizeof(portalSSID));
  strlcpy(portalPassword, SETUP_PORTAL_PASSWORD_DEFAULT, sizeof(portalPassword));
  strlcpy(remoteHost1, REMOTE_HOST1_DEFAULT, sizeof(remoteHost1));
  strlcpy(remoteHost2, REMOTE_HOST2_DEFAULT, sizeof(remoteHost2));
  strlcpy(remoteHost3, REMOTE_HOST3_DEFAULT, sizeof(remoteHost3));
  strlcpy(remoteHost4, REMOTE_HOST4_DEFAULT, sizeof(remoteHost4));
  wifiRstTimeout = WIFI_RESTART_TIMEOUT_DEFAULT;
  rebootDelay = REBOOT_DELAY_DEFAULT;
  hostPingTimeout = HOST_PING_TIMEOUT_DEFAULT;

  WifiEspReboots = 0;
  writePrefs();
  //readPrefs();
}

//*******************************************************************
// reboot the router and wait for reboot to complete
//*******************************************************************
void rebootRouter() {
  DEBUG_PRINTLN("*** REBOOT ROUTER ***");
  DEBUG_PRINTLN("Switch router off");
  digitalWrite(RELAIS_PIN, HIGH);
  delay(10000);
  DEBUG_PRINTLN("Switch router on");
  digitalWrite(RELAIS_PIN, LOW);
  DEBUG_PRINT("Waiting");  DEBUG_PRINT(rebootDelay) ;DEBUG_PRINTLN("  seconds to allow router to reboot...");
  for (int i = 0; i < rebootDelay; i++) {
    delay(1000);
    digitalWrite(LED_2_PIN, !digitalRead(LED_2_PIN));
    if (i % 10 == 0) {
      DEBUG_PRINT(" ");
      DEBUG_PRINT(i);
      DEBUG_PRINTLN(" seconds elapsed");
    }
  }
  DEBUG_PRINTLN("End of wait");
}
