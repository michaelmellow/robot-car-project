#include "pico/stdlib.h"
#include <stdio.h>

#include "Car.h"
#include "Ultrasonic.h"
#include "MotorClass.h"
#include "ReactToDistance.h"
#include "TestFunctions.h"

int main()
{
    stdio_init_all(); // Initialize the serial communication
    DataLogger a{};
    a.wifi_connect("ACSlab", "lab@ACS24");
    while (true) {
    
        if (a.wifi_initialized == false) {
            printf("no wifi :(");
        }
        if (a.wifi_initialized == true) {
            printf("wifi :D");
        }
    sleep_ms(5000);
    //Navigate();
    }
}
