
const byte dataPin = D2; 
const byte interrupt = D2;
int upload_interval = 60000;
const int additionalBits = 0;
int beginn = millis();
String SensorValue[17];
String WMZ1[3];
String WMZ2[3];
bool Ausgang[14];
String Drehzahl[5];
String rssi;

const char* ssid = "WLAN Name";  // SSID deines WLAN Netzwerkes
const char* wlan_passwd = "dasPasswort"; // Passwort deines WLAN Netzwerkes
char* esp_hostname = "BL-NET";

const char* mqtt_server = "mqtt-server"; // MQTT Server

extern "C" { 
  #include "user_interface.h" 
  }

#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "WLAN.h"
#include "MQTT.h"
#include "receive.h"
#include "process.h"
#include "dump.h"



void setup() {
  wifi_station_set_hostname(esp_hostname);
  Serial.begin(115200);
  // WLAN Verbindung
  if (!wlan_connect()) {
      Serial.println ("WLAN Verbindung fehlgeschlagen!");
      Serial.println ("Reset!");
      delay(2000);
      ESP.reset();
    } else {
      Serial.println();
      Serial.print("Verbindung! RSSI: "); Serial.print(WiFi.RSSI()); Serial.println(" dBi");
      Serial.print("IP-Adresse: "); Serial.println(WiFi.localIP());
    }
  Receive::start();
}

void loop() {
  if (mqtt_client.connected()) {
    mqtt_client.loop();
  }
  if (!Receive::receiving) {
    Process::start(); // Daten auswerten // process data
    Receive::start(); // Daten sammeln // receive data
  }
  if (millis() - beginn > upload_interval) {
    if (mqtt_connect()) {
      mqtt_daten_senden();
      beginn=millis();
    }
  }
}

