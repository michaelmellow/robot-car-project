#include "MotorClass.h"

class Car{
    public:
        Car();
        void start();
        void stop();
        void update();

    private:
        MotorClass motorController;
        uint32_t start_time = 0;
        float total_time = 0;

};