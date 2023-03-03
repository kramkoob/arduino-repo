// "Good enough" attempt to get an Uno WiFi Rev2 to talk to a Tello drone
// by Thomas Dodds for ATU IEEE

// #include <SPI.h>
// #include <WiFiNINA.h>
#include "protocol.h"
// #include "wifisecrets.h"

void setup() {
  // open serial
  Serial.begin(9600);

  // create packet
  Packet pkt(TAKEOFF_CMD);
  pkt.fixup();

  // print packet buffer to serial
  Serial.println("--BEGIN PACKET--");
  pkt.print_buffer(Serial);
  Serial.println("--END PACKET--");
}

void loop() {
  
}
