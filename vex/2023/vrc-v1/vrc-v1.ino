// VeX VRC 2022-2023 Spin Up
// Excellence Trophy Lighting

// by Thomas Dodds

// NeoPixels connected to pin 6

#include <Adafruit_NeoPixel.h>

#define PIXEL_COUNT 16
#define PIXEL_PIN 6
#define BRIGHTNESS 140

float pos;
int offset, attribute;
uint32_t color_set;
bool color_red, dir, coldir;

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
}

void loop() {
  if(dir){
    offset++;
  }else{
    offset--;
  }
  if((offset >= 180 && dir) || (offset <= 0 && !dir)){
    coldir = !coldir;
    if( coldir ){
      dir = !dir;
    }
    if(dir){
      offset = 0;
    }else{
      offset = 180;
    }
  }
  pos = (cos(radians(offset)) + 0.9) * PIXEL_COUNT / 1.8;
  
  for(int i = 0; i < PIXEL_COUNT; i++){
    color_red = (i < pos) ^ coldir ^ dir;
    color_set = strip.gamma32(strip.Color(BRIGHTNESS * color_red, 0, BRIGHTNESS * !color_red));
    strip.setPixelColor(i, color_set);
  }
  
  strip.show();
  delay(7);
}
