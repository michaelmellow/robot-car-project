#ifndef DATALOGGERCLASS_H
#define DATALOGGERCLASS_H

#include <vector>
#include <cmath>
#include <string>

#include "pico/cyw43_arch.h"
#include "lwip/apps/http_client.h"
#include "lwip/netif.h"

struct Waypoint {
    float x = 0.0f;          
    float y = 0.0f;          
    uint64_t timestamp = 0;  
    bool is_turn = false;    
    float heading = 0.0f;
};



enum class MotorDirection; // forward declaration from MotorClass.h


class DataLogger {
public:
    DataLogger();
    
    float calculate_distance(int speed, uint64_t time) const;
    void log_waypoint(int speed, MotorDirection direction);
    void log_turn(float angle_degrees);
    void wifi_connect(std::string ssid, std::string password);

    const std::vector<Waypoint>& get_route() const { return route; };

    bool wifi_initialized = false;

private:
    
    std::vector<Waypoint> route;
    float current_x = 0.0f, current_y = 0.0f;
    float current_heading = 0.0f; // radians

};

#endif