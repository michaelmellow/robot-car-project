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

        Motor_test ();

        sleep_ms(1000);
    }
    
    return 0;
}
