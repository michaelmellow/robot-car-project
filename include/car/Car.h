#include "MotorClass.h"
#include "include/telemetry/DataLoggerClass.h"

class Car{
    public:
        Car();
        void start();
        void stop();
        void update();

    private:
        MotorClass _motorController;
        DataLogger _dataLogger;
};