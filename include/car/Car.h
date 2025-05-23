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

        int speed();
        MotorClass& getMotorController();
        DataLogger& getDataLogger();

    private:
        MotorClass motorController;
        DataLogger dataLogger;
        
        uint32_t start_time = 0;
        float total_time = 0;
        int speed_ = 100;
        
};

#endif