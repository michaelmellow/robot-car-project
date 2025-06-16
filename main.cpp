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
    std::cout<<"Car start!\n";

    while (true){

        if (car.update_tremaux() == false) break;
        sleep_ms(300);
    }

    while (true){

        if (car.update_follow_stack() == false) break;
        sleep_ms(300);
    }

    car.test_stop();
    std::cout<<"Car stop!\n";

}


/*
int main (void){
    stdio_init_all();
    DEV_Delay_ms(5000);

    Car car;

    car.test_forward();

}
*/



