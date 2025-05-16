#include "Car.h"
// #include "testBasicMotors.cpp"


Car::Car()
{
}

void Car::update()
{

    // full_movement_test();
}

void Car::start()
{

    if (is_active)
    {
        // if the car is already moving - stop and start moving again
        is_active = false;
        motorController.stop();
    }

    motorController.forward_move();
    is_active = true;
    // start detecting the time when the car starts moving
    start_time = time_us_32();
}

void Car::stop()
{
    if (is_active)
    {
        motorController.stop();
        is_active = false;
    }
    // calculate the time from start until the car stops
    total_time = start_time - time_us_32();
}
