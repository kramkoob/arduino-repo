// VeX VRC 2022-2023 Spin Up
// Excellence Trophy Lighting

// by Thomas Dodds

// NeoPixels connected to pin 6

#include <Adafruit_NeoPixel.h>

#define PIXEL_COUNT 32
#define PIXEL_PIN 6
#define BRIGHTNESS 140

float pos;
int offset, attribute;
uint32_t color_set;
bool color_red;

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
}

void loop() {
  offset += 1;
  if(offset >= 360){ offset = 0; }
  pos = (sin(radians(offset)) + 0.5) * (PIXEL_COUNT / 2);
  
  for(int i = 0; i < (PIXEL_COUNT / 2) + 1; i++){
    color_red = i < pos;
    color_set = strip.gamma32(strip.Color(BRIGHTNESS * color_red, 0, BRIGHTNESS * !color_red));
    strip.setPixelColor(i, color_set);
    strip.setPixelColor(PIXEL_COUNT - i - 1, color_set);
  }
  
  strip.show();
  delay(10);
}
