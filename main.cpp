#include <iostream>
#include "Car.h"
#include "TestFunctions.h"

int main(void){
    Car car;
<<<<<<< Updated upstream
    while (true){
        
        new_test(car);
=======
    
    car.start();

    while (true){

        if (car.update_tremaux()) break;
        
        DEV_Delay_ms(300);
    }

    car.stop();
}

/*
int main(void)
{
    Ultrasonic front(15, 16);
    Ultrasonic left(13, 18);
    Ultrasonic right(14, 17);
>>>>>>> Stashed changes

        //printWaypoints(car.getDataLogger().get_route());
    }
}
<<<<<<< Updated upstream


=======
*/
>>>>>>> Stashed changes
