// VeX IQ 2022-2023 Slapshot
// Excellence Trophy Lighting

// by Thomas Dodds

// NeoPixels connected to pin 6

// Timer0 used by NeoPixel library
// Timer1 used for long timing (sequence switching)
// Timer2 used for smoothing/animation

#include <Adafruit_NeoPixel.h>

#define PIXEL_COUNT 32
#define PIXEL_PIN 6

#define FADE_RATE 8
#define BRIGHTNESS_MAX 140
#define BRIGHTNESS_MIN 10

#define TIMER_SHORT_INTERVAL 12.0 // ms
// #define TIMER_SHORT_MAX 3
#define TIMER_LONG_INTERVAL 0.4 // s
#define TIMER_LONG_MAX 5
#define SEQUENCE_COUNT 4

const uint8_t colors[] = {
  35,   // yellow
  65,   // green
  135,  // blue
  200,  // purple
  25    // orange
};

uint8_t timer_long, sequence, pixel, fade;

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

uint8_t nextpixel(){
  if(++pixel == (PIXEL_COUNT + 1)){
    pixel = 0;
    strip.show();
  }
  return pixel;
}

void setup() {
  cli();

  // timer_short
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  OCR2A = uint8_t(constrain(15.625 * TIMER_SHORT_INTERVAL, 0, 255));
  TCCR2B |= bit(WGM21) | bit(CS20) | bit(CS22);
  TIMSK2 |= bit(OCIE2A);

  // timer_long
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = uint16_t(constrain(15625 * TIMER_LONG_INTERVAL, 0, 65535));
  TCCR1B |= bit(WGM12) | bit(CS10) | bit(CS12);
  TIMSK1 |= bit(OCIE1A);
  
  sei();

  strip.begin();
}

void loop() {
  strip.setPixelColor(nextpixel(), strip.gamma32(strip.ColorHSV(colors[sequence] << 8, 255, fade)));
}

ISR(TIMER2_COMPA_vect){
  if(timer_long == 0){
    fade += FADE_RATE * (fade < (BRIGHTNESS_MAX - FADE_RATE));
  }
  if(timer_long == TIMER_LONG_MAX){
    fade -= FADE_RATE * (fade > (BRIGHTNESS_MIN + FADE_RATE));
  }
}

ISR(TIMER1_COMPA_vect){
  if(++timer_long == (TIMER_LONG_MAX + 1)){
    timer_long = 0;
    if(++sequence == (SEQUENCE_COUNT)){
       sequence = 0;
    }
  }
}