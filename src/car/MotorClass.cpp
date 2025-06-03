#include "MotorClass.h"

/*MotorClass::MotorClass(DataLogger* logger) : dataLogger(logger) {

    DEV_Module_Init();
    Motor_Init();
}
*/
MotorClass::MotorClass(){
    DEV_Module_Init();
    Motor_Init();
}


void MotorClass::forward_move(int speed) {
    
    is_active = true;

    motor_running(FORWARD, FORWARD, FORWARD, FORWARD, speed);
    //dataLogger->log_waypoint(speed, MotorDirection::D_FORWARD);

}

void MotorClass::backward_move(int speed) {

    is_active = true;

    motor_running(BACKWARD, BACKWARD, BACKWARD, BACKWARD, speed);

    //dataLogger->log_waypoint(speed, MotorDirection::D_TURN_BACKWARD);

}

void MotorClass::left_lateral(int speed) {
    
    is_active = true;

    motor_running(BACKWARD, FORWARD, FORWARD, BACKWARD, speed);

    //dataLogger->log_waypoint(speed, MotorDirection::D_LEFT_LATERAL);

}

void MotorClass::right_lateral(int speed) {
    
    is_active = true;

    motor_running(FORWARD, BACKWARD, BACKWARD, FORWARD, speed);

    //dataLogger->log_waypoint(speed, MotorDirection::D_RIGHT_LATERAL);

}

void MotorClass::turn(int speed, DIR dir1, DIR dir2) {
    
    int angle = 90;
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
    //dataLogger->log_turn(angle);
    stop();
}

void MotorClass::stop() {
    
    Motor_Stop(MOTORA);
    Motor_Stop(MOTORB);
    Motor_Stop(MOTORC);
    Motor_Stop(MOTORD);
    is_active = false;
    
}

void MotorClass::turn_right(int speed) {
    turn(speed, FORWARD, BACKWARD);
}

void MotorClass::turn_left(int speed) {
    turn(speed, BACKWARD, FORWARD);
}

void MotorClass::turn_180(int speed) {
    turn_right(speed);
    stop();
    sleep_ms(10);
    turn_right(speed);
}


void MotorClass::motor_running(DIR dir1, DIR dir2, DIR dir3, DIR dir4, int speed) {

    Motor_Run(MOTORA, dir1, speed);
    Motor_Run(MOTORB, dir2, speed);
    Motor_Run(MOTORC, dir3, speed);
    Motor_Run(MOTORD, dir4, speed);
}

void MotorClass::turn_to_direction(MotorDirection dir, int speed){
    
    //using enum MotorDirection;

    switch (dir){

        case MotorDirection::D_FORWARD: break;
        case MotorDirection::D_TURN_BACKWARD: turn_180(speed);
        case MotorDirection::D_LEFT_LATERAL: left_lateral(speed);
        case MotorDirection::D_RIGHT_LATERAL: right_lateral(speed);
        case MotorDirection::D_TURN_LEFT: turn_right(speed);
        case MotorDirection::D_TURN_RIGHT: turn_left(speed);
        case MotorDirection::D_CURVED_LEFT: CurvedTurnLeft(speed);
        case MotorDirection::D_CURVED_RIGHT: CurvedTurnRight(speed);
        default: break;
    }
}

std::ostream& operator<<(std::ostream& os, MotorDirection direction) {
    switch (direction) {
        case MotorDirection::D_FORWARD: return os << "D_FORWARD";
        case MotorDirection::D_TURN_BACKWARD: return os << "D_TURN_BACKWARD";
        case MotorDirection::D_LEFT_LATERAL: return os << "D_LEFT_LATERAL";
        case MotorDirection::D_RIGHT_LATERAL: return os << "D_RIGHT_LATERAL";
        case MotorDirection::D_TURN_LEFT: return os << "D_TURN_LEFT";
        case MotorDirection::D_TURN_RIGHT: return os << "D_TURN_RIGHT";
        case MotorDirection::D_STOP: return os << "D_STOP";
        default: return os << "ERROR";
    }
}

void MotorClass::CurvedTurnRight(int speed)
{
    Motor_Run(MOTORA, FORWARD, speed);
    Motor_Run(MOTORB, FORWARD, speed / 2);
    Motor_Run(MOTORC, FORWARD, speed);
    Motor_Run(MOTORD, FORWARD, speed / 2);
}

void MotorClass::CurvedTurnLeft(int speed)
{
    Motor_Run(MOTORA, FORWARD, speed / 2);
    Motor_Run(MOTORB, FORWARD, speed);
    Motor_Run(MOTORC, FORWARD, speed / 2);
    Motor_Run(MOTORD, FORWARD, speed);
}
