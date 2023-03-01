#include "Arduino.h"
#include "Packet.h"

// as of now these functions are unused... uncomment to use, commented for array errors
// (aforementioned array errors may or may not be a problem, unsure)

/*
// initialize packet with string of packet content
Packet::Packet(String cmd) {
  _size = cmd.length();
  for (int k = 0; k < _size; k++) {
    _buf[k] = uint8_t(cmd[k]);
  }
}

// initialize packet with byte array of packet content
Packet::Packet(uint8_t cmd[]) {
  _size = sizeof(cmd);
  for (int k = 0; k < _size; k++) {
    _buf[k] = cmd[k];
  }
}

// initialize packet with raw payload bytes
Packet::Packet(uint16_t cmd, uint8_t pkt_type, uint8_t payload[]) {
  _buf[0] = START_OF_PACKET;
  _buf[1] = 0;
  _buf[2] = 0;
  _buf[3] = 0;
  _buf[4] = pkt_type;
  _buf[5] = le16b0(cmd);
  _buf[6] = le16b1(cmd);
  _buf[7] = 0;
  _buf[8] = 0;
  for (uint8_t k = 0; k < sizeof(payload); k++) {
    _buf[k + 8] = payload[k];
  }
  _size = 8 + sizeof(payload);
}
*/

// default for empty payload and default packet type
Packet::Packet(uint16_t cmd) {
  _buf[0] = START_OF_PACKET;
  _buf[1] = 0;
  _buf[2] = 0;
  _buf[3] = 0;
  _buf[4] = 0x68;
  _buf[5] = le16b0(cmd);
  _buf[6] = le16b1(cmd);
  _buf[7] = 0;
  _buf[8] = 0;
  _size = 9;
}

// fill in missing bits specifying length and crc checking
void Packet::fixup(uint16_t seq_num) {
  if (_buf[0] == START_OF_PACKET) {
    for (uint8_t k = 0; k < _size; k++) {
      _buf_fixup[k] = _buf[k];
    }
    _buf_fixup[0] = START_OF_PACKET;
    _buf_fixup[1] = le16b0(_size + 2) << 3;
    _buf_fixup[2] = le16b1(_size + 2);
    _buf_fixup[3] = crc8(_buf_fixup, 3);
    _buf_fixup[7] = le16b0(seq_num);
    _buf_fixup[8] = le16b1(seq_num);
    for(uint8_t k = 0; k < 8; k++){
      _buf[k] = _buf_fixup[k];
    }
    uint16_t _crc16 = crc16(_buf, _size);
    _size += 2;
    _buf[_size - 2] = le16b0(_crc16);
    _buf[_size - 1] = le16b1(_crc16);
  }
}

// default condition
void Packet::fixup() {
  Packet::fixup(0);
}

// return size of packet
uint8_t Packet::length(){
  return _size;
}

// return a byte of a buffer
// to-do: possibly optimize using pointers
uint8_t Packet::get_buffer(uint8_t position){
  return _buf[position];
}

// return lower 8 bits ofa 16-bit integer
uint8_t le16b0(uint16_t val) {
  return val & 0xff;
}
// return upper 8 bits ofa 16-bit integer
uint8_t le16b1(uint16_t val) {
  return (val >> 8) & 0xff;
}

// 8-bit cyclic redundancy check
uint8_t crc8(uint8_t buf[], uint8_t buf_len) {
  uint8_t crc = 0x77;
  for (uint8_t k = 0; k < buf_len; k++) {
    uint8_t v = buf[k];
    crc = pgm_read_byte_near(crc8table + ((crc ^ v) & 0xff));
  }
  return crc;
}

// 16-bit cyclic redundancy check
uint16_t crc16(uint8_t buf[], uint8_t buf_len) {
  uint16_t crc = 0x3692;
  for (uint8_t k = 0; k < buf_len; k++) {
    uint8_t v = buf[k];
    crc = pgm_read_word_near(crc16table + ((crc ^ uint16_t(v)) & 0xff)) ^ (crc >> 8);
  }
  return crc;
}
