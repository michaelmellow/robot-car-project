#include "pico/stdlib.h"
#include "DataLoggerClass.h"
#include "MotorClass.h" 
#include <iostream>

DataLogger::DataLogger() {
    uint64_t start_time = to_ms_since_boot(get_absolute_time());
    route.push_back({0.0f, 0.0f, start_time, false, 0.0f});
}

float DataLogger::calculate_distance(int speed, uint64_t time) const{

    const float car_speed = .3333; // m/s value of car, not related to motor speed. Need to experiment for value

    float speed_factor = static_cast<float>(speed) / 100.0f;
    float time_seconds = static_cast<float>(time) / 1000.0f;

    float distance = car_speed * speed_factor * time_seconds;

    return distance; //in meters

}

void DataLogger::log_waypoint(int speed, MotorDirection direction){

    uint64_t current_time = to_ms_since_boot(get_absolute_time());
    uint64_t time_difference = current_time - route.back().timestamp;

    float distance = calculate_distance(speed,time_difference);

   //std::cout << "TEST!!!! ------ " << distance;

   switch (direction) {
        case MotorDirection::D_FORWARD:
            current_x += distance * std::cos(current_heading);
            current_y += distance * std::sin(current_heading);
            break;

        case MotorDirection::D_BACKWARD:
            current_x -= distance * std::cos(current_heading);
            current_y -= distance * std::sin(current_heading);
            break;

        case MotorDirection::D_LEFT_LATERAL:
            current_x += distance * std::cos(current_heading - M_PI_2);
            current_y += distance * std::sin(current_heading - M_PI_2);
            break;

        case MotorDirection::D_RIGHT_LATERAL:
            current_x += distance * std::cos(current_heading + M_PI_2);
            current_y += distance * std::sin(current_heading + M_PI_2);
            break;
    }

    route.push_back({current_x,current_y,current_time,false,current_heading});

}

void DataLogger::log_turn(float angle_degrees){
    
    uint64_t current_time = to_ms_since_boot(get_absolute_time());

    current_heading += angle_degrees * (M_PI / 180.0f);
    while (current_heading > M_PI) current_heading -= 2 * M_PI;
    while (current_heading <= -M_PI) current_heading += 2 * M_PI;

    route.push_back({current_x,current_y,current_time,true,current_heading});

}

void wifi_connect(std::string ssid, std::string password) {

    
}