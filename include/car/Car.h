#ifndef __CAR_H_
#define __CAR_H_

#include "MotorClass.h"
#include "DataLoggerClass.h"
#include "MazeSolver.h"
#include "Ultrasonic.h"

#include <optional>

class Car{
    public:
        Car();
        void start();
        void stop();
        bool update_tremaux();

        int speed();
        DataLogger& getDataLogger();
        MazeSolver& getMazeSolver();
        MotorClass& getMotorController();
        SensorArray& getSensorArray();

    private:
        DataLogger dataLogger;
        MazeSolver mazeSolver;
        MotorClass motorController;
        SensorArray sensorArray;

        uint32_t start_time = 0;
        float total_time = 0;
        int speed_ = 100;
        
};

#endif