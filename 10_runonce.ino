/************************************************************************
 * initialization
 ************************************************************************/
void RunOnce() {
  Serial.begin(115200);
  delay(100);  // serve per dargli il tempo di inizializzarsi
  // delete old config
  WiFi.disconnect(true);
  WiFi.onEvent(WiFiEvent);
  Serial.println();
  Serial.println();
  Serial.println("************************ Start of ARR (Automatic Router Rebooter **");
  pinMode(RESET_WIFI_SETTINGS_PIN, INPUT_PULLUP);
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(RELAIS_PIN, OUTPUT);
  digitalWrite(RELAIS_PIN, LOW);

  // init preferences
  prefs.begin("WIFIParms", false);  // the first parameter is the name of the memory area , the seconds indicates readonly

  //Flash once all the leds
  digitalWrite(LED_1_PIN, HIGH);
  digitalWrite(LED_2_PIN, HIGH);
  digitalWrite(LED_3_PIN, HIGH);
  delay(500);
  digitalWrite(LED_1_PIN, LOW);
  digitalWrite(LED_2_PIN, LOW);
  digitalWrite(LED_3_PIN, LOW);

  //************** check if at startup we need to set up the portal parameters or factory reset
  if (digitalRead(RESET_WIFI_SETTINGS_PIN) == 0) buttonpressed();
  readPrefs();
  WiFi.mode(WIFI_STA);         //start ARR wifi as a client
  WiFi.begin(ssid, password);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
  lastWifiOK = millis();
}

/***********************************************************
 * if button is pressed at startup for more than 15 seconds do a factory reset and 
 * aunch the web portal. 
 * otherwise if button is pressed at startup for less than 15 seconds, just launch the web portal
 ************************************************************/
void buttonpressed() {
  do {
    //wait until reset pin is released
  } while ((digitalRead(RESET_WIFI_SETTINGS_PIN) == 0) && (millis() <= FACTORY_RESET_WAIT));
  if (millis() >= FACTORY_RESET_WAIT) {  //button was pressed for more than 15 seconds: -> a facory reset is requested before web portal is displayed
    //factory reset; init all parameters
    DEBUG_PRINTLN(">>>>>>>>>>>>>>>>>>>> FACTORY RESET");
    //fast blinking of a led to signal that facory reset has been invoked
    for (int i = 0; i < 15; i++) {
      digitalWrite(LED_1_PIN, HIGH);
      digitalWrite(LED_3_PIN, HIGH);
      digitalWrite(LED_2_PIN, HIGH);
      delay(100);
      digitalWrite(LED_1_PIN, LOW);
      digitalWrite(LED_3_PIN, LOW);
      digitalWrite(LED_2_PIN, LOW);
      delay(100);
    }
    factoryReset();
  }

  DEBUG_PRINTLN("**** PARAMETERS WEB PORTAL PARAMETERS SETUP *****");
  digitalWrite(LED_3_PIN, LOW);
  readPrefs();
  webPortal();
  writePrefs();
  ESP.restart();  // after the setup of the parameters using the web interface the ESP module is restarted
}
