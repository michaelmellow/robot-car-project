#include "Car.h"
#include "TestFunctions.h"
#include "BottomSensor.h"



int main(void){
    BottomSensor s{};

    while (true){
       s.start_check();
       sleep_ms(200); 
        
    }
    
}
