// VeX VRC 2021-2022 Tipping Point
// Excellency Trophy

// v2: removed servo support
// v3: removed button support
// v4: fixed rainbow scaling

// by Thomas Dodds

// NeoPixels connected to pin 6

#include <Adafruit_NeoPixel.h>

#define NUM_MODES 2
const uint16_t modeLen[] = {8000, 11600};
#define PIXEL_COUNT 64
#define PIXEL_PIN 6
#define BR 70

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

byte mode = 1; 
float offset = 0;
unsigned long last;

int i = -1;

void setup() {
  strip.begin();
  strip.show();
}

void loop() {
  switch(mode){
    case 1: rainbow(); break;
    case 2: tip_the_odds(); break;
  }
  if(millistimer(modeLen[mode - 1])){ nextloop(); }
}

bool millistimer(int wait){
  bool retval = false;
  if((last + wait) <= millis()){
    last = millis();
    retval = true;
  }
  return retval;
}
void rainbow(){
  offset += 0.1 * float(PIXEL_COUNT) / 16;
  if(offset >= PIXEL_COUNT){ offset = 0; }
  
  uint16_t hue;
  int rBR = int(float((modeLen[mode - 1]) - (millis() - last)) * float(BR) / float(1000));
  
  for(int i = 0; i < PIXEL_COUNT; i++){
    hue = 65535 / float(PIXEL_COUNT) * fmod(offset + i,PIXEL_COUNT);
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(hue, 255, constrain(rBR, 0, BR))));
  }
  
  strip.show();
  delay(15);
}

void tip_the_odds(){
  if(++offset >= 360){ offset = 0; }
  float pos = sin(radians(offset));
  
  if(pos < 0){
    for(int i = 0; i < PIXEL_COUNT; i++){
      int attribute = -pos * BR * PIXEL_COUNT - BR * i;
      strip.setPixelColor(i, strip.gamma32(strip.Color(constrain(attribute, 0, BR), 0, 0)));
    }
  } else {
    for(int i = 0; i < PIXEL_COUNT; i++){
      int attribute = pos * BR * PIXEL_COUNT - BR * i;
      strip.setPixelColor(PIXEL_COUNT - i - 1, strip.gamma32(strip.Color(0, 0, constrain(attribute, 0, BR))));
    }
  }
  
  strip.show();
  delay(15);
}

void nextloop(){
  if(++mode > NUM_MODES){ mode = 1; }
  offset = 0;
  i = -1;
}
