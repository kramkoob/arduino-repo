// "Good enough" attempt to get an Uno WiFi Rev2 to talk to a Tello drone
// by Thomas Dodds for ATU IEEE

// #include <SPI.h>
// #include <WiFiNINA.h>
#include "Packet.h"
// #include "wifisecrets.h"

void setup() {
  // open serial
  Serial.begin(9600);

  // create packet
  Packet pkt(TAKEOFF_CMD);
  pkt.fixup();

  // print packet buffer to serial
  Serial.println("");
  Serial.println("--BEGIN PACKET--");
  for(uint8_t k = 0; k < pkt.length(); k++){
    Serial.print(pkt.get_buffer(k), HEX);
    if(k + 1 < pkt.length()){
      Serial.print(":");
    }
  }
  Serial.println("");
  Serial.println("--END PACKET--");
}

void loop() {
  
}
