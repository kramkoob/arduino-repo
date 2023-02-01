#include<iostream>
#include<cmath>

// timer interval in microseconds
#define TIMER_INTERVAL 4
// target output compare interrupt value
// lower = more accurate stepping, higher = more CPU time for other things
#define TIMER_OCR2A 31

int rpm, microstepping;
float revsec;
int fullsteps;
int microsteps;
int microsec_interval;
int count;

int main(){
	std::cout << "Enter desired RPM: ";
	std::cin >> rpm;
	std::cout << "Enter stepping: ";
	std::cin >> microstepping;

	revsec = float(rpm) / 60.0;
	fullsteps = revsec * 200;
	microsteps = fullsteps * microstepping;
	microsec_interval = 1000000 / microsteps;
	count = std::floor(microsec_interval / TIMER_INTERVAL / TIMER_OCR2A);

	std::cout << "For " << rpm << " RPM (" << revsec << " revolutions per second)," << std::endl;
	std::cout << "you need " << fullsteps << " full steps per second," << std::endl;
	std::cout << "but at microstepping 1:" << microstepping << ", you need " << microsteps << " microsteps," << std::endl;
	std::cout << "which translates to " << microsec_interval << " microsteps per second," << std::endl;
	std::cout << "and for " << TIMER_OCR2A << " ticks at " << TIMER_INTERVAL << " usec per tick, that's " << count << " ticks." << std::endl;
	return 0;
}
