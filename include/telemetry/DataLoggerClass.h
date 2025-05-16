#ifndef __DATALOGGER_H_
#define __MOTORCLASS_H_

#include "pico/stdlib.h"
#include <vector>

class DataLogger{

    public:
        DataLogger();
        void log_active_time();
        void log_inactive_time();

        std::vector<uint64_t> log_stop_times(
            std::vector<uint64_t>& active_times,
            std::vector<uint64_t>& inactive_times);

        float calculate_distance(int speed, uint64_t time);

    private:

        std::vector<uint64_t> _active_motor_times {};
        std::vector<uint64_t> _inactive_motor_times{};
        std::vector<uint64_t> _stop_times{};

        float _total_distance_traveled;

        

};

#endif