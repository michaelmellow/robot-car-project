#include "Car.h"
// #include "testBasicMotors.cpp"

Car::Car(){}

bool Car::update_tremaux(){
    
    // #todo change how update_readings returns so that if all sensors are not open - deadend is detected
    sensorArray.update_sensors();

    MotorDirection adjustment_direction = mazeSolver.adjust(sensorArray.current_readings());
    motorController.turn_to_direction(adjustment_direction, speed_);

    //if junction is found

    //if not currently backtracking, make new junction


    if (!mazeSolver.get_is_backtracking()){

        mazeSolver.create_junction(sensorArray.current_status());
    }

    else mazeSolver.check_backtracking_status();

    DEV_Delay_ms(1000); // experiment with value;
    motorController.stop();

    MotorDirection chosen_direction = mazeSolver.choose_direction();
    
    if (chosen_direction == MotorDirection::D_STOP) return false;

    motorController.turn_to_direction(chosen_direction, speed_);
    motorController.forward_move(speed_);

        test_print_data();

    return true;
}

bool Car::update_wall_follow(){


    return false;
}

//void Car::update_following(){}

void Car::start()
{

    if (motorController.is_active)
    {
        // if the car is already moving - stop and start moving again
    
        motorController.stop();
    }

    motorController.forward_move(speed_);
    motorController.is_active = true;
    // start detecting the time when the car starts moving
    start_time = time_us_32();
}

void Car::stop()
{
    if (motorController.is_active)
    {
        motorController.stop();
    }
    // calculate the time from start until the car stops
    total_time = start_time - time_us_32();
}

int Car::speed(){

    return speed_;
}

MotorClass& Car::getMotorController() {
    return motorController;
}

DataLogger& Car::getDataLogger() {
    return dataLogger;
}


void Car::test_start(){

    motorController.forward_move(40);
}

void Car::test_stop(){

    motorController.stop();
}

void Car::test_print_data(){
    
    if (mazeSolver.get_is_backtracking()){

        std::cout <<"Is now backtracking!";
    }

    //std::cout<< "Chosen Direction\n" << "--" << chosen_direction << "\n";
    sensorArray.print_current_readings();
    mazeSolver.print_current_junction();
    std::cout <<"\n";
    
}
