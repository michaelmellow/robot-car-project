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

    car.getMotorController().backward_move(100);

    sleep_ms(1000);

    car.getMotorController().stop();
}

void printWaypoints(const std::vector<Waypoint>& waypoints) {
    std::cout << "Waypoints:\n";
    std::cout << "Index\tX\tY\tTimestamp\tis_turn\tHeading(rad)\tHeading(deg)\n";
    
    for (size_t i = 0; i < waypoints.size(); ++i) {
        const auto& wp = waypoints[i];
        std::cout << i << "\t"
                  << wp.x << "\t"
                  << wp.y << "\t"
                  << wp.timestamp << "\t"
                  << (wp.is_turn ? "true" : "false") << "\t"
                  << wp.heading << "\t"
                  << (wp.heading * 180.0 / M_PI) << "\n";
    }
}