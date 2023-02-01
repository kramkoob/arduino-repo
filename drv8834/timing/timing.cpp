#include<iostream>
#include<cmath>

#define TIMER_INTERVAL 4
#define TIMER_RATIO 10

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
	count = std::floor(microsec_interval / TIMER_INTERVAL / TIMER_RATIO);

	std::cout << "For " << rpm << " RPM (" << revsec << " revolutions per second)," << std::endl;
	std::cout << "you need " << fullsteps << " full steps per second," << std::endl;
	std::cout << "but at microstepping 1:" << microstepping << ", you need " << microsteps << " microsteps," << std::endl;
	std::cout << "which translates to " << microsec_interval << " microsteps per second," << std::endl;
	std::cout << "and for " << TIMER_RATIO << " timer ticks at " << TIMER_INTERVAL << " usec per tick, that's " << count << std::endl;
	return 0;
}
