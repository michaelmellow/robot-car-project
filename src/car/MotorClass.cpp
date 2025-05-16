#include "MotorClass.h"

MotorClass::MotorClass() {

    DEV_Module_Init();
    Motor_Init();
}

void MotorClass::forward_move(int speed) {
    
    is_active = true;

    Motor_Run(MOTORA, FORWARD, speed);
    Motor_Run(MOTORB, FORWARD, speed);
    Motor_Run(MOTORC, FORWARD, speed);
    Motor_Run(MOTORD, FORWARD, speed);

}

void MotorClass::backward_move(int speed) {

    is_active = true;

    Motor_Run(MOTORA, BACKWARD, speed);
    Motor_Run(MOTORB, BACKWARD, speed);
    Motor_Run(MOTORC, BACKWARD, speed);
    Motor_Run(MOTORD, BACKWARD, speed);
}

void MotorClass::left_lateral(int speed) {
    
    is_active = true;

    Motor_Run(MOTORA, BACKWARD, speed);
    Motor_Run(MOTORB, FORWARD, speed);
    Motor_Run(MOTORC, FORWARD, speed);
    Motor_Run(MOTORD, BACKWARD, speed);
}

void MotorClass::right_lateral(int speed) {
    
    is_active = true;

    Motor_Run(MOTORA, FORWARD, speed);
    Motor_Run(MOTORB, BACKWARD, speed);
    Motor_Run(MOTORC, BACKWARD, speed);
    Motor_Run(MOTORD, FORWARD, speed);
}

void MotorClass::turn(int speed, DIR dir1, DIR dir2) {
    
    int angle = 90;
    float turn_speed_rad = (2 * speed) / car_width; //car_width = 10 (cm)
    float rad = angle * (3.14 / 180);
    float seconds = rad/turn_speed_rad;

    seconds *= 5.8;

    const uint64_t start_time = time_us_64();
    const uint64_t microseconds = (uint64_t)(seconds * 1000000);
    
    // Motor_Run(MOTORA, FORWARD, speed);
    // Motor_Run(MOTORB, BACKWARD, speed);
    // Motor_Run(MOTORC, FORWARD, speed);
    // Motor_Run(MOTORD, BACKWARD, speed);
    Motor_Run(MOTORA, dir1, speed);
    Motor_Run(MOTORB, dir2, speed);
    Motor_Run(MOTORC, dir1, speed);
    Motor_Run(MOTORD, dir2, speed);

    while (time_us_64() - start_time < microseconds) {

        DEV_Delay_ms(10);
    }

    stop();
}

void MotorClass::turn_right(int speed) {
    turn(speed, FORWARD, BACKWARD);
}

void MotorClass::turn_left(int speed) {
    turn(speed, BACKWARD, FORWARD);
}

void MotorClass::turn_180(int speed) {
    turn_right(speed);
    turn_right(speed);
}

void MotorClass::stop(void) {
    
    Motor_Stop(MOTORA);
    Motor_Stop(MOTORB);
    Motor_Stop(MOTORC);
    Motor_Stop(MOTORD);
    is_active = false;
    
}

