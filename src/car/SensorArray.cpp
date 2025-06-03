#include "SensorArray.h"
#include <optional>

//returns new sensor status if a decision point is found, else returns null optional 
std::optional<sensor_status> SensorArray::update_readings(){
    
    sensor_reading new_sensor_reading{sensor_front.getDistance(), sensor_left.getDistance(),sensor_right.getDistance()};
    sensor_status new_sensor_status{false,false,false};

    //if the new sensor reading is significantly greater than old sensor reading, the car reached a potential decision point
    //new_sensor_status.front_open = new_sensor_reading.front > current_sensor_reading.front + SENSOR_DIFFERENCE;
    //new_sensor_status.right_open = new_sensor_reading.right > current_sensor_reading.right + SENSOR_DIFFERENCE;
    //new_sensor_status.left_open = new_sensor_reading.left > current_sensor_reading.left + SENSOR_DIFFERENCE;

    new_sensor_status.front_open = (new_sensor_reading.front > SENSOR_DIFFERENCE)true : false;
    new_sensor_status.right_open = (new_sensor_reading.right > SENSOR_DIFFERENCE) ? true : false;
    new_sensor_status.left_open = (new_sensor_reading.left > SENSOR_DIFFERENCE) ? true : false;


    
    current_sensor_reading.update(new_sensor_reading);

    if (new_sensor_status.front_open || new_sensor_status.right_open || new_sensor_status.left_open) {
        
        return new_sensor_status;
    }

    return std::nullopt;  
}

void SensorArray::print_current_readings (){
    std::cout << "Sensor Readings:\n";
    std::cout << "--Front: " << current_sensor_reading.front  << "\n";
    std::cout << "--Left:  " << current_sensor_reading.left << "\n";
    std::cout << "--Right: " << current_sensor_reading.right << "\n";
}


