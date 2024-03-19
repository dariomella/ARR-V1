/*************************************************************************
 *main procedure to start the web server and display/enter the connection parameters
*************************************************************************/
void webPortal() {
  //scan list of networks
  DEBUG_PRINTLN("**** WEB PORTAL STARTED");

  digitalWrite(LED_2_PIN, HIGH);
  digitalWrite(LED_3_PIN, LOW);
  showNetworks();

  // Connect to Wi-Fi network with SSID and password
  Serial.println("Setting AP (Access Point)…");
  Serial.printf("SSID=%s PASSWORD=%s \n\r", portalSSID, portalPassword);
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(portalSSID, portalPassword);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("Original AP IP address: ");
  Serial.println(IP);

  /******************************************************************************
  * invoked when the index.html root page is accessed
  *******************************************************************************/ 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    Serial.println("** root page");
    request->send_P(200, "text/html", index_html, replacePlaceholders);
  });

  //******************************************************************************
  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [](AsyncWebServerRequest* request) {
    String inputMessage;
    // GET input value on <ESP_IP>/get?input3=<inputMessage>
    // 1
    if (request->getParam(SSID_PARAM)->value() != "") {
      inputMessage = request->getParam(SSID_PARAM)->value();
      strncpy(ssid, inputMessage.c_str(), sizeof(ssid));
      ssid[sizeof(ssid) - 1] = 0;  // per sicurezza metto l'ultimo carattere e' zero
    }
    //2
    if (request->getParam(PASSWORD_PARAM)->value() != "") {
      inputMessage = request->getParam(PASSWORD_PARAM)->value();
      strncpy(password, inputMessage.c_str(), sizeof(password));
      password[sizeof(password) - 1] = 0;  // per sicurezza metto l'ultimo carattere e' zero
    }
    //3
    if (request->getParam(SETUP_PORTAL_SSID_PARAM)->value() != "") {
      inputMessage = request->getParam(SETUP_PORTAL_SSID_PARAM)->value();
      strncpy(portalSSID, inputMessage.c_str(), sizeof(portalSSID));
      portalSSID[sizeof(portalSSID) - 1] = 0;  // per sicurezza metto l'ultimo carattere e' zero
    }
    //4
    if (request->getParam(SETUP_PORTAL_PASSWORD_PARAM)->value() != "") {
      DEBUG_PRINTLN("** GET PASSWORD PARAM BEGIN");
      inputMessage = request->getParam(SETUP_PORTAL_PASSWORD_PARAM)->value();
      DEBUG_PRINTLN(inputMessage);
      strncpy(portalPassword, inputMessage.c_str(), sizeof(portalPassword));
      DEBUG_PRINTLN(portalPassword);
      portalPassword[sizeof(portalPassword) - 1] = 0;  // per sicurezza metto l'ultimo carattere e' zero
      DEBUG_PRINTLN(portalPassword);
      DEBUG_PRINTLN("** GET PASSWORD PARAM end");
    }
    //5
    if (request->getParam(REMOTE_HOST1_PARAM)->value() != "") {
      inputMessage = request->getParam(REMOTE_HOST1_PARAM)->value();
      strncpy(remoteHost1, inputMessage.c_str(), sizeof(remoteHost1));
      remoteHost1[sizeof(remoteHost1) - 1] = 0;  // per sicurezza metto l'ultimo carattere e' zero
    }
    //6
    if (request->getParam(REMOTE_HOST2_PARAM)->value() != "") {
      inputMessage = request->getParam(REMOTE_HOST2_PARAM)->value();
      strncpy(remoteHost2, inputMessage.c_str(), sizeof(remoteHost2));
      remoteHost2[sizeof(remoteHost2) - 1] = 0;  // per sicurezza metto l'ultimo carattere e' zero
    }
    //7
    if (request->getParam(REMOTE_HOST3_PARAM)->value() != "") {
      inputMessage = request->getParam(REMOTE_HOST3_PARAM)->value();
      strncpy(remoteHost3, inputMessage.c_str(), sizeof(remoteHost3));
      remoteHost3[sizeof(remoteHost3) - 1] = 0;  // per sicurezza metto l'ultimo carattere e' zero
    }
    //8
    if (request->getParam(REMOTE_HOST4_PARAM)->value() != "") {
      inputMessage = request->getParam(REMOTE_HOST4_PARAM)->value();
      strncpy(remoteHost4, inputMessage.c_str(), sizeof(remoteHost4));
      remoteHost4[sizeof(remoteHost4) - 1] = 0;  // per sicurezza metto l'ultimo carattere e' zero
    }
    //9
    if (request->getParam(WIFI_RESTART_TIMEOUT_PARAM)->value() != "") {
      inputMessage = request->getParam(WIFI_RESTART_TIMEOUT_PARAM)->value();
      strncpy(wifiRstTimeoutString, inputMessage.c_str(), sizeof(wifiRstTimeoutString));
      wifiRstTimeoutString[sizeof(wifiRstTimeoutString) - 1] = 0;  // per sicurezza metto l'ultimo carattere e' zero
      wifiRstTimeout = strtoul(wifiRstTimeoutString, NULL, 10);
    }
    //10
    if (request->getParam(REBOOT_DELAY_PARAM)->value() != "") {
      inputMessage = request->getParam(REBOOT_DELAY_PARAM)->value();
      strncpy(rebootDelayString, inputMessage.c_str(), sizeof(rebootDelayString));
      rebootDelayString[sizeof(rebootDelayString) - 1] = 0;  // per sicurezza metto l'ultimo carattere e' zero
      rebootDelay = strtoul(rebootDelayString, NULL, 10);
    }
    //11
    if (request->getParam(HOST_PING_TIMEOUT_PARAM)->value() != "") {
      inputMessage = request->getParam(HOST_PING_TIMEOUT_PARAM)->value();
      strncpy(hostPingTimeoutString, inputMessage.c_str(), sizeof(hostPingTimeoutString));
      hostPingTimeoutString[sizeof(hostPingTimeoutString) - 1] = 0;  // per sicurezza metto l'ultimo carattere e' zero
      hostPingTimeout = strtoul(hostPingTimeoutString, NULL, 10);
    }

    Serial.println();
    Serial.printf("1 %s = %s \n\r", SSID_PARAM, ssid);
    Serial.printf("2 %s = %s \n\r", PASSWORD_PARAM, password);
    Serial.printf("3 %s = %s \n\r", SETUP_PORTAL_SSID_PARAM, portalSSID);
    Serial.printf("4 %s = %s \n\r", SETUP_PORTAL_PASSWORD_PARAM, portalPassword);
    Serial.printf("5 %s = %s \n\r", REMOTE_HOST1_PARAM, remoteHost1);
    Serial.printf("6 %s = %s \n\r", REMOTE_HOST2_PARAM, remoteHost2);
    Serial.printf("7 %s = %s \n\r", REMOTE_HOST3_PARAM, remoteHost3);
    Serial.printf("8 %s = %s \n\r", REMOTE_HOST4_PARAM, remoteHost4);
    Serial.printf("9 %s = %lu \n\r", WIFI_RESTART_TIMEOUT_PARAM, wifiRstTimeout);
    Serial.printf("10 %s = %d \n\r", REBOOT_DELAY_PARAM, rebootDelay);
    Serial.printf("11 %s = %lu \n\r", HOST_PING_TIMEOUT_PARAM, hostPingTimeout);

    snprintf(longString, sizeof(longString),
             "Parameters sent to ARR:<br>"
             "1) &#60 %s &#62= %s<br>"
             "2) &#60 %s &#62= %s<br>"
             "3) &#60 %s &#62= %s<br>"
             "4) &#60 %s &#62= %s<br>"
             "5) &#60 %s &#62= %s<br>"
             "6) &#60 %s &#62= %s<br>"
             "7) &#60 %s &#62= %s<br>"
             "8) &#60 %s &#62= %s<br>"
             "9) &#60 %s &#62= %lu<br>"
             "10) &#60 %s &#62= %d<br>"
             "11) &#60 %s &#62= %lu<br>"


             "<br>"
             "<a href=\\>Return to Home Page</a>",
             SSID_PARAM, ssid, //1
             PASSWORD_PARAM, password,  //2
             SETUP_PORTAL_SSID_PARAM, portalSSID,  //3
             SETUP_PORTAL_PASSWORD_PARAM, portalPassword,  //4
             REMOTE_HOST1_PARAM, remoteHost1,  //5
             REMOTE_HOST2_PARAM, remoteHost2,  //6
             REMOTE_HOST3_PARAM, remoteHost3,  //7
             REMOTE_HOST4_PARAM, remoteHost4,  //8
             WIFI_RESTART_TIMEOUT_PARAM, wifiRstTimeout,  //9
             REBOOT_DELAY_PARAM, rebootDelay,  //10
             HOST_PING_TIMEOUT_PARAM, hostPingTimeout  //11
    );
    request->send(200, "text/html", longString);
    webParametersSet = true;
  });
  
  /*********************************************************************************
  * invoked when a non existing page is requested
  **********************************************************************************/
  server.onNotFound(pageNotFound);
  server.begin();
  Serial.println("Web portal active");
  digitalWrite(LED_3_PIN, HIGH);
  
  int contatore = 1;
  while (!webParametersSet) { //wait (stay on the page) until the parameters are set
    delay(1000);
    contatore++;
    /* the following shows how long the portal page has been on */
    //Serial.print(".");
    //if ((contatore % 60) == 0) Serial.println(contatore);
  }
  
  //******* here a best practice would be to close the web serve, however for this project the ESP will be rebooted afterwards so 
  // the server closure is implicit in the reboot 
  DEBUG_PRINTLN("******* WEB PORTAL END");
  digitalWrite(LED_2_PIN, LOW);
  digitalWrite(LED_2_PIN, LOW);
}

