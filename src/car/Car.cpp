#include "Car.h"
// #include "testBasicMotors.cpp"

bool running = false;

Car::Car()
{
}

void Car::update()
{

    // full_movement_test();
}

void Car::start()
{

    if (running)
    {
        // if the car is already moving - stop and start moving again
        running = false;
        motorController.stop();
    }

    motorController.forward_move();
    running = true;
    // start detecting the time when the car starts moving
    start_time = time_us_32();
}

void Car::stop()
{
    if (running)
    {
        motorController.stop();
        running = false;
    }
    // calculate the time from start until the car stops
    total_time = start_time - time_us_32();
}
