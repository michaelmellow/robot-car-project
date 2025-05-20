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

    car.getMotorController().turn_right(50);

    sleep_ms(1000);
<<<<<<< Updated upstream
    a.turn_180();
    sleep_ms(15000);
=======

    car.getMotorController().turn_right();

    sleep_ms(1000);
}

void printWaypoints(const std::vector<Waypoint>& waypoints) {
    std::cout << "Waypoints:\n";
    std::cout << "Index\tX\tY\tTimestamp\tis_turn\tHeading(rad)\tHeading(deg)\n";
>>>>>>> Stashed changes
    
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