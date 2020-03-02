/*****************************************************
 * Written by Tabea Röthemeyer(@tabeatheunicorn) 2020 
 * 
 ****************************************************/
#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include <Wire.h>

#include "node_specifications.h"
#include "lmic_functions.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
void do_send(osjob_t* j){
  Serial.println("Starting to send");
  // Check if there is not a current TX/RX job running
  if (LMIC.opmode & OP_TXRXPEND) {
      Serial.println("OP_TXRXPEND, not sending");
  } else {
      // Prepare upstream data transmission at the next possible time.
      // LMIC_setTxData2 (u1_t port, xref2u1_t data, u1_t dlen, u1_t confirmed)
      uint8_t mydata[] = {25};
      LMIC_setTxData2(1, mydata, sizeof(mydata) - 1, 0);
      Serial.println("Packet queued");
  }
  // Next TX is scheduled after TX_COMPLETE event.
}
//////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting");
  
  // setup LoRa
  os_init();
  LMIC_reset();

  // setup Sensor/Wiring
  
 }
 
void loop() {
  // structure of main as suggested in lmic documentation 2.1.2 https://github.com/matthijskooijman/arduino-lmic/blob/master/doc/LMiC-v1.5.pdf
   //do_send(&sendjob);
   os_runloop_once();
}
