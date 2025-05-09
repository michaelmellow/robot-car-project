//#include "test.h"   //Examples
#include "MotorDriver.h"

// #include "pico/stdlib.h"
// #include <stdio.h>

int main(void)
{
    //test();
    // stdio_init_all();
    // printf("WS2812 Smoke Test, using pin ");

    while(1){

        turn_Motor_test (90, 100);

        sleep_ms(1000);
    }
    
    return 0;
}
