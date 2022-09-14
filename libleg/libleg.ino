#include "Arduino.h"
#include "libleg.h"
leg::leg(uint8_t index, uint16_t leg_center, uint16_t leg_range, uint16_t pivot_center, uint16_t pivot_range, bool center){
  _index = index;
  _center_leg = center;
  _center_pivot = center;
}
void leg::set(bool leg, bool pivot){
  if(_center_leg | _center_pivot){
    _center_leg = false;
    _center_pivot = false;
  }
  _dest_leg = leg;
  _dest_pivot = pivot;
}
bool leg::_leg_done(){
  return _leg == ((int16_t(_dest_leg) * 2 - 1) * int16_t(!_center_leg) * _leg_range) + _leg_center;
}
bool leg::_pivot_done(){
  return _pivot == ((int16_t(_dest_pivot) * 2 - 1) * int16_t(!_center_pivot) * _pivot_range) + _pivot_center;
}
