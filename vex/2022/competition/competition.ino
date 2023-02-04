// VeX 2021-2022 Tipping Point
// Excellency Trophy Control

// by Thomas Dodds

// Button connected to pin 2 - active low
// NeoPixels connected to pin 6
// Servo connected to pin 9

#include <Adafruit_NeoPixel.h>
#include <Servo.h>

#define NUM_MODES 2

#define PIXEL_COUNT 16
#define SERVO_MAX 11
#define SERVO_ZERO 11

#define PIXEL_PIN 6
#define BUTTON_PIN 2
#define SERVO_PIN 9

#define BR 120

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

byte mode = 1; 
float offset = 0;
int motorpos = 0;
unsigned long last;
unsigned long stoplast;

int i = -1;

Servo servo;

void setup() {
  strip.begin();
  strip.show();
  servo.attach(SERVO_PIN);
  servo.write(SERVO_ZERO);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), nextloop, FALLING);
}

void loop() {
  switch(mode){
    case 1: rainbow(), stop_motor(); break;
    case 2: tip_the_odds(); break;
  }
}

bool millistimer(int wait){
  bool retval = false;
  if((last + wait) <= millis()){
    last = millis();
    retval = true;
  }
  return retval;
}

void stop_motor(){
  if(servo.attached() & (millis() - stoplast) > 1000){
    servo.detach();
  }
}

void rainbow(){
  if(millistimer(15)){
    offset += 0.1;
    if(offset >= 16){ offset = 0; }
    
    uint16_t hue;
    
    for(int i = 0; i < PIXEL_COUNT; i++){
      hue = 65535 / float(PIXEL_COUNT) * fmod(offset + i,PIXEL_COUNT);
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(hue, 255, BR)));
    }
    
    strip.show();
  }
}

void tip_the_odds(){
  if(millistimer(20)){
    if(!servo.attached()){ servo.attach(SERVO_PIN); }
    if(++motorpos >= 360){ motorpos = 0; }
    float pos = sin(radians(motorpos));
    
    servo.write(int(pos * SERVO_MAX) + SERVO_ZERO);
    
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
  }
}

void nextloop(){
  if(++mode > NUM_MODES){ mode = 1; }
  stoplast = millis();
  servo.write(SERVO_ZERO);
  motorpos = 0;
  offset = 0;
  i = -1;
}
