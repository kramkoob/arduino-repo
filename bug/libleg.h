#ifndef libleg_h
#define libleg_h
#include "Arduino.h" 

class leg {
public:
  leg(uint8_t index, uint16_t leg_center, uint16_t leg_range, uint16_t pivot_center, uint16_t pivot_range, bool center);
  void rate(float rate);          // set movement speed
  void set(bool leg, bool pivot); // set leg position
  void tick();                    // calculate leg position
  
private:
  uint8_t _index;                                                 // which servo
  uint8_t _servo_leg, _servo_pivot;                               // indicies for servo board
  
  float _leg, _pivot, _dest_leg_pos, _dest_pivot_pos;             // leg and pivot position, and destination
  float _rate_leg, _rate_pivot;                                   // speed of motors
  uint32_t _last_leg, _last_pivot;                                // last millis time moved
  bool _dest_leg, _dest_pivot, _center_leg, _center_pivot;        // destination (1=forward/up) / center
  
  uint16_t _leg_center, _leg_range, _pivot_center, _pivot_range;  // actuation parameters

  bool _leg_done();
  bool _pivot_done();
};
#endif
