
# arduino-repo

My Arduino sketchbook, with projects that need to be portable

### telloduino

*rewrite the TelloPy library for Arduino*

Heavy work-in-progress. Likely not all features will be implemented.

### drv8834

*timer interrupt driving of servo motors*

Other libraries I've seen for various stepper drivers hold execution until a stepper finishes its motion. The goal for this program/library is to drive four Pololu DRV8834 drivers independently for a 4-wheel ground robot given directional input (likely over serial from an RPi) while having time to think inbetween driving (serial, sensors, etc.).

### bugv2

*get an old six-legged crawling robot walking*

Somewhat successful, but the math is ugly and unoptimized... the robot *did* crawl, but the old rubber feet don't have any traction anymore

