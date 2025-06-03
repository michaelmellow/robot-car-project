#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "DEV_Config.h"

class Ultrasonic {
public:
    //constructor
    Ultrasonic(uint8_t triggerPin, uint8_t echoPin);

    /// @brief get the sensor's distance
    float getDistance();
    /// @brief Sensors test
    void TestSensor();

private:
    uint8_t triggerPin_;
    uint8_t echoPin_;
    bool motorsRunning;
};

#endif