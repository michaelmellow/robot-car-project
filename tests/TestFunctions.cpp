#include "TestFunctions.h"

void full_movement_test(){

    uint current_time = to_ms_since_boot(get_absolute_time());
    Car car;

    while (current_time <= 2000) {
        car.getMotorController().forward_move(100);
        current_time = to_ms_since_boot(get_absolute_time());
    }
    car.getMotorController().stop();

    while (current_time <= 4000) {
        car.getMotorController().backward_move(100);
        current_time = to_ms_since_boot(get_absolute_time());
    }
    car.getMotorController().stop();

    while (current_time <= 6000) {
        car.getMotorController().left_lateral(100);
        current_time = to_ms_since_boot(get_absolute_time());
    }
    car.getMotorController().stop();

    while (current_time <= 8000) {
        car.getMotorController().right_lateral(100);
        current_time = to_ms_since_boot(get_absolute_time());
    }


    car.getMotorController().stop();
}

void new_test(Car car){
    sleep_ms(5000);

    car.getMotorController().forward_move(100);

    sleep_ms(1000);

    car.getMotorController().stop();

    sleep_ms(1000);

    car.getMotorController().turn_right(100);

    sleep_ms(1000);
    car.getMotorController().turn_180(100);
    sleep_ms(15000);
    
}

/*void turn_test() {
    MotorClass a;
    a.turn_left();
    sleep_ms(2000);
    a.turn_right();
    sleep_ms(2000);
    a.turn_180();
    sleep_ms(5000);
}*/


void maze_solver_test(Car car){

    
}