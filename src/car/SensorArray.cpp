#include "SensorArray.h"

//returns new sensor status if a decision point is found, else returns null optional 
std::optional<sensor_status> SensorArray::update_readings(){
    
    sensor_reading new_sensor_reading{
        sensor_front.getDistance(), 
        sensor_forward_left.getDistance(), 
        sensor_forward_right.getDistance(),
        sensor_back_left.getDistance(), 
        sensor_back_left.getDistance()

    };
    sensor_status new_sensor_status{false,false,false,false,false};

    //if the new sensor reading is significantly greater than old sensor reading, the car reached a potential decision point
    //new_sensor_status.front_open = new_sensor_reading.front > current_sensor_reading.front + SENSOR_DIFFERENCE;
    //new_sensor_status.right_open = new_sensor_reading.right > current_sensor_reading.right + SENSOR_DIFFERENCE;
    //new_sensor_status.left_open = new_sensor_reading.left > current_sensor_reading.left + SENSOR_DIFFERENCE;

    new_sensor_status.front_open = (new_sensor_reading.front > SENSOR_DIFFERENCE) ? true : false;
    new_sensor_status.forward_right_open = (new_sensor_reading.forward_right > SENSOR_DIFFERENCE) ? true : false;
    new_sensor_status.forward_left_open = (new_sensor_reading.forward_left > SENSOR_DIFFERENCE) ? true : false;
    new_sensor_status.back_right_open = (new_sensor_reading.back_right > SENSOR_DIFFERENCE) ? true : false;
    new_sensor_status.back_left_open = (new_sensor_reading.back_left > SENSOR_DIFFERENCE) ? true : false;

    
    current_sensor_reading.update(new_sensor_reading);

    if (new_sensor_status.front_open || new_sensor_status.back_right_open || new_sensor_status.back_left_open) {
        
        return new_sensor_status;
    }

    return std::nullopt;  
}

void SensorArray::print_current_readings (){
    std::cout << "Sensor Readings:\n";
    std::cout << "--Front: " << current_sensor_reading.front  << "\n";
    std::cout << "--Forward Left:  " << current_sensor_reading.forward_left << "\n";
    std::cout << "--Forward Right: " << current_sensor_reading.forward_right << "\n";
    std::cout << "--Back Left: " << current_sensor_reading.back_left << "\n";
    std::cout << "--Back Right: " << current_sensor_reading.back_right << "\n";

}

sensor_reading SensorArray::current_readings(){

    return current_sensor_reading;
}


