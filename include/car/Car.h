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
        DataLogger& getDataLogger();
        MazeSolver& getMazeSolver();
        MotorClass& getMotorController();

    private:
        DataLogger dataLogger;
        MazeSolver mazeSolver;
        MotorClass motorController;

        uint32_t start_time = 0;
        float total_time = 0;
        int speed_ = 100;
        
};

#endif