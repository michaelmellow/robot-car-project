#ifndef __DATALOGGER_H_
#define __MOTORCLASS_H_

#include "pico/stdlib.h"
#include <vector>
<<<<<<< Updated upstream
=======
#include <cmath>
#include <string>
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
=======
=======
=======
=======

#include "pico/cyw43_arch.h"
#include "lwip/apps/http_client.h"
#include "lwip/netif.h"
#include "pico/stdio_usb.h"
>>>>>>> Stashed changes

#include "pico/cyw43_arch.h"
#include "lwip/apps/http_client.h"
#include "lwip/netif.h"
#include "pico/stdio_usb.h"
>>>>>>> Stashed changes

#include "pico/cyw43_arch.h"
#include "lwip/apps/http_client.h"
#include "lwip/netif.h"
#include "pico/stdio_usb.h"
>>>>>>> Stashed changes

#include "pico/cyw43_arch.h"
#include "lwip/apps/http_client.h"
#include "lwip/netif.h"
#include "pico/stdio_usb.h"
>>>>>>> Stashed changes

#include "pico/cyw43_arch.h"
#include "lwip/apps/http_client.h"
#include "lwip/netif.h"
#include "pico/stdio_usb.h"
>>>>>>> Stashed changes

class DataLogger{

    public:
        DataLogger();
        void log_active_time();
        void log_inactive_time();

        std::vector<uint64_t> log_stop_times(
            std::vector<uint64_t>& active_times,
            std::vector<uint64_t>& inactive_times);

<<<<<<< Updated upstream
        float calculate_distance(int speed, uint64_t time);
=======
class DataLogger {
public:
    DataLogger();
    
    float calculate_distance(int speed, uint64_t time) const;
    void log_waypoint(int speed, MotorDirection direction);
    void log_turn(float angle_degrees);
    void wifi_connect(std::string ssid, std::string password);
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes

    private:

        std::vector<uint64_t> _active_motor_times {};
        std::vector<uint64_t> _inactive_motor_times{};
        std::vector<uint64_t> _stop_times{};

        float _total_distance_traveled;

        

};

#endif