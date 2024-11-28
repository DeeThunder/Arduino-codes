#include <VARSTEP_ultrasonic.h>

VARSTEP_ultrasonic::VARSTEP_ultrasonic(int trigger_pin, int echo_pin) {
	this -> trigger_pin = trigger_pin;
	this -> echo_pin = echo_pin;
	pinMode(trigger_pin, OUTPUT);
	pinMode(echo_pin, INPUT);
}

double VARSTEP_ultrasonic::distance_cm() {
	digitalWrite(trigger_pin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigger_pin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigger_pin, LOW);

	noInterrupts();
	unsigned long wave_response_micro_seconds = pulseIn(echo_pin, HIGH);
	interrupts();
	distance_cm_ = (wave_response_micro_seconds * 0.0343) / 2.0;

	if(distance_cm_ == 0 || distance_cm_ > 400) {
		return - 1.0;
	} else {
		return distance_cm_;
	}
}

double VARSTEP_ultrasonic::distance_m() {
	if(distance_cm_ == 0 || distance_cm_ > 400) {
		return - 1.0;
	} else {
		return distance_cm_ / 100.0;
	}
}
