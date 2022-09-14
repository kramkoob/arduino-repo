#ifndef libleg_h
#define libleg_h
#include "Arduino.h" 
class leg {
public:
  leg(uint8_t index, uint16_t leg_center, uint16_t leg_range, uint16_t pivot_center, uint16_t pivot_range, bool center);
  void set(bool leg, bool pivot);
  void tick();
  
private:
  uint8_t _index;                                                 // which servo
  uint16_t _leg, _pivot;                                          // leg and pivot position
  uint32_t _last_leg, _last_pivot;                                // last time moved
  bool _dest_leg, _dest_pivot, _center_leg, _center_pivot;        // destination (1=forward/up) / center
  
  uint16_t _leg_center, _leg_range, _pivot_center, _pivot_range;  // actuation parameters

  uint16_t _move(uint16_t move_center, uint16_t move_range, uint32_t last, bool dest, bool center);
  bool _leg_done();
  bool _pivot_done();
};
#endif
