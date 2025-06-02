#ifndef _SERVO_H_
#define _SERVO_H_

#include "pico/stdlib.h"

class Servo {
public:
	Servo(uint8_t pin);
	virtual ~Servo();

	void goDegree(float degree);

private:
	uint8_t xGP = 0;
};

#endif

//sources: https://youtu.be/kpOG2eTOzzA?si=ZsjMWE7L7eNv6e5s