#include "MotorClass.h"

MotorClass::MotorClass(DataLogger* logger) : dataLogger(logger) {

    DEV_Module_Init();
    Motor_Init();
}

void MotorClass::forward_move(int speed) {
    
    is_active = true;

    motor_running(FORWARD, FORWARD, FORWARD, FORWARD, speed);
    dataLogger->log_waypoint(speed, MotorDirection::D_FORWARD);

}

void MotorClass::backward_move(int speed) {

    is_active = true;

    motor_running(BACKWARD, BACKWARD, BACKWARD, BACKWARD, speed);

    dataLogger->log_waypoint(speed, MotorDirection::D_BACKWARD);

}

void MotorClass::left_lateral(int speed) {
    
    is_active = true;

    motor_running(BACKWARD, FORWARD, FORWARD, BACKWARD, speed);

    dataLogger->log_waypoint(speed, MotorDirection::D_LEFT_LATERAL);

}

void MotorClass::right_lateral(int speed) {
    
    is_active = true;

    motor_running(FORWARD, BACKWARD, BACKWARD, FORWARD, speed);

    dataLogger->log_waypoint(speed, MotorDirection::D_RIGHT_LATERAL);

}

void MotorClass::turn(DIR dir1, DIR dir2) {
    
    int angle = 90;
    int speed = 100;
    float error_correction = 0.23;

    float turn_speed_rad = (2 * speed) / car_width;
    float rad = angle * (3.141 / 180);
    float seconds = rad/turn_speed_rad;

    seconds += error_correction;

    const uint64_t start_time = time_us_64();
    const uint64_t microseconds = (uint64_t)(seconds * 1000000);
    
    motor_running(dir1, dir2, dir1, dir2, speed);

    while (time_us_64() - start_time < microseconds) {

        DEV_Delay_ms(10);
    }
    dataLogger->log_turn(angle);
    stop();
}

void MotorClass::turn_right() {
    turn(FORWARD, BACKWARD);
}

void MotorClass::turn_left() {
    turn(BACKWARD, FORWARD);
}

void MotorClass::turn_180() {
    turn_right();
    stop();
    sleep_ms(10);
    turn_right();
}

void MotorClass::stop() {
    
    Motor_Stop(MOTORA);
    Motor_Stop(MOTORB);
    Motor_Stop(MOTORC);
    Motor_Stop(MOTORD);
    is_active = false;
    
}

void MotorClass::motor_running(DIR dir1, DIR dir2, DIR dir3, DIR dir4, int speed) {

    Motor_Run(MOTORA, dir1, speed);
    Motor_Run(MOTORB, dir2, speed);
    Motor_Run(MOTORC, dir3, speed);
    Motor_Run(MOTORD, dir4, speed);
}

