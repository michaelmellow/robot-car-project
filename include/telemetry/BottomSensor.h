#ifndef __BOTTOMSENSOR_H_
#define __BOTTOMSENSOR_H_

//#include "Car.h"
#include "hardware/adc.h"

class BottomSensor {
public:
    /// @brief constructor
    BottomSensor();
    
    void start_check ();
    int get_light_color_counter();

private:
    int light_color_counter_{};
};


#endif