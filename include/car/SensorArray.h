#include "Ultrasonic.h"
#include "Car.h"
#include <optional>
#include <iostream>

struct sensor_reading{

    float front;
    float left;
    float right;

    sensor_reading(float f, float l, float r) : front(f), left(l), right(r) {}
    
    void update(sensor_reading new_sensor_reading){

        front = new_sensor_reading.front;
        left = new_sensor_reading.left;
        right = new_sensor_reading.right;
    }
};

struct sensor_status{
    
    bool front_open;
    bool left_open;
    bool right_open;    
};

class SensorArray : public Car{

    public:
        
        SensorArray() : sensor_front(15, 16), sensor_left(11, 10), sensor_right(12, 19) {}        
        std::optional<sensor_status> update_readings();
        void print_current_readings ();

    private:

        sensor_reading current_sensor_reading {0.0, 0.0, 0.0};

        Ultrasonic sensor_front;
        Ultrasonic sensor_left;
        Ultrasonic sensor_right;;

};