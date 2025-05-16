#include "Car.h"

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

}

void Car::start(){


}

void Car::stop{


}
