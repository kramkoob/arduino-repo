
# arduino-repo

My Arduino sketchbook, with projects that need to be portable

### *telloduino* - transcode [TelloPy](https://github.com/hanyazou/TelloPy)

Heavy work-in-progress. Likely not all features will be implemented. For controlling a DJI Tello drone from an Arduino Uno WiFi Rev2, given serial commands or etc, unsure of specifics yet.

### *drv8834* - timer interrupt driving of servo motors

Other libraries I've seen for various stepper drivers hold execution until a stepper finishes its motion. The goal for this program/library is to drive four [Pololu DRV8834](https://www.pololu.com/product/2134) drivers independently for a 4-wheel ground robot given directional input (likely over serial from an RPi) while having time to think inbetween driving (serial, sensors, etc.).

### *vex* - trophy lighting design and control

- VRC 2021-2022 Tipping Point (complete)
- VRC 2022-2023 Spin Up (planning)
- IQ 2022-2023 Snapshot (planning)

### *bugv2*

Old project. Goal was get an old six-legged crawling robot walking. Somewhat successful, but the math is ugly and unoptimized... and the robot *did* crawl, but the old rubber feet don't have any traction anymore, so it was a sad display.
