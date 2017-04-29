/*  
 ~~~~~~~
 uvr2web
 ~~~~~~~
 © Elias Kuiter 2013 (http://elias-kuiter.de)
 
 process.h:
 Processing of saved data frames
 
 */

namespace Process {

  // ein Datenrahmen hat 64 Datenbytes + SYNC, also 64 * (8+1+1) + 16 = 656
  // 656 * 2 = 1312 (das Doppelte eines Datenrahmens wird gespeichert,
  // so dass ein ganzer Datenrahmen da ist)
  // one data frame has 64 data bytes + SYNC, so 64 * (8+1+1) + 16 = 656
  // 656 * 2 = 1312 (twice as much as a data frame is saved
  // so there's one complete data frame
  const int bit_number = (64 * (8 + 1 + 1) + 16) * 2 + additionalBits;
  byte data_bits[bit_number / 8 + 1]; // jedes Bit wird in eine Bitmap einsortiert // every bit gets sorted into a bitmap
  int start_bit; // erstes Bit des Datenrahmens // first bit of data frame
  
  // Sensortypen
  // sensor types
#define UNUSED      0b000
#define DIGITAL     0b001
#define TEMP        0b010
#define VOLUME_FLOW 0b011
#define RAYS        0b110
#define ROOM   0b111

  // Modi für Raumsensor
  // room sensor modes
#define AUTO        0b00
#define NORMAL      0b01
#define LOWER       0b10
#define STANDBY     0b11

  // Zeitstempel der Regelung
  // heating control timestamp
  typedef struct {
    byte minute;
    byte hour;
    byte day;
    byte month;
    int year;
    boolean summer_time;
  } 
  timestamp_t;
  timestamp_t timestamp;

  // sensor
  typedef struct {
    byte number;
    byte type;
    byte mode;
    boolean invalid;
    float value;
  }
  sensor_t;
  sensor_t sensor;

  // Wärmemengenzähler
  // heat meter
  typedef struct {
    byte number;
    boolean invalid;
    float current_power;
    float kwh;
    int mwh;
  }
  heat_meter_t;
  heat_meter_t heat_meter;

  // Datenrahmen
  // data frame
  void start(); // Datenrahmen auswerten
  boolean prepare(); // Datenrahmen vorbereiten
  int analyze(); // Datenrahmen analysieren
  void invert(); // Datenrahmen invertieren
  byte read_bit(int pos); // aus Bitmap lesen // read from bitmap
  void write_bit(int pos, byte set); // Bitmap beschreiben // write to bitmap
  void trim(); // Datenrahmen in Bitmap schreiben // remove start and stop bits
  boolean check_device(); // Datenrahmen überprüfen // verify data frame

  // Informationen auslesen
  // readout information
  void fetch_timestamp(); // Zeitstempel
  void fetch_sensor(int sensor); // Sensor
  void fetch_heat_meter(int heat_meter); // Wärmemengenzähler
  boolean fetch_output(int output); // Ausgang
  int fetch_speed_step(int output); // Drehzahlstufe

}
