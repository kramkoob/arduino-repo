// "Good enough" attempt to get an Uno WiFi Rev2 to talk to a Tello drone
// by Thomas Dodds for ATU IEEE

//#include <SPI.h>
//#include <WiFiNINA.h>
//#include <WiFiUdp.h>
//#include "wifisecrets.h"
#include "protocol.h"

// WiFiUDP udp;

void setup() {
  Serial.begin(9600);
  /*
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }
  
  while (status != WL_CONNECTED) {
    Serial.print("Connecting: ");
    Serial.println(TELLO_WIFI_SSID);
    status = WiFi.begin(TELLO_WIFI_SSID, TELLO_WIFI_PASS);

    // wait 10 seconds for connection:
    delay(10000);
  }
  //Serial.println("Connected");
  */
  //udp.begin(TELLO_PORT);

  Packet height(SET_ALT_LIMIT_CMD);
  height.add_byte(0x1e);
  height.add_byte(0x00);
  height.print_buffer(Serial);

  Packet takeoff(TAKEOFF_CMD);
  takeoff.fixup();
  takeoff.print_buffer(Serial);

  Packet land(LAND_CMD);
  land.add_byte(0x00);
  land.fixup();
  land.print_buffer(Serial);
  
  //udp.beginPacket(TELLO_ADDR, TELLO_PORT);
  //udp.write(pkt.buffer, pkt.size());
  //udp.endPacket();
}

void loop() {
  
}
