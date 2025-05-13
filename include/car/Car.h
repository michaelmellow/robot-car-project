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