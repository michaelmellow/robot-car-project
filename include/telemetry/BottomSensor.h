#ifndef __BOTTOMSENSOR_H_
#define __BOTTOMSENSOR_H_

#include "Car.h"

class BottomSensor {
public:
    /// @brief constructor
    BottomSensor();
    
    void start_check ();


private:
    bool LightColor_{};
    int LightColorCounter_{};
}


#endif