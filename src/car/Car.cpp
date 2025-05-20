#include "Car.h"
// #include "testBasicMotors.cpp"


Car::Car() : motorController(&dataLogger) {}

void Car::update()
{

    sleep_ms(100);
}

void Car::start()
{

    if (motorController.is_active)
    {
        // if the car is already moving - stop and start moving again
    
        motorController.is_active = false;
        motorController.stop();
    }

    motorController.forward_move(speed_);
    motorController.is_active = true;
    // start detecting the time when the car starts moving
    start_time = time_us_32();
}

void Car::stop()
{
    if (motorController.is_active)
    {
        motorController.stop();
        motorController.is_active = false;
    }
    // calculate the time from start until the car stops
    total_time = start_time - time_us_32();
}

int Car::speed(){

    return speed_;
}

MotorClass& Car::getMotorController() {
    return motorController;
}

DataLogger& Car::getDataLogger() {
    return dataLogger;
}