/*************************************************************************
 * scan all the available networks and store the results in HTML text in the tableRows string (global variable
 *************************************************************************/
void showNetworks() {
  typedef struct {
    int id;
    char ssid[40];
    int32_t rssi;
    uint8_t encryptionType;
    int32_t channel;
  } Network;

  int n = WiFi.scanNetworks(false, false);
  Network listOfNetworks[n];

  for (int i = 0; i < n; i++)  // ...initialize it
  {
    listOfNetworks[i].id = i;
    strcpy(listOfNetworks[i].ssid, WiFi.SSID(i).c_str());
    listOfNetworks[i].rssi = WiFi.RSSI(i);
    listOfNetworks[i].encryptionType = WiFi.encryptionType(i);
    listOfNetworks[i].channel = WiFi.channel(i);
  }
  tableRows[0] = '\0';         //clear string
  for (int i = 0; i < n; i++)  // ...initialize it
  {
    int RSSIpct = min(max(2 * (listOfNetworks[i].rssi + 100), 0), 100);
    char RSSIvisual[5] = "poor";
    if (RSSIpct > 54) strncpy(RSSIvisual, "avg ", sizeof(RSSIvisual));
    if (RSSIpct > 67) strncpy(RSSIvisual, "good", sizeof(RSSIvisual));
#ifdef DEBUG
    Serial.printf("| %32s | %2d | %4d | %3d%% | %s | %15s |\n\r",
                  listOfNetworks[i].ssid,
                  listOfNetworks[i].channel,
                  listOfNetworks[i].rssi,
                  RSSIpct,
                  RSSIvisual,
                  translateEncryptionType(listOfNetworks[i].encryptionType).c_str());
#endif  
    snprintf(trText, sizeof(trText), "<tr>"
                                     "<td>%s</td>"       //SSID
                                     "<td>%d</td>"       //Channel
                                     "<td>%d</td>"       //RSSI
                                     "<td>%d%%%% </td>"  //RSSIpct
                                     "<td>"
                                     "<div class=\"container\">"
                                     "<div class=\"wifistrenght %s\" style=\"width: %d%%%%;\"/>"  //quality and pct
                                     "</div>"
                                     "</td>"
                                     "<td>%s</td>"  //encryption
                                     "</tr>\n\r",
             listOfNetworks[i].ssid,
             listOfNetworks[i].channel,
             listOfNetworks[i].rssi,
             RSSIpct,
             RSSIvisual,
             RSSIpct,
             translateEncryptionType(listOfNetworks[i].encryptionType).c_str());

    DEBUG_PRINTF("length of table Rows = %d\n\r", strlen(tableRows));
    if (strlen(tableRows) + strlen(trText) < sizeof(tableRows)) {
      strncat(tableRows, trText, sizeof(tableRows));
    } else {
      tableRowsTruncated = true;
      //DEBUG_PRINTF("DEBUG LINE %d\n\r", __LINE__);
      DEBUG_PRINTLN("table truncated");
    }
  }
  DEBUG_PRINTLN(tableRows);
}

