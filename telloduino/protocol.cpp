// Packet class and related functions

#include "Arduino.h"
#include "protocol.h"
#include "utils.h"
#include "crc.h"

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
//  buffer = &_buf;
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
uint8_t Packet::size(){
  return _size;
}

// return a byte of a buffer
// to-do: possibly optimize using pointers
//uint8_t Packet::get_buffer(uint8_t position){
//  return _buf[position];
//}

// add byte to end of packet (payload)
void Packet::add_byte(uint8_t data){
  _buf[++_size - 1] = data;
}

// print buffer to interface (ex.: Serial)
void Packet::print_buffer(Stream &interface){
  for(uint8_t k = 0; k < _size; k++){
    if(_buf[k] < 0x10){
      interface.print(0);
    }
    interface.print(_buf[k], HEX);
    interface.print((k + 1 < _size) ? ":" : "\n");
  }
}
