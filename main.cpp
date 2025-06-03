#include <iostream>
#include "Car.h"
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
