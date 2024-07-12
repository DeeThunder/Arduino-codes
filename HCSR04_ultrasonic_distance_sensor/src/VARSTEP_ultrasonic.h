#ifndef VARSTEP_ULTRASONIC_H_INCLUDED
#define VARSTEP_ULTRASONIC_H_INCLUDED

#include <Arduino.h>

class VARSTEP_ultrasonic {
public:
	VARSTEP_ultrasonic(int trigger_pin, int echo_pin);
	double distance_cm();
	double distance_m();
private:
	int trigger_pin;
	int echo_pin;
	double distance_cm_;
};

#endif