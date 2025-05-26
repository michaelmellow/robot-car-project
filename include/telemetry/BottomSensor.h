#ifndef __BOTTOMSENSOR_H_
#define __BOTTOMSENSOR_H_

#include "Car.h"
#include "hardware/adc.h"

class BottomSensor {
public:
    /// @brief constructor
    BottomSensor();
    
    bool start_check ();


private:
    int light_color_counter_{};
};


#endif