#ifndef __CAR_H_
#define __CAR_H_

#include "Car.h"
#include "DataLoggerClass.h"
#include "MazeSolver.h"
#include "MotorClass.h"
#include "ReactToDistance.h"
#include "SensorArray.h"
#include "BottomSensor.h"

#include <optional>

class DataLogger; // forward declaration of needed classes.
class MazeSolver;
class MotorClass;
class SensorArray;

class Car{
    public:
        Car();
        void start();
        void stop();
        void move_to_center();
        void move_out_from_center();
        void test_start();
        void test_stop();
        void test_print_data();
        void test_forward();



        bool update_tremaux();
        bool update_follow_stack();
        void sensor_test();

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
        BottomSensor bottomSensor;

        uint32_t start_time = 0;
        float total_time = 0;
        int speed_ = 40;
        
        //const float SENSOR_DIFFERENCE = 15.0; // experiment with value

        
};

#endif