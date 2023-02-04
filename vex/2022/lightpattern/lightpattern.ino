#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN 6

#define PIXEL_COUNT 16

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

const byte lookup[] = {32, 64, 96, 128, 160, 192, 224, 255};

int mode = 0; 
int t = -1;
int i = -1;
bool dir = true;

void setup() {
  strip.begin();
  strip.show();
}

void loop() {
  switch(dir){
    case true: if(++t == sizeof(lookup)){ dir = false; t--; }; break;
    case false: if(!--t){ dir = true; }; break;
  }
  if(++i == PIXEL_COUNT){ i = 0; delay(50);}
  strip.setPixelColor(i, strip.gamma32(strip.Color(lookup[t], 0, 0)));
  strip.show();
  
}
