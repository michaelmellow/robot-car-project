// #include "test.h"   //Examples
// #include "MotorDriver.h"
#include "MotorClass.h"
#include <pico/time.h>

int main(void)
{
    uint current_time = to_ms_since_boot(get_absolute_time());
    Motor a;

    while(1){
        // while (current_time <= 2000) {
        //     a.forward_move(100);
        //     current_time = to_ms_since_boot(get_absolute_time());
        // }
        // a.stop();

        // while (current_time <= 4000) {
        //     a.backward_move(100);
        //     current_time = to_ms_since_boot(get_absolute_time());
        // }
        // a.stop();

        // while (current_time <= 6000) {
        //     a.left_lateral(100);
        //     current_time = to_ms_since_boot(get_absolute_time());
        // }
        // a.stop();

        // while (current_time <= 8000) {
        //     a.right_lateral(100);
        //     current_time = to_ms_since_boot(get_absolute_time());
        // }
        // a.stop();

        a.turn_left(100);
        sleep_ms(1000);
        a.turn_right(100);
        sleep_ms(1000);
        a.turn_180(100);
        sleep_ms(15000);
    }
    
    return 0;
}