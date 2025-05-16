#ifndef __CAR_H_
#define __CAR_H_

#include "MotorClass.h"
#include "DataLoggerClass.h"

class Car{
    public:
        Car();
        void start();
        void stop();
        void update();

    private:
        MotorClass _motorController;
        DataLogger _dataLogger;
};

#endif