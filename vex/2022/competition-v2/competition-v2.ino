// VeX 2021-2022 Tipping Point
// Excellency Trophy Control

// v2: removed servo support

// by Thomas Dodds

// Button connected to pin 2 - active low
// NeoPixels connected to pin 6

#include <Adafruit_NeoPixel.h>

#define NUM_MODES 2

#define PIXEL_COUNT 16

#define PIXEL_PIN 6
#define BUTTON_PIN 2

#define BR 120

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

byte mode = 1; 
float offset = 0;

int i = -1;

void setup() {
  strip.begin();
  strip.show();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), nextloop, FALLING);
}

void loop() {
  switch(mode){
    case 1: rainbow(); break;
    case 2: tip_the_odds(); break;
  }
}

void rainbow(){
  offset += 0.1;
  if(offset >= 16){ offset = 0; }
  
  uint16_t hue;
  
  for(int i = 0; i < PIXEL_COUNT; i++){
    hue = 65535 / float(PIXEL_COUNT) * fmod(offset + i,PIXEL_COUNT);
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(hue, 255, BR)));
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
  delay(20);
}

void nextloop(){
  if(++mode > NUM_MODES){ mode = 1; }
  offset = 0;
  i = -1;
}
