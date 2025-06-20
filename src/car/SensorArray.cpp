#include "SensorArray.h"
// trigger pin, echo pin
SensorArray::SensorArray() :
    sensor_front(15, 16),
    sensor_forward_left(13, 18),
    sensor_forward_right(14, 17), 
    sensor_back_right(12, 19),
    sensor_back_left(11, 10) { // 

        std::cout << "SensorArray Constructor Initialized!\n";
    }

void SensorArray::update_sensors(){
    
    while (true) {

        int count = 0;
        if (count > 5) {

            std::cout << "Error: Sensor Timeout";
            break;
        }
        sensor_reading new_sensor_reading(
            sensor_front.getDistance(),
            sensor_forward_left.getDistance(),
            sensor_forward_right.getDistance(),
            sensor_back_left.getDistance(),
            sensor_back_right.getDistance()
        );
        /*
        std::cout << "Sensor Refresh\n"
                  << new_sensor_reading.front << "\n"
                  << new_sensor_reading.forward_left << "\n"
                  << new_sensor_reading.forward_right << "\n"
                  << new_sensor_reading.back_right << "\n"
                  << new_sensor_reading.back_left << "\n";
        */

        // Break when all sensors have valid (non -2) readings
        if (new_sensor_reading.front != -2 &&
            new_sensor_reading.forward_left != -2 &&
            new_sensor_reading.forward_right != -2 &&
            new_sensor_reading.back_left != -2 &&
            new_sensor_reading.back_right != -2) {
            
            // Build status only when data is valid
            sensor_status new_sensor_status{
                new_sensor_reading.front > SENSOR_DIFFERENCE,
                new_sensor_reading.forward_left > SENSOR_DIFFERENCE,
                new_sensor_reading.forward_right > SENSOR_DIFFERENCE,
                new_sensor_reading.back_left > SENSOR_DIFFERENCE,
                new_sensor_reading.back_right > SENSOR_DIFFERENCE
            };

            current_sensor_reading.update(new_sensor_reading);
            current_sensor_status.update(new_sensor_status);
            break;
        }

        count++;
        sleep_ms(10);
    }
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

sensor_status SensorArray::current_status(){

    return current_sensor_status;
}

bool SensorArray::compare(sensor_status current_sensor_status, sensor_status new_sensor_status) {
        
    return (
        current_sensor_status.front_open != new_sensor_status.front_open ||
        current_sensor_status.forward_left_open != new_sensor_status.forward_left_open ||
        current_sensor_status.forward_right_open != new_sensor_status.forward_right_open ||
        current_sensor_status.back_left_open != new_sensor_status.back_left_open ||
        current_sensor_status.back_right_open != new_sensor_status.back_right_open);
}
