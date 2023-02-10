#include "Arduino.h"
#include "Packet.h"

Packet::Packet(String str, byte pkt_type, byte payload[]) {

}
Packet::Packet(byte str[], byte pkt_type, byte payload[]) {
  
}

uint8_t crc8(uint8_t buf[], uint8_t buf_len){
  uint8_t crc = 0x77;
  for(uint8_t k = 0; k < buf_len; k++){
     uint8_t v = buf[k];
     crc = pgm_read_byte_near(crc8table + ((crc ^ v) & 0xff));
  }
  return crc;
}

uint16_t crc16(uint8_t buf[], uint8_t buf_len){
  uint16_t crc = 0x3692;
  for(uint8_t k = 0; k < buf_len; k++){
    uint8_t v = buf[k];
    crc = pgm_read_word_near(crc16table + ((crc ^ uint16_t(v)) & 0xff)) ^ (crc >> 8);
  }
  return crc;
}
