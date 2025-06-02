#ifndef __DATALOGGER_H_
#define __MOTORCLASS_H_

#include "pico/stdlib.h"
#include <vector>

#include "pico/cyw43_arch.h"
#include "lwip/apps/http_client.h"
#include "lwip/netif.h"
#include "pico/stdio_usb.h"


class DataLogger {
public:
    DataLogger();
    
    float calculate_distance(int speed, uint64_t time) const;
    void log_waypoint(int speed, MotorDirection direction);
    void log_turn(float angle_degrees);
    void wifi_connect(std::string ssid, std::string password);

    const std::vector<Waypoint>& get_route() const { return route; }

private:
    
    std::vector<Waypoint> route;
    float current_x = 0.0f, current_y = 0.0f;
    float current_heading = 0.0f; // radians
};

#endif