#ifndef SENSOR_ARRAY_H
#define SENSOR_ARRAY_H

#include "Ultrasonic.h" // Required for Ultrasonic // Subclass

#include <optional>
#include <iostream>

struct sensor_reading{

    float front;
    float forward_left;
    float forward_right;
    float back_left;
    float back_right;

    sensor_reading(float f, float fl, float fr, float bl, float br) : 
        front(f), 
        forward_left(fl), 
        forward_right(fr),
        back_left(bl), 
        back_right(br) {}
    
    void update(sensor_reading new_sensor_reading){

        front = new_sensor_reading.front;
        forward_left = new_sensor_reading.forward_left;
        forward_right = new_sensor_reading.forward_right;
        back_left = new_sensor_reading.back_left;
        back_right = new_sensor_reading.back_right;
    }
};

struct sensor_status{
    
    bool front_open;
    bool forward_left_open;
    bool forward_right_open; 
    bool back_left_open;
    bool back_right_open; 

    void update(sensor_status new_sensor_status){
        
        front_open = new_sensor_status.front_open;
        forward_left_open = new_sensor_status.forward_left_open;
        forward_right_open = new_sensor_status.forward_right_open;
        back_left_open = new_sensor_status.back_left_open;
        back_right_open = new_sensor_status.back_right_open;

    } 
};

class SensorArray{

    public:
        
        SensorArray() : 
            sensor_front(15, 16), 
            sensor_forward_left(13, 18), 
            sensor_forward_right(14, 17),
            sensor_back_left(11,10),
            sensor_back_right(12,19) {}  
      
        void update_sensors();

        sensor_reading current_readings();
        sensor_status current_status();

        void print_current_readings ();

    private:
        const float SENSOR_DIFFERENCE = 15.0;

        sensor_reading current_sensor_reading {0.0, 0.0, 0.0, 0.0, 0.0};
        sensor_status current_sensor_status;

        Ultrasonic sensor_front;
        Ultrasonic sensor_forward_left;
        Ultrasonic sensor_forward_right;
        Ultrasonic sensor_back_left;
        Ultrasonic sensor_back_right;
};

#endif
