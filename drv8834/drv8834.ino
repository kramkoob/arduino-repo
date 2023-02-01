//Timer interrupt asynchronous control of multiple stepper motors with DRV8834
//by Thomas Dodds for ATU IEEE

//Driver wiring details:
//Pin 1 GND to microcontroller-side GND
//Pin 3-6 A1-B2 wired per usual to motor
//Pin 7 GND and Pin 8 VMOT to motor-side power supply
//Pin 10 M0 to microcontroller-side +5V
//Pin 11 M1 to microcontroller-side GND
//Pin 14 ~SLEEP to microcontroller Digital Pin 12
//

//reference: https://community.robotshop.com/forum/t/arduino-101-timers-and-interrupts/13072
//reference: https://www.ti.com/lit/ds/symlink/drv8834.pdf

// 200 full steps at half step -> 400 half-steps per revolution
// target 120 revolutions per minute -> 800 half steps per second
// want a higher resolution than that though, say 10:1
// so when step target is 10, it will rotate 120 rpm
// when step target is 20, it will rotate 60 rpm

// to calc: 1200 / target = rpm
//            or
//          1200 / rpm = target

#define STEP_RATE 1500 // minimum time between steps
#define STEP_TIMER_RATIO 10 // speed resolution
#define STEP_FULL_COUNT 200 // full steps per revolution
#define STEP_RATIO 4 // microstepping mode (set in hardware, see wiring details)
#define STEP_MICRO_COUNT (STEP_RATIO * STEP_FULL_COUNT)

#define NUM_STEPPERS 4 // number of stepper drivers, generally don't change this

// assign D.2-5 as direction.
// that is, driver #1 DIR to Arduino Digital Pin 2, driver #2 DIR on digital 3,...
#define STEPPER_DIR_PORT PORTD
#define STEPPER_DIR_PORT_DIR DDRD
#define STEPPER_DIR_START 2

// assign B.0-3 as step.
// that is, driver 1 STEP to Digital Pin 8, driver 2 STEP on digital 9,...
#define STEPPER_STEP_PORT PORTB
#define STEPPER_STEP_PORT_DIR DDRB
#define STEPPER_STEP_START 0

// assign B.4 as sleep
// that is, all drivers' ~SLEEP inputs to Digital Pin 12
#define STEPPER_SLEEP_PORT PORTB
#define STEPPER_SLEEP_PORT_DIR DDRB
#define STEPPER_SLEEP_PIN 4

uint8_t stepper_step_count[NUM_STEPPERS];
uint8_t stepper_step_target[NUM_STEPPERS];
boolean stepper_step_state[NUM_STEPPERS];

// interrupt service routine for timer2 compare
ISR(TIMER2_COMPA_vect) {
  for (uint8_t stepper_id = 0; stepper_id < NUM_STEPPERS; stepper_id++) {
    if ((stepper_step_target[stepper_id] != 0) && ++stepper_step_count[stepper_id] >= stepper_step_target[stepper_id]) {
      stepper_step_count[stepper_id] = 0;
      stepper_step_state[stepper_id] = !stepper_step_state[stepper_id];
      if(stepper_step_state[stepper_id] == true){
        STEPPER_STEP_PORT |= 1 << stepper_id << STEPPER_STEP_START;
      }else{
        STEPPER_STEP_PORT &= ~(1 << stepper_id << STEPPER_STEP_START);
      }
    }
  }
}

void setup() {
  // configure Timer2
  noInterrupts(); // disable all interrupts
  TCCR2A = 0; // clear control register A
  TCCR2B = 0; // clear control register B
  TCNT2 = 0; // clear timer value

  //1500 microseconds / ratio = 150 per timer tick, 10 to step
  //16MHz / 64 prescaler = 250000, 1/250000 = 0.00004, or 4 microseconds
  //divide wanted time per tick (150) by resolution of 4 microseconds and floor = timer OCR2A

  OCR2A = floor(STEP_RATE / STEP_TIMER_RATIO / 4);
  TCCR2B |= bit(WGM12) | bit(CS11) | bit(CS10); // CTC mode (clear at OC), 64 prescaler
  TIMSK2 |= bit(OCIE2A); // ocie = output compare interrupt
  interrupts(); // enable interrupts

  // set port configuration, initial conditions
  for(uint8_t id = 0; id < NUM_STEPPERS; id++){    
    STEPPER_STEP_PORT_DIR |= bit(STEPPER_STEP_START + id);
    STEPPER_STEP_PORT &= ~bit(STEPPER_STEP_START + id);
    STEPPER_DIR_PORT_DIR |= bit(STEPPER_DIR_START + id);
    STEPPER_DIR_PORT |= bit(STEPPER_DIR_START + id) * ((id % 2) == 1);
  }
  STEPPER_SLEEP_PORT_DIR |= bit(STEPPER_SLEEP_PIN);
  STEPPER_SLEEP_PORT &= ~bit(STEPPER_SLEEP_PIN);
}

void setStepperSpeed(uint8_t stepper_id, byte speed, boolean direction){
  if(direction == true){
    STEPPER_DIR_PORT |= 1 << STEPPER_DIR_START << stepper_id;
  }else{
    STEPPER_DIR_PORT &= ~(1 << STEPPER_DIR_START << stepper_id);
  }
  //stepper_
}
void setStepperSpeed(uint8_t stepper_id, int16_t speed){
  uint8_t magnitude;
  if(abs(speed) > 255){
    magnitude = 255;
  }else{
    magnitude = abs(speed);
  }
  setStepperSpeed(stepper_id, magnitude, speed > 0);
}
void loop() {


}
