/*
 * Program by Tabea Röthemeyer (@tabeatheunicorn)
 * Dieses Programm gibt die vom BME280 Sensor gemessenen Werte aus und sendet die Werte per LoRa Paket.
 * Immer wenn ein Paket erfolgreich gesendet wurde, soll eine Minute später erneut der Sensor ausgelesen und als Paket verschickt werden.
 * Dazu wird in der onEvent-Funktion auf das Event TX_COMPLETE gewartet. Die Zeitdauer ist in der Variablen TIMEINTERVAL festgelegt.
 */
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <SPI.h> //Serial Peripheral Interface
#include <lmic.h>
#include <hal/hal.h>
#include <math.h> //Um Runden zu können etc.
#include "node_specifications.h"

//Using I2C as Protocol. has to be global as variable is used in setup and loop
Adafruit_BME280 bme; //I2C as no SPI pins are defined.

static osjob_t bme_sendjob;
const int TX_INTERVAL = 60; //zeit zwischen erfolgreich verschicktem Paket und neuem Paket in Sekunden

// Pin mapping for Heltec_WIFI_LoRa_32 V2
const lmic_pinmap lmic_pins = {
  .nss = 18,      
  .rxtx = LMIC_UNUSED_PIN,      
  .rst = 14,        
  .dio = {26, 35, LMIC_UNUSED_PIN},
};


// implementation of functions that are too long for main arduino project.
void os_getDevEui (u1_t* buf) {
  memcpy_P(buf, DEVEUI, 8);
}
void os_getArtEui (u1_t* buf) {
  memcpy_P(buf, APPEUI, 8);
}
void os_getDevKey (u1_t* buf) {
  memcpy_P(buf, APPKEY, 16);
}

/*
 * Diese Funktion ist besonders lang, da sie festlegt, was bei den möglichen Events passieren soll. Event TXCOMPLETE für abgeschlossene Übertragung -> hier neues Paket in Auftrag geben
 */
void onEvent (ev_t ev) {
    Serial.print(os_getTime());
    Serial.print(": ");
    switch(ev) {
        case EV_SCAN_TIMEOUT:
            Serial.println(F("EV_SCAN_TIMEOUT"));
            break;
        case EV_BEACON_FOUND:
            Serial.println(F("EV_BEACON_FOUND"));
            break;
        case EV_BEACON_MISSED:
            Serial.println(F("EV_BEACON_MISSED"));
            break;
        case EV_BEACON_TRACKED:
            Serial.println(F("EV_BEACON_TRACKED"));
            break;
        case EV_JOINING:
            Serial.println(F("EV_JOINING"));
            break;
        case EV_JOINED:
            Serial.println(F("EV_JOINED"));
            os_setCallback(&bme_sendjob, bme_do_send); //first call when successfully joined
            break;
        case EV_RFU1:
            Serial.println(F("EV_RFU1"));
            break;
        case EV_JOIN_FAILED:
            Serial.println(F("EV_JOIN_FAILED"));
            break;
        case EV_REJOIN_FAILED:
            Serial.println(F("EV_REJOIN_FAILED"));
            break;
        case EV_TXCOMPLETE:
            Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
            if (LMIC.txrxFlags & TXRX_ACK)
              Serial.println(F("Received ack"));
            if (LMIC.dataLen) {
              Serial.println(F("Received "));
              Serial.println(LMIC.dataLen);
              Serial.println(F(" bytes of payload"));
            }
            // Schedule next transmission
            os_setTimedCallback(&bme_sendjob, os_getTime()+sec2osticks(TX_INTERVAL), bme_do_send);
            break;
        case EV_LOST_TSYNC:
            Serial.println(F("EV_LOST_TSYNC"));
            break;
        case EV_RESET:
            Serial.println(F("EV_RESET"));
            break;
        case EV_RXCOMPLETE:
            // data received in ping slot
            Serial.println(F("EV_RXCOMPLETE"));
            break;
        case EV_LINK_DEAD:
            Serial.println(F("EV_LINK_DEAD"));
            break;
        case EV_LINK_ALIVE:
            Serial.println(F("EV_LINK_ALIVE"));
            break;
         default:
            Serial.println(F("Unknown event"));
            break;
    }
}
//https://www.thethingsnetwork.org/forum/t/how-to-efficiently-assemble-and-extract-a-mix-of-integer-and-float-data-for-ttn/22908

typedef struct sensorData {
  float temperature;
  int humidity;
  int pressure;
};

const int PACKET_SIZE = sizeof(sensorData);

typedef union LoRa_Packet {
  sensorData sensor;
  byte LoRaPacketBytes[PACKET_SIZE];
};


void bme_do_send(osjob_t* j){
    // Check if there is not a current TX/RX job running
    if (LMIC.opmode & OP_TXRXPEND) {
        Serial.println(F("OP_TXRXPEND, not sending"));
    } else {
        //read in data from bme. every "frame" is 8 bit long and contains one value.
        // Prepare upstream data transmission at the next possible time. if calling function multiple times before tx_complete, data is overwritten!
        
        float temp = bme.readTemperature();
        int humidity = bme.readHumidity();
        int pressure = bme.readPressure();
        Serial.println(temp);
        Serial.println(humidity);
        Serial.println(pressure);

        LoRa_Packet mypacket;
        mypacket.sensor.temperature = temp;
        mypacket.sensor.humidity = humidity;
        mypacket.sensor.pressure = pressure;
         
        LMIC_setTxData2(1, mypacket.LoRaPacketBytes, sizeof(mypacket.LoRaPacketBytes), 0); //1. port, 2. daten, 3. datengröße , 4. confirmed
        Serial.println(F("Packet queued"));
    }
    // Next TX is scheduled after TX_COMPLETE event.
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (!bme.begin()){
    Serial.println("Could not find BME Sensor, check wiring.");
  }
  //lmic setup
  os_init();
  LMIC_reset();
  LMIC_startJoining(); // starting to connect, calling bme_do_send first when join was succesfull
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(F("Starting"));
  os_runloop();

}
