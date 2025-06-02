#ifndef __CAR_H_
#define __CAR_H_

#include "MotorClass.h"
#include "DataLoggerClass.h"
#include "Ultrasonic.h"
#include "ReactToDistance.h"
#include "MazeSolver.h"
#include "Ultrasonic.h"

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
        
        //Ultrasonic ultraSonicFront(15,16);
        //Ultrasonic ultraSonicLeft(14,17);
        //Ultrasonic ultraSonicRight(13,18);

        uint32_t start_time = 0;
        float total_time = 0;
        int speed_ = 100;
        
};

#endif