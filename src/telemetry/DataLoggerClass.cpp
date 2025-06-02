#include "DataLoggerClass.h"

void DataLogger::log_active_time(){

    uint64_t current_time = to_ms_since_boot(get_absolute_time());

    _active_motor_times.push_back(current_time/1000);

}

void DataLogger::log_inactive_time(){
    
    uint64_t current_time = to_ms_since_boot(get_absolute_time());

    _inactive_motor_times.push_back(current_time/1000);

}

<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
std::vector<uint64_t> log_stop_times(
    std::vector<uint64_t>& active_times,
    std::vector<uint64_t>& inactive_times)
    
{
    
    std::vector<uint64_t> stopping_times;
    size_t i = 0, j = 0;

    while (active_times[i] < inactive_times[j]){

        if ((i + 1) > active_times.size()) break;
        i++;
    }

    while (i < active_times.size() && j < inactive_times.size()){
        
        
        if (active_times[i] < inactive_times[j]){

            stopping_times.push_back(inactive_times[j]);
        }
    }

    return stopping_times;
}

float calculate_distance(int speed, uint64_t time){

    const float car_speed = .3333; // temp m/s value need to experiment

    float distance = (car_speed * (speed/100)) * (time);

    return distance; //in meters
}

<<<<<<< Updated upstream
=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
}

void wifi_connect(std::string ssid, std::string password) {

    
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
}
>>>>>>> Stashed changes
=======
}
>>>>>>> Stashed changes
=======
}
>>>>>>> Stashed changes
=======
}
>>>>>>> Stashed changes
=======
}
>>>>>>> Stashed changes
