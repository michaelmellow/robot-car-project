#include "TestFunctions.h"

void full_movement_test(){

    uint current_time = to_ms_since_boot(get_absolute_time());
    MotorClass a;

    while (current_time <= 2000) {
        a.forward_move(100);
        current_time = to_ms_since_boot(get_absolute_time());
    }
    a.stop();

    while (current_time <= 4000) {
        a.backward_move(100);
        current_time = to_ms_since_boot(get_absolute_time());
    }
    a.stop();

    while (current_time <= 6000) {
        a.left_lateral(100);
        current_time = to_ms_since_boot(get_absolute_time());
    }
    a.stop();

    while (current_time <= 8000) {
        a.right_lateral(100);
        current_time = to_ms_since_boot(get_absolute_time());
    }
    a.stop();

    a.turn_left();
    sleep_ms(1000);
    a.turn_right();
    sleep_ms(1000);
    a.turn_180();
    sleep_ms(15000);
    
}

void turn_test() {
    MotorClass a;
    a.turn_left();
    sleep_ms(2000);
    a.turn_right();
    sleep_ms(2000);
    a.turn_180();
    sleep_ms(5000);
}