/***********************************************************
 * decodes the type of WIFI encryption
 ***********************************************************/
String translateEncryptionType(uint8_t encryptionType) {
  switch (encryptionType) {
    case (WIFI_AUTH_OPEN):
      return "Open";
    case (WIFI_AUTH_WEP):
      return "WEP";
    case (WIFI_AUTH_WPA_PSK):
      return "WPA_PSK";
    case (WIFI_AUTH_WPA2_PSK):
      return "WPA2_PSK";
    case (WIFI_AUTH_WPA_WPA2_PSK):
      return "WPA_WPA2_PSK";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
      return "WPA2_ENTERPRISE";
    default:
      return "Security UNKOWN";
  }
}

/***************************************************
 * manage requests of web pages not defined (invoked by
 server.onNotFound)
 ***************************************************/
void pageNotFound(AsyncWebServerRequest* request) {
  DEBUG_PRINTLN("** notfound page");
  request->send_P(404, "text/html", notfound_html);
}

/***************************************************
 * replaces the placeholders in the HTML page
 * invoked when when the index.html page is shown
  **************************************************/
String replacePlaceholders(const String& var) {
  //Serial.println(var);
  if (var == "inputfield1") {
    return String(SSID_PARAM);
  } else if (var == "currentValue1") {
    return String(ssid);

  } else if (var == "inputfield2") {
    return String(PASSWORD_PARAM);
  } else if (var == "currentValue2") {
    return String(password);

  } else if (var == "inputfield3") {
    return String(SETUP_PORTAL_SSID_PARAM);
  } else if (var == "currentValue3") {
    return String(portalSSID);

  } else if (var == "inputfield4") {
    return String(SETUP_PORTAL_PASSWORD_PARAM);
  } else if (var == "currentValue4") {
    return String(portalPassword);

  } else if (var == "inputfield5") {
    return String(REMOTE_HOST1_PARAM);
  } else if (var == "currentValue5") {
    return String(remoteHost1);

  } else if (var == "inputfield6") {
    return String(REMOTE_HOST2_PARAM);
  } else if (var == "currentValue6") {
    return String(remoteHost2);

  } else if (var == "inputfield7") {
    return String(REMOTE_HOST3_PARAM);
  } else if (var == "currentValue7") {
    return String(remoteHost3);

  } else if (var == "inputfield8") {
    return String(REMOTE_HOST4_PARAM);
  } else if (var == "currentValue8") {
    return String(remoteHost4);

  } else if (var == "inputfield9") {
    return String(WIFI_RESTART_TIMEOUT_PARAM);
  } else if (var == "currentValue9") {
    return String(wifiRstTimeout);

  } else if (var == "inputfield10") {
    return String(REBOOT_DELAY_PARAM);
  } else if (var == "currentValue10") {
    return String(rebootDelay);

  } else if (var == "inputfield11") {
    return String(HOST_PING_TIMEOUT_PARAM);
  } else if (var == "currentValue11") {
    return String(hostPingTimeout);

  } else if (var == "wifiNetworksAvailable") {
    return String(tableRows);
  } else if (var == "tableRowsWarning") {
    if (tableRowsTruncated) return String("<b>Too many networks: list truncated</b><br>");
    else return String("");
  }
  return String(var + "=variabile non definita");
}
