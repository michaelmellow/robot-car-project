//#include "test.h"   //Examples
#include "include/car/Car.h"

// #include "pico/stdlib.h"
// #include <stdio.h>
namespace Car{
    
    Car car;
    int main(void){

        while (true){
            
            car.update();
        }
        
    }

}