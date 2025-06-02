#ifndef _NAVIGATECAR_H_
#define _NAVIGATECAR_H_

#include "MotorDriver.h"
#include "Ultrasonic.h"

class NavigateCar {
public: 
NavigateCar();

void decideTurn(float distance, float left_distance, float right_distance);

private:

float min_distance_front = 25;
float min_distance_sides = 15;
const int speed_ = 80;
MotorClass motor;

};

#endif