#ifndef __CAR_H_
#define __CAR_H_

#include "MotorClass.h"
#include "DataLoggerClass.h"
#include "MazeSolver.h"

class Car{
    public:
        Car();
        void start();
        void stop();
        void update();

        int speed();
        MotorClass& getMotorController();
        DataLogger& getDataLogger();
        MazeSolver& getMazeSolver();

    private:
        MotorClass motorController;
        DataLogger dataLogger;
        MazeSolver mazeSolver;
        
        uint32_t start_time = 0;
        float total_time = 0;
        int speed_ = 100;
        
};

#endif