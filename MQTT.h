WiFiClient wlanClient;
PubSubClient mqtt_client(wlanClient);


boolean mqtt_connect(void) {
  if (!wlan_status()) {
    return false;
  } else {
    int counter = 0;
  
    mqtt_client.setServer(mqtt_server, 1883);
    //mqtt_client.setCallback(callback);
    
    mqtt_client.connect("BL-NET");
    Serial.print("MQTT Connection: ");
    while (!mqtt_client.connected()) 
    {
      delay(500);
      Serial.print(".");
      counter++;
      if (counter > 15 ) {
        Serial.println("Verbindung konnte nicht aufgebaut werden!");
        ESP.reset();
        delay(2000);
        return false;
      }
    }
    Serial.println ("OK");
    return true;
  }
}

void mqtt_daten_senden() {
  Serial.println ("MQTT - Senden!");
  String topic = "";

  // Sensordaten über mqtt versenden
  for (int sv = 1; sv <= 16; sv++) {
    if (mqtt_client.connected()) {
      topic = "/openHAB/UVR1611/Sensor" + String(sv);
      Serial.println("MQTT: " + topic + ": "+ String(SensorValue[sv]));
      mqtt_client.publish(topic.c_str(), SensorValue[sv].c_str());
    } 
    else {
      mqtt_connect();
    }
  }
  if (mqtt_client.connected()) {
  //Wärmemengenzähler über mqtt versenden
    mqtt_client.publish("/openHAB/UVR1611/WMZ1currentPower", WMZ1[1].c_str());
    mqtt_client.publish("/openHAB/UVR1611/WMZ1kwh", WMZ1[2].c_str());
    mqtt_client.publish("/openHAB/UVR1611/WMZ1mwh", WMZ1[3].c_str());
    mqtt_client.publish("/openHAB/UVR1611/WMZ2currentPower", WMZ2[1].c_str());
    mqtt_client.publish("/openHAB/UVR1611/WMZ2kwh", WMZ2[2].c_str());
    mqtt_client.publish("/openHAB/UVR1611/WMZ2mwh", WMZ2[3].c_str());
  } 
  else {
      mqtt_connect();
    }

  // Zustände der Ausgänge übertragen
  for (int sv = 1; sv <= 13; sv++) {
    if (mqtt_client.connected()) {
      topic = "/openHAB/UVR1611/Ausgang" + String(sv);
      Serial.println("MQTT: " + topic + ": "+ Ausgang[sv]);
      mqtt_client.publish(topic.c_str(), Ausgang[sv]? "1" : "0");
    } 
    else {
      mqtt_connect();
    }
  }

  // Drehzahl Ausgänge übertragen
  if (mqtt_client.connected()) {
    for (int sv = 1; sv <= 4; sv++) {
      topic = "/openHAB/UVR1611/Drehzahl" + String(sv);
      Serial.println("MQTT: " + topic + ": "+ Drehzahl[sv]);
      mqtt_client.publish(topic.c_str(), Drehzahl[sv].c_str());
    } 
  } else {
      mqtt_connect();
    }

  // WLAN RSSI
  if (mqtt_client.connected()) {
    rssi = WiFi.RSSI();
    topic = "/openHAB/UVR1611/RSSI";
    Serial.println("MQTT: " + topic + ": "+ rssi);
    mqtt_client.publish(topic.c_str(), rssi.c_str());
  } else {
      mqtt_connect();
    }
}
