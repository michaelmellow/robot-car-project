#ifndef __CAR_H_
#define __CAR_H_

#include "MotorClass.h"
#include "DataLoggerClass.h"
#include "Ultrasonic.h"
#include "ReactToDistance.h"

class Car{
    public:
        Car();
        void start();
        void stop();
        void update();

    private:
        MotorClass motorController{};
        uint32_t start_time = 0;
        float total_time = 0;
        int speed_ = 100;
        
        DataLogger _dataLogger;
};

#endif