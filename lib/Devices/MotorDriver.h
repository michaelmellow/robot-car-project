/*****************************************************************************
* | File        :   MotorDriver.h
* | Author      :   Waveshare team
* | Function    :   Drive TB6612FNG
* | Info        :
*                TB6612FNG is a driver IC for DC motor with output transistor in
*                LD MOS structure with low ON-resistor. Two input signals, IN1
*                and IN2, can choose one of four modes such as CW, CCW, short
*                brake, and stop mode.
*----------------
* |	This version:   V1.0
* | Date        :   2018-09-04
* | Info        :   Basic version
*
******************************************************************************/
#ifndef __MOTORDRIVER_H_
#define __MOTORDRIVER_H_

#include "DEV_Config.h"
#include "PCA9685.h"

//GPIO config
// #define PWMA        0
// #define AIN1        1
// #define AIN2        2
// #define PWMB        3
// #define BIN1        4
// #define BIN2        5
// #define PWMC        6
// #define CIN1        7
// #define CIN2        8
// #define PWMD        9
// #define DIN1        10
// #define DIN2        11

#define MOTORA       0
#define MOTORB       1
#define MOTORC       2
#define MOTORD       3

typedef enum {
    FORWARD  = 0,
    BACKWARD,
} DIR;

/// @brief motor initialization
void Motor_Init(void);

/// @brief runs a certain motor (wheel)
/// @param motor: Motors (wheels) A-D
/// @param dir: forward and backward.
/// @param speed: Rotation speed (0~100)
void Motor_Run(UBYTE motor, DIR dir, UWORD speed);

/// @brief stops a selected running motor
/// @param motor motor to stop
void Motor_Stop(UBYTE motor);


void forward_Motor_test(void);
void backward_Motor_test(void);
void left_Motor_test(void);
void right_Motor_test(void);
void turn_Motor_test(int angle, int speed);
#endif
