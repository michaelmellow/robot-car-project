#include "pico/stdlib.h"
#include <stdio.h>

#include "Car.h"
#include "Ultrasonic.h"
#include "MotorClass.h"
#include "ReactToDistance.h"
#include "TestFunctions.h"

/*
int main(void){

    stdio_init_all();

    //DEV_Delay_ms(5000);

    sleep_ms(5000);

    Car car;

    while (true){ 

        car.sensor_test();

        sleep_ms(300);
    }
}
*/


/*
int main(void){
    stdio_init_all();

    while (true){
        
        std::cout <<"HellO!\n";
        sleep_ms(100);
    }
}
*/


/*
int main(void){
    stdio_init_all();
    DEV_Delay_ms(5000);

    Ultrasonic test{14,15};
    float distance;
    while(true){

        distance = test.getDistance();

        std::cout <<distance<< "\n";
    }
}
*/

int main(void){
    
    stdio_init_all();
    DEV_Delay_ms(5000);

    Car car;

    //car.test_start();
    std::cout<<"Car start! --------------------------------\n";

    while (true){

        if (car.update_tremaux() == false) break;
        sleep_ms(300);
    }
    /*
    while (true){

        if (car.update_follow_stack() == false) break;
        sleep_ms(300);
    }
    */
    std::cout<<"Car stop!\n";
    car.test_stop();

}



/*
int main (void){
    stdio_init_all();
    DEV_Delay_ms(5000);

    Car car;

    car.test_forward();

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
