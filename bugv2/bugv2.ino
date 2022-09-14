// there's an old blue bug robot with six legs
// this tries to make it work again

#include <Bluepad32.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// Pivot (leg forward and backward) amount
#define PIVOT_AMOUNT 0
// Leg (leg up and down) amount
#define LEG_AMOUNT 0

// Stick deadzone and 100% levels
#define STICK_DEAD 100
#define STICK_MAX 400

//#define UPDATE_TIME 50

// Forward and back motion
static const int16_t PIVOT_CENTER[] = {260, 280, 282, 272, 275, 185};
static const int16_t PIVOT_RANGE[] = {PIVOT_AMOUNT, PIVOT_AMOUNT, PIVOT_AMOUNT, PIVOT_AMOUNT, PIVOT_AMOUNT, PIVOT_AMOUNT};

// Up and down motion
static const int16_t LEG_CENTER[] = {240, 210, 310, 320, 140, 340};
static const int16_t LEG_RANGE[] = {LEG_AMOUNT, LEG_AMOUNT, LEG_AMOUNT, LEG_AMOUNT, LEG_AMOUNT, -LEG_AMOUNT};

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
GamepadPtr pad;

// Left and right movement
int32_t mL, mR;
// Current stick position
int stick;

void setup() {
  pwm.begin();

  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  
  BP32.setup(&onConnectedGamepad, &onDisconnectedGamepad);
}

void onConnectedGamepad(GamepadPtr gp) {
  if(pad == nullptr){
    pad = gp;
    BP32.enableNewBluetoothConnections(false);
  }
}

void onDisconnectedGamepad(GamepadPtr gp) {
  if(pad == gp){
    pad == nullptr;
    BP32.enableNewBluetoothConnections(true);
  }
}

void loop() {
  BP32.update();
  
  if(pad && pad->isConnected()){
    stick = (pad->axisRY());
    mR += constrain(stick, STICK_DEAD, STICK_MAX) + constrain(stick, -STICK_MAX, -STICK_DEAD);
    stick = (pad->axisY());
    mL += constrain(stick, STICK_DEAD, STICK_MAX) + constrain(stick, -STICK_MAX, -STICK_DEAD);
  }
  
  // right
  for(int leg = 0; leg <= 2; leg++){
    pwm.setPWM(leg * 2, 0, int(cos(float(mR) / 4000.0 + float(leg) * PI) * LEG_RANGE[leg]) + LEG_CENTER[leg]);
    pwm.setPWM(leg * 2 + 1, 0, int(sin(float(mR) / 4000.0 + float(leg) * PI) * PIVOT_RANGE[leg]) + PIVOT_CENTER[leg]);
  }
  // left
  for(int leg = 3; leg <= 5; leg++){
    pwm.setPWM(leg * 2, 0, int(cos(float(mL) / 4000.0 + float(leg) * PI) * LEG_RANGE[leg]) + LEG_CENTER[leg]);
    pwm.setPWM(leg * 2 + 1, 0, int(sin(float(mL) / 4000.0 + float(leg) * PI) * PIVOT_RANGE[leg]) + PIVOT_CENTER[leg]);
  }

  //delay(UPDATE_TIME);
}
