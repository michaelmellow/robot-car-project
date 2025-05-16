#ifndef __CAR_H_
#define __CAR_H_

#include "MotorClass.h"

class Car{
    public:
        Car();
        void start();
        void stop();
        void update();

    private:
        MotorClass motorController;

};

#endif