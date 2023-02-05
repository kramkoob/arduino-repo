//Timer interrupt asynchronous control of multiple stepper motors with DRV8834
//by Thomas Dodds for ATU IEEE

//Driver wiring details, common to all drivers:
//Pin 1 GND to microcontroller-side GND
//Pin 3-6 A1-B2 wired per usual to motor
//Pin 7 GND and Pin 8 VMOT to motor-side power supply
//Pin 10 M0 to microcontroller-side +5V
//Pin 11 M1 to microcontroller-side GND
//Pin 14 ~SLEEP to microcontroller Digital Pin 12

//Specific wiring for indicated drivers:
//Front left Pin 15 STEP to Digital Pin 2
//Front right Pin 15 STEP to Digital Pin 3
//Rear left Pin 15 STEP to Digital Pin 4
//Rear right Pin 15 STEP to Digital Pin 5

//Front left Pin 16 DIR to Digital Pin 8
//Front right Pin 16 DIR to Digital Pin 9
//Rear left Pin 16 DIR to Digital Pin 10
//Rear right Pin 16 DIR to Digital Pin 11

//reference: https://community.robotshop.com/forum/t/arduino-101-timers-and-interrupts/13072
//reference: https://www.ti.com/lit/ds/symlink/drv8834.pdf

#define STEP_RATIO 4 // microstepping ratio set in hardware on drivers
#define TIMER_OCR2A 31 // timer resolution. lower = accurate stepping, higher = more CPU time
#define STEP_FULL 200 // full steps per revolution

#define NUM_STEPPERS 4 // number of stepper drivers, generally don't change this for our project

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

boolean stepper_state[NUM_STEPPERS];
uint8_t stepper_step_target[NUM_STEPPERS];
uint8_t stepper_step_count[NUM_STEPPERS];
boolean stepper_step[NUM_STEPPERS];
boolean syncmode = false;

// interrupt service routine for timer2 compare
ISR(TIMER2_COMPA_vect) {
  if (!syncmode) {
    for (uint8_t stepper_id = 0; stepper_id < NUM_STEPPERS; stepper_id++) {
      if (stepper_state[stepper_id] && ++stepper_step_count[stepper_id] >= stepper_step_target[stepper_id]) {
        stepper_step_count[stepper_id] = 0;
        stepper_step[stepper_id] = !stepper_step[stepper_id];
        if (stepper_step[stepper_id]) {
          STEPPER_STEP_PORT |= bit(stepper_id + STEPPER_STEP_START);
        } else {
          STEPPER_STEP_PORT &= ~bit(stepper_id + STEPPER_STEP_START);
        }
      }
    }
  } else {
    if (stepper_state[0] && ++stepper_step_count[0] >= stepper_step_target[0]) {
      stepper_step[0] = !stepper_step[0];
      stepper_step_count[0] = 0;
      for (uint8_t stepper_id = 0; stepper_id < NUM_STEPPERS; stepper_id++) {
        if (stepper_step[0]) {
          STEPPER_STEP_PORT |= bit(stepper_id + STEPPER_STEP_START);
        } else {
          STEPPER_STEP_PORT &= ~bit(stepper_id + STEPPER_STEP_START);
        }
      }

    }
  }
}

void setup() {
  // set port configuration, initial conditions
  for (uint8_t id = 0; id < NUM_STEPPERS; id++) {
    STEPPER_STEP_PORT_DIR |= bit(STEPPER_STEP_START + id);
    STEPPER_STEP_PORT &= ~bit(STEPPER_STEP_START + id);
    STEPPER_DIR_PORT_DIR |= bit(STEPPER_DIR_START + id);
    STEPPER_DIR_PORT |= bit(STEPPER_DIR_START + id) * ((id % 2) == 1);
  }
  STEPPER_SLEEP_PORT_DIR |= bit(STEPPER_SLEEP_PIN);
  STEPPER_SLEEP_PORT &= ~bit(STEPPER_SLEEP_PIN);

  // configure Timer2
  noInterrupts(); // disable all interrupts
  TCCR2A = 0; // clear control register A
  TCCR2B = 0; // clear control register B
  TCNT2 = 0; // clear timer value

  OCR2A = TIMER_OCR2A;
  TCCR2B |= bit(WGM12) | bit(CS11) | bit(CS10); // CTC mode (clear at OC match), 64 prescaler
  TIMSK2 |= bit(OCIE2A); // ocie = output compare interrupt
  interrupts(); // enable interrupts
}

void setdir(uint8_t stepper_id, boolean dir) {
  if (dir == true) {
    STEPPER_DIR_PORT |= bit(STEPPER_DIR_START + stepper_id);
  } else {
    STEPPER_DIR_PORT &= ~bit(STEPPER_DIR_START + stepper_id);
  }
}
void setRPM(uint8_t stepper_id, uint8_t rpm) {
  // given an rpm, how many ticks of the timer to step:
  // 1000000 usec / (rpm / 60 s/m * full rotation steps * microstep ratio) / interrupt value / 4 usec
  syncmode = false;
  stepper_state[stepper_id] = rpm != 0;
  stepper_step_count[stepper_id] = (rpm != 0) ? stepper_step_count[stepper_id] : 0;
  stepper_step_target[stepper_id] = uint8_t(1000000 / (float(rpm) / 60.0 * STEP_FULL * STEP_RATIO) / 4 / TIMER_OCR2A);

}
void syncRPM(uint8_t rpm) {
  syncmode = true;
  uint8_t steptarget = uint8_t(1000000 / (float(rpm) / 60.0 * STEP_FULL * STEP_RATIO) / 4 / TIMER_OCR2A);
  stepper_step_count[0] = (rpm != 0) ? stepper_step_count[0] : 0;
  for (int stepper_id = 0; stepper_id < NUM_STEPPERS; stepper_id++) {
    stepper_state[stepper_id] = rpm != 0;
    stepper_step_target[stepper_id] = steptarget;
  }
}
void syncRPM(uint8_t rpm, boolean dir) {
  // turn on sync mode so they all run the same direction and speed
  for (int stepper_id = 0; stepper_id < NUM_STEPPERS; stepper_id++) {
    setdir(stepper_id, dir);
  }
  syncRPM(rpm);
}
void loop() {


}
