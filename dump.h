/*  
 ~~~~~~~
 uvr2web
 ~~~~~~~
 © Elias Kuiter 2013 (http://elias-kuiter.de)
 
 dump.h:
 Ausgabe der Daten auf der seriellen Schnittstelle
 Data output via serial interface
 
 */

namespace Dump {

  void start(); // Ausgabe aller Daten // output all data
  void meta(); // Metadaten (Regelung + Zeitstempel) // meta data (heating control + timestamp)
  void bytes();
  void bits();

  void sensors(); // Sensoren
  void heat_meters(); // Wärmemengenzähler
  void outputs(); // Ausgänge
  void speed_steps(); // Drehzahlstufen

  // Ausgabe einzelner Elemente
  // output of particular elements
  void heat_meter();
  void sensor();
  void speed_step(int output);

}

