/*  
 ~~~~~~~
 uvr2web
 ~~~~~~~
 © Elias Kuiter 2013 (http://elias-kuiter.de)
 
 dump.ino:
 Ausgabe der Daten auf der seriellen Schnittstelle
 Data output via serial interface
 
 */


namespace Dump {

  void start() {
    meta();
    sensors();
    heat_meters();
    outputs();
    speed_steps();
  }

  void meta() {
    Process::fetch_timestamp();
    Serial.print("\n\nUVR1611 on ");
    if (Process::timestamp.day < 10)
      Serial.print("0");
    Serial.print(Process::timestamp.day);
    Serial.print("/");
    if (Process::timestamp.month < 10)
      Serial.print("0");
    Serial.print(Process::timestamp.month);
    Serial.print("/");
    Serial.print(Process::timestamp.year);
    Serial.print(" at ");
    if (Process::timestamp.hour < 10)
      Serial.print("0");
    Serial.print(Process::timestamp.hour);
    Serial.print(":");
    if (Process::timestamp.minute < 10)
      Serial.print("0");
    Serial.print(Process::timestamp.minute);
    if (Process::timestamp.summer_time)
      Serial.println(" (DST)");
    else
      Serial.println(" (not DST)");
  }

  void sensors() {
    Serial.println("Sensordaten lesen");
    for (int i = 1; i <= 16; i++) {
      Process::fetch_sensor(i);
      sensor();
    }
  }

  void sensor() {
    int sNr = Process::sensor.number;
    if ((Process::sensor.value <1200) && (Process::sensor.value > -40)) {
      String sValue = String(Process::sensor.value);
      SensorValue[sNr] = sValue;
    }
  }

  void heat_meters() {
    Serial.println("Wärmemengenzähler lesen");
    Process::fetch_heat_meter(1);
    heat_meter();
    Process::fetch_heat_meter(2);
    heat_meter();
  }

  void heat_meter() {
    if (Process::heat_meter.number == 1) {
      if (Process::heat_meter.current_power <200) { WMZ1[1] = Process::heat_meter.current_power; }
      if (Process::heat_meter.kwh <100) {
        WMZ1[2] = Process::heat_meter.kwh;
        WMZ1[3] = Process::heat_meter.mwh;
      }
    }
    else {
      if (Process::heat_meter.current_power <200) { WMZ2[1] = Process::heat_meter.current_power; }
      if (Process::heat_meter.kwh <100) {
        WMZ2[2] = Process::heat_meter.kwh;
        WMZ2[3] = Process::heat_meter.mwh;
      }
    }
  }

  void outputs() {
    Serial.println("Ausgänge lesen");
    for (int i = 1; i <= 13; i++) {
      Ausgang[i]= Process::fetch_output(i);
    }
  }

  void speed_steps() {
    Serial.println("Drehzahl lesen");
    speed_step(1);
    speed_step(2);
    speed_step(6);
    speed_step(7);
  }

  void speed_step(int output) {
    switch (output) {
      case 1: {
        Drehzahl[1] = Process::fetch_speed_step(output);
      }
      break;
      case 2: {
        Drehzahl[2] = Process::fetch_speed_step(output);
      }
      break;
      case 6: {
        Drehzahl[3] = Process::fetch_speed_step(output);
      }
      break;
      case 7: {
        Drehzahl[4] = Process::fetch_speed_step(output);
      }
      break;
    }
  }
}

