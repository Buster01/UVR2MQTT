bool wlan_connect(void) {
  
  int counter = 0;
  bool wlan_loop = false;
  String wlan_txt = "SSID: " + String(ssid);

  //text_anzeigen(wlan_txt, "", "");
  Serial.print("Connecting to ");
  Serial.print(ssid);

  WiFi.begin(ssid, wlan_passwd);
  while (!wlan_loop) {
    if (WiFi.status() == WL_CONNECTED) { wlan_loop = true; }
    if (counter > 30) { wlan_loop = true; }
    counter++;
    Serial.print(".");
    delay(500);
    }
    Serial.println();
    Serial.print("Status: ");
    switch (WiFi.status()) {  
      case WL_CONNECTED:
        Serial.println("Verbunden!");
       // text_anzeigen("WLAN verbunden!", "", "");
        return true;
        break;

      case WL_NO_SHIELD:
        Serial.println("kein WLAN Shield gefunden!");
       // text_anzeigen("kein WLAN Shield!", "", "");
        return false;
        break;

      case WL_NO_SSID_AVAIL:
        Serial.println("kein SSID gefunden!");
        // text_anzeigen("kein SSID gefunden!", "", "");
        return false;
        break;

      case WL_CONNECT_FAILED:
        Serial.println("WLAN Verbindung fehlgeschlagen!");
        // text_anzeigen("Verbindung fehlgeschlagen!", "", "");
        return false;
        break;

      case WL_CONNECTION_LOST:
        Serial.println("WLAN Verbindung verloren!");
        // text_anzeigen("WLAN Verb. Fehlgeschlagen!", "", "");
        return false;
        break;

      case WL_DISCONNECTED:
        Serial.println("WLAN Verbindung geschlossen!");
        // text_anzeigen("WLAN Verb. geschlossen!", "", "");
        return false;
        break;
      }
      if (counter > 30) {
        Serial.println("WLAN Verbindung dauert zu lange!");
        // text_anzeigen("Verb. dauert zu lange!", "", "");
        return false;
      }
  }

bool wlan_status(void) {
  switch (WiFi.status()) {
    case WL_CONNECTED:
      return true;
      break;

    case WL_CONNECTION_LOST:
      Serial.println("Verbindung verloren!");
      if (!wlan_connect()) { Serial.println ("WLAN Verbindung fehlgeschlagen!");}
      return false;
      break;

    case WL_DISCONNECTED:
      Serial.println("Verbindung getrennt!");
      if (!wlan_connect()) { Serial.println ("WLAN Verbindung fehlgeschlagen!");}
      return false;
      break;

    case WL_CONNECT_FAILED:
      Serial.println("Verbindung wird wieder hergestellt!");
      if (!wlan_connect()) { Serial.println ("WLAN Verbindung fehlgeschlagen!");}
      return false;
      break;
  }
}
