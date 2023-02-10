// "Good enough" attempt to get an Uno WiFi Rev2 to talk to a Tello drone
// by Thomas Dodds for ATU IEEE

#define TELLO_CMD_TAKEOFF 0x0058

#include <SPI.h>
#include <WiFiNINA.h>
#include "Packet.h"
#include "wifisecrets.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  String str = "Hello, world!";
  Serial.println(str);
  uint8_t len = str.length();
  uint8_t test[len];
  for(int k = 0; k < len; k++){
    test[k] = uint8_t(str[k]);
  }
  Serial.println(crc8(test, len));
  Serial.println(crc16(test, len));
}

void loop() {
  // put your main code here, to run repeatedly:

}
