#ifndef __MOTORCLASS_H_
#define __MOTORCLASS_H_

#include "MotorDriver.h"
#include "DataLoggerClass.h"

enum class MotorDirection {
    D_FORWARD,
    D_BACKWARD,
    D_LEFT_LATERAL,
    D_RIGHT_LATERAL
};

class MotorClass {
public:
    //constructor
    MotorClass(DataLogger* dataLogger);

    //movement
    void forward_move(int speed);
    void backward_move(int speed);
    void left_lateral(int speed);
    void right_lateral(int speed);
    //void turn(int angle, int speed);
    void turn_right(int speed);
    void turn_left(int speed);
    void turn_180(int speed);
    void stop(void);
    bool is_active = false;


private:
    DataLogger* dataLogger;

    void turn(int speed, DIR dir1, DIR dir2);
    float car_width = 10; //cm
};

#endif