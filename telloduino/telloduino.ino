// "Good enough" attempt to get an Uno WiFi Rev2 to talk to a Tello drone
// by Thomas Dodds for ATU IEEE

#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include "wifisecrets.h"
#include "protocol.h"

int status = WL_IDLE_STATUS;
WiFiUDP udp;

void setup() {
  Serial.begin(9600);
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
  Serial.println("Connected");

  udp.begin(TELLO_RECV_PORT);

  // command mode
  Serial.print("command:\n\t[string packet]\n");
  Packet command("command");
  
  udp.beginPacket(TELLO_ADDR, TELLO_SEND_PORT);
  udp.write(command.buffer, command.size());
  udp.endPacket();
  delay(1000);

  // set height 30 inches
  Serial.print("set_alt_limit:\n\t");
  Packet height(SET_ALT_LIMIT_CMD);
  height.add_byte(0x1e);
  height.add_byte(0x00);
  height.print_buffer(Serial);

  udp.beginPacket(TELLO_ADDR, TELLO_SEND_PORT);
  udp.write(height.buffer, height.size());
  udp.endPacket();

  // takeoff
  Serial.print("takeoff:\n\t");
  Packet takeoff(TAKEOFF_CMD);
  takeoff.fixup();
  takeoff.print_buffer(Serial);

  udp.beginPacket(TELLO_ADDR, TELLO_SEND_PORT);
  udp.write(takeoff.buffer, takeoff.size());
  udp.endPacket();

  // wait 10 seconds
  delay(10000);

  // land
  Serial.print("land:\n\t");
  Packet land(LAND_CMD);
  land.add_byte(0x00);
  land.fixup();
  land.print_buffer(Serial);

  udp.beginPacket(TELLO_ADDR, TELLO_SEND_PORT);
  udp.write(land.buffer, land.size());
  udp.endPacket();  
}

void loop() {
  
}
