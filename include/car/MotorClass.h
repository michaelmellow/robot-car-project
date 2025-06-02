#ifndef __MOTORCLASS_H_
#define __MOTORCLASS_H_

#include "MotorDriver.h"
#include "DataLoggerClass.h"

enum class MotorDirection {
    D_FORWARD,
    D_BACKWARD,
    D_LEFT_LATERAL,
    D_RIGHT_LATERAL,
    D_TURN_LEFT,
    D_TURN_RIGHT
};

class MotorClass {
public:
    //constructor
    MotorClass(DataLogger* dataLogger);

    //movement
    
    /// @brief starts moving the car forward
    /// @param speed the speed (0~100) to move at
    void forward_move(int speed);

    /// @brief starts moving the car backwards
    /// @param speed the speed (0~100) to move at
    void backward_move(int speed);

    /// @brief starts moving the car laterally to the left
    /// @param speed the speed (0~100) to move at
    void left_lateral(int speed);

    /// @brief starts moving the car laterally to the right
    /// @param speed the speed (0~100) to move at
    void right_lateral(int speed);

    /// @brief turns the car 90 degrees to the right
    void turn_right(int speed);

    /// @brief turns the car 90 degrees to the left
    void turn_left(int speed);

    /// @brief turns the car around (180 degree turn)
    void turn_180(int speed);

    /// @brief stops all car movements
    void stop();

    /// @brief turns the car a bit to the right 
    void CurvedTurnRight(int speed);

    /// @brief turns the car a bit to the left
    void CurvedTurnLeft(int speed);

    bool is_active = false;

private:
    DataLogger* dataLogger;

    /// @brief a general turn function used by the other turning function
    /// @param dir1 a direction used by motors A and C (FORWARD or BACKWARD based on the turn direction)
    /// @param dir2 a direction used by motors B and D (FORWARD or BACKWARD based on the turn direction)
    void turn(int speed, DIR dir1, DIR dir2);

    /// @brief runs all 4 motors in the given directions (FORWARD or BACKWARD)
    /// @param dir1 direction for motor A
    /// @param dir2 direction for motor B
    /// @param dir3 direction for motor C
    /// @param dir4 direction for motor D
    /// @param speed the speed (0~100) to move at
    void motor_running(DIR dir1, DIR dir2, DIR dir3, DIR dir4, int speed);
    
    float car_width = 11; //cm
};

#endif