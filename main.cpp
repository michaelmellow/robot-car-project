#include <iostream>
#include "Car.h"
#include "TestFunctions.h"

int main(void){
    Car car;
    while (true){
        
        new_test(car);

        printWaypoints(car.getDataLogger().get_route());
    }
}


