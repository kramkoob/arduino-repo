// there's an old blue bug robot with six legs
// this tries to make it work again

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
//#include <libleg.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define PIVOT_AMOUNT 40
#define LEG_AMOUNT 150

// Forward and back motion
static const int16_t PIVOT_CENTER[] = {260, 280, 282, 272, 275, 275};
static const int16_t PIVOT_RANGE[] = {PIVOT_AMOUNT, PIVOT_AMOUNT, PIVOT_AMOUNT, PIVOT_AMOUNT, PIVOT_AMOUNT, PIVOT_AMOUNT};

// Up and down motion
static const int16_t LEG_CENTER[] = {240, 210, 310, 320, 340, 340};
static const int16_t LEG_RANGE[] = {LEG_AMOUNT, LEG_AMOUNT, LEG_AMOUNT, LEG_AMOUNT, LEG_AMOUNT, -LEG_AMOUNT};

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

void setup() {
  pwm.begin();

  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);

  // wink the no. 1 leg
  for(int i = 0; i < 7; i++){
    pwm.setPWM(0, 0, 150 + (i % 2) * 100);
    delay(150);
  }  
}

void loop() {
  // left
  /*
  for(int leg = 0; leg <= 2; leg++){
    pwm.setPWM(leg * 2, 0, int(cos(float(millis()) / 500 + float(leg * 2 * PI / float(3))) * LEG_RANGE[leg]) + LEG_CENTER[leg]);
    pwm.setPWM(leg * 2 + 1, 0, int(sin(float(millis()) / 500 + float(leg * 2 * PI / float(3))) * PIVOT_RANGE[leg]) + PIVOT_CENTER[leg]);
  }
  // right
  for(int leg = 3; leg <= 5; leg++){
    pwm.setPWM(leg * 2, 0, int(cos(float(millis()) / 500 + float(leg * 2 * PI / float(3))) * LEG_RANGE[leg]) + LEG_CENTER[leg]);
    pwm.setPWM(leg * 2 + 1, 0, int(sin(float(millis()) / 500 + float(leg * 2 * PI / float(3))) * PIVOT_RANGE[leg]) + PIVOT_CENTER[leg]);
  }
  */
}
