#include "pico/stdlib.h"
#include <stdio.h>

#include "Car.h"
#include "Ultrasonic.h"
#include "MotorClass.h"
#include "ReactToDistance.h"
#include "TestFunctions.h"
#include <stdio.h>

int main(void){
    
    stdio_init_all();
    DEV_Delay_ms(5000);

    Car car;

    car.test_start();
    std::cout<<"Car start!\n";

    while (true){

        if (car.update_tremaux() == false) break;

        DEV_Delay_ms(100);
    }

    car.test_stop();
    std::cout<<"Car stop!\n";

}

/*
int main(void)
{
    Ultrasonic front(15, 16);
    Ultrasonic left(13, 18);
    Ultrasonic right(14, 17);

        //printWaypoints(car.getDataLogger().get_route());
    }
}
*/

// int main()
// {
//     stdio_init_all(); // Initialize the serial communication
//     DataLogger a{};
//     a.wifi_connect("ACSlab", "lab@ACS24");
//     while (true) {
    
//         if (a.wifi_initialized == false) {
//             printf("no wifi :(");
//         }
//         if (a.wifi_initialized == true) {
//             printf("wifi :D");
//         }
//     sleep_ms(5000);
//     //Navigate();
//     }
// }
