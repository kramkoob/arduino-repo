#include "Arduino.h"
#include "libleg.h"

#define LEG_SPEED 1
#define PIVOT_SPEED 1

leg::leg(uint8_t index, uint16_t leg_center, uint16_t leg_range, uint16_t pivot_center, uint16_t pivot_range, bool center){
  _index = index;
  _center_leg = center;
  _center_pivot = center;
}
void leg::tick(){
  if(!_leg_done()){
    _leg += constrain(_dest_leg_pos - _leg, -_rate_leg, _rate_leg);
  }
  if(!_pivot_done()){
    _pivot += constrain(_dest_pivot_pos - _pivot, -_rate_pivot, _rate_pivot);
  }
}
void leg::set(bool leg, bool pivot){
  if(_center_leg | _center_pivot){
    _center_leg = false;
    _center_pivot = false;
  }
  _dest_leg = leg;
  _dest_leg_pos = ((int16_t(_dest_leg) * 2 - 1) * _leg_range) + _leg_center;
  _dest_pivot = pivot;
  _dest_pivot_pos = ((int16_t(_dest_pivot) * 2 - 1) * _pivot_range) + _pivot_center;
  _last_leg = millis();
  _last_pivot = millis();
}
bool leg::_leg_done(){
  return _leg == _dest_leg_pos;
}
bool leg::_pivot_done(){
  return _pivot == _dest_pivot_pos;
}
