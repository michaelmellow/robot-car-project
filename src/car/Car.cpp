#include "Car.h"
// #include "testBasicMotors.cpp"

Car::Car(){}

bool Car::update_tremaux(){
    
    sensorArray.update_sensors();
    const sensor_reading current_readings = sensorArray.current_readings();
    const sensor_status current_status = sensorArray.current_status();

    MotorDirection adjustment_direction = mazeSolver.adjust(current_readings);

    if (adjustment_direction != MotorDirection::D_FORWARD){

        motorController.move_to_direction(adjustment_direction, speed_);
        return true;
    }
    
    //if junction is found
    if (current_status.back_left_open == true || current_status.back_right_open == true){

        //if not currently backtracking, make new junction
        if (!mazeSolver.get_is_backtracking()){
            
            mazeSolver.create_junction(current_status);
        }

        else {
            
            mazeSolver.check_backtracking_status();
            
            if (mazeSolver.get_path_history().empty() == true) return false;
        }
           
        sleep_ms(400);// Move to center of junction

        MotorDirection chosen_direction = mazeSolver.choose_direction();
        motorController.move_to_direction(chosen_direction, speed_);
        sleep_ms(400); //adjustment for turn


        test_print_data();
        std::cout << "--Chosen Direction : " << chosen_direction << "\n";
    }
    //if deadend is found
    else if (current_status.front_open == false && current_status.back_left_open == false && current_status.back_right_open == false){

        mazeSolver.handle_deadend();
        
        motorController.move_to_direction(MotorDirection::D_TURN_BACKWARD, speed_);
        sleep_ms(400);
    }

    motorController.move_to_direction(MotorDirection::D_FORWARD, speed_);

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
