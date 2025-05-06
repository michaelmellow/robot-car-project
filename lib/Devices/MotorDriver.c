/*****************************************************************************
* | File        :   MotorDriver.c
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
#include "MotorDriver.h"
#include "Debug.h"
#include <math.h>

int MotorPin[4][3]={ {0,1,2},{3,4,5},{6,7,8},{9,10,11} } ;//MA,MB,MC,MD
int MotorDir[2][2]={ {0,1},{1,0} } ;//forward, backward

const float car_circumference = 81.68; //cm
const float car_width = 10; //cm  





/**
 * Motor rotation.
 *
 * Example:
 * Motor_Init();
 */
void Motor_Init(void)
{
    PCA9685_Init(0x40);
    PCA9685_SetPWMFreq(100);
}

/**
 * Motor rotation.
 *
 * @param motor: Motor A and Motor B.
 * @param dir: forward and backward.
 * @param speed: Rotation speed.  //(0~100)
 *
 * Example:
 * @code
 * Motor_Run(MOTORA, FORWARD, 50);
 * Motor_Run(MOTORB, BACKWARD, 100);
 */
void Motor_Run(UBYTE motor, DIR dir, UWORD speed)
{
    if(speed > 100)
        speed = 100;

    PCA9685_SetPwmDutyCycle(MotorPin[motor][0], speed);
    PCA9685_SetLevel(MotorPin[motor][1], MotorDir[dir][0]);
    PCA9685_SetLevel(MotorPin[motor][2], MotorDir[dir][1]);
}

/**
 * Motor stop rotation.
 *
 * @param motor: Motor A and Motor B.
 *
 * Example:
 * @code
 * Motor_Stop(MOTORA);
 */
void Motor_Stop(UBYTE motor)
{
    PCA9685_SetPwmDutyCycle(MotorPin[motor][0], 0);
}

/**
 * Motor stop rotation.
 *
 * @param motor: Motor A and Motor B.
 *
 * Example:
 * @code
 * Motor_Stop(MOTORA);
 */
void forward_Motor_test(void)
{
    //1.System Initialization
    if(DEV_Module_Init()!=0){
        return;
    }
    DEV_Delay_ms(3000);
    printf("MOTOR TEST");
    // int x = 0;
    // while(1){
        // x++;
        // printf("MOTOR TEST\r\n");
        // DEV_Delay_ms(1000);
        
         // 2.Motor Initialization
        // Motor_Init();
        // printf("Motor_Init\r\n");
        
        // printf("Motor_Run time = %d\r\n", x );
        // Motor_Run(MOTORA, FORWARD, 100);
        
    // }
    
    //2.Motor Initialization
    Motor_Init();
    printf("Motor_Init\r\n");
    
    printf("Motor_Run\r\n");
    Motor_Run(MOTORA, FORWARD, 100);
    Motor_Run(MOTORB, FORWARD, 100);
    Motor_Run(MOTORC, FORWARD, 100);
    Motor_Run(MOTORD, FORWARD, 100);
    // Motor_Run(MOTORB, BACKWARD, 100);
}

void backward_Motor_test(void){

    //1.System Initialization
    if(DEV_Module_Init()!=0){
        return;
    }
    DEV_Delay_ms(3000);

    //2.Motor Initialization
    Motor_Init();

    Motor_Run(MOTORA, BACKWARD, 100);
    Motor_Run(MOTORB, BACKWARD, 100);
    Motor_Run(MOTORC, BACKWARD, 100);
    Motor_Run(MOTORD, BACKWARD, 100);
}

void right_Motor_test(void){

    //1.System Initialization
    if(DEV_Module_Init()!=0){
        return;
    }
    DEV_Delay_ms(3000);

    //2.Motor Initialization
    Motor_Init();

    Motor_Run(MOTORA, FORWARD, 100);
    Motor_Run(MOTORB, BACKWARD, 100);
    Motor_Run(MOTORC, BACKWARD, 100);
    Motor_Run(MOTORD, FORWARD, 100);
}

void left_Motor_test(void){

    //1.System Initialization
    if(DEV_Module_Init()!=0){
        return;
    }
    DEV_Delay_ms(3000);

    //2.Motor Initialization
    Motor_Init();

    Motor_Run(MOTORA, BACKWARD, 100);
    Motor_Run(MOTORB, FORWARD, 100);
    Motor_Run(MOTORC, FORWARD, 100);
    Motor_Run(MOTORD, BACKWARD, 100);
}

void turn_Motor_test(int angle, int speed){
    
    //1.System Initialization
    if(DEV_Module_Init()!=0){
        return;
    }
    DEV_Delay_ms(3000);

    //2.Motor Initialization
    Motor_Init();

    float turn_speed_rad = (2 * speed) / car_width;
    float rad = angle * (3.14 / 180);
    float seconds = rad/turn_speed_rad;

    seconds *= 5.8;

    const uint64_t start_time = time_us_64();
    const uint64_t microseconds = (uint64_t)(seconds * 1000000);
    
    Motor_Run(MOTORA, FORWARD, speed);
    Motor_Run(MOTORB, BACKWARD, speed);
    Motor_Run(MOTORC, FORWARD, speed);
    Motor_Run(MOTORD, BACKWARD, speed);


    while (time_us_64() - start_time < microseconds) {
        
        DEV_Delay_ms(10);
    }

    Motor_Stop(MOTORA);
    Motor_Stop(MOTORB);
    Motor_Stop(MOTORC);
    Motor_Stop(MOTORD);

}












