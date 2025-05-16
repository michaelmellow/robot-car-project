
#include "include/car/Car.h"
#include "tests/testBasicMotors.cpp"
#include "include/car/MotorClass.h"

void Car::Car{
    :   motorControl_()
        dataLogger()
}


void Car::update(){

    if (_motorController.is_active){

        _dataLogger.log_active_time();
    }

    if else (!_motorController.is_active){

        _dataLogger.log_inactive_time();
    }


    full_movement_test();
}

void Car::start(){


}

void Car::stop{


}
