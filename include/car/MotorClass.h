#ifndef __MOTORCLASS_H_
#define __MOTORCLASS_H_

// #include "DEV_Config.h"
// #include "PCA9685.h"
#include "lib/Devices/MotorDriver.h"
#

class MotorClass {
public:
    //constructor
    MotorClass();

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


private:
    void turn(int speed, DIR dir1, DIR dir2);
    float car_width = 10; //cm
    bool is_active = false;
};

#endif