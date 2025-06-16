#include "Car.h"
// #include "testBasicMotors.cpp"

Car::Car(){}

bool Car::update_tremaux(){
    
    /*
    bottomSensor.start_check();

    if (bottomSensor.get_light_color_counter == 2){

        mazeSolver.handle_deadend();
        
        motorController.move_to_direction(MotorDirection::D_TURN_BACKWARD, speed_);

        return false;
    }
    */

    sensorArray.update_sensors();
    sensor_reading current_readings = sensorArray.current_readings();
    sensor_status current_status = sensorArray.current_status();

    std::cout <<"-------\n";
    
    test_print_data();

    motorController.move_to_direction(MotorDirection::D_FORWARD, speed_);

    MotorDirection adjustment_direction = mazeSolver.adjust(current_readings);
    
    if (adjustment_direction != MotorDirection::D_FORWARD){
        
        motorController.move_to_direction(adjustment_direction, speed_);
        
        std::cout <<"Adjustment detected!\n";
        std::cout << adjustment_direction << "\n";

        sleep_ms(50);
        return true;
    }

    //if junction is found
    if (current_status.back_left_open == true || current_status.back_right_open == true){
        
        std::cout << "Junction detected!\n";

        //if not currently backtracking, make new junction
        if (mazeSolver.get_is_backtracking()){
        
            mazeSolver.check_backtracking_status();
            //if the car is backtracking and the path history is empty, the maze is complete
            if (mazeSolver.get_path_history().empty() == true) return false;
        }

        else {
            
            mazeSolver.create_junction(current_status);
        }
           
        sleep_ms(800);// Move to center of junction
        motorController.stop();

        sensorArray.update_sensors();
        sensor_reading current_readings = sensorArray.current_readings();
        sensor_status current_status = sensorArray.current_status();
        sleep_ms(1000);

        MotorDirection chosen_direction = mazeSolver.choose_direction();

        motorController.move_to_direction(chosen_direction, speed_);
        //sleep_ms(1150); //adjustment for turn
        
        motorController.stop();
        sleep_ms(1000);
        motorController.move_to_direction(MotorDirection::D_FORWARD, speed_);
        sleep_ms(500);

    }
    //if deadend is found
    else if (current_status.front_open == false && current_status.back_left_open == false && current_status.back_right_open == false){

        std::cout <<"Deadend detected!\n";

        mazeSolver.handle_deadend();
        
        motorController.move_to_direction(MotorDirection::D_TURN_BACKWARD, speed_);
        
        motorController.stop();
        sleep_ms(1000);
        motorController.move_to_direction(MotorDirection::D_FORWARD, speed_);
        sleep_ms(500);

    }
    std::cout <<"-------\n";

    return true;
}

bool Car::update_follow_stack(){
    
    if (bottomSensor.get_light_color_counter() == 3){

        return false;
    }
    
    if (mazeSolver.get_path_history().empty() == true) return true;
    
    sensorArray.update_sensors();
    sensor_reading current_readings = sensorArray.current_readings();
    sensor_status current_status = sensorArray.current_status();

    std::cout <<"-------\n";
    
    test_print_data();

    motorController.move_to_direction(MotorDirection::D_FORWARD, speed_);

    MotorDirection adjustment_direction = mazeSolver.adjust(current_readings);
    
    if (adjustment_direction != MotorDirection::D_FORWARD){
        
        motorController.move_to_direction(adjustment_direction, speed_);
        
        std::cout <<"Adjustment detected!\n";
        std::cout << adjustment_direction << "\n";

        sleep_ms(50);
        return true;
    }

    //if junction is found
    if (current_status.back_left_open == true || current_status.back_right_open == true){
        
        std::cout << "Junction detected!\n";
    
        sleep_ms(800);// Move to center of junction
        motorController.stop();

        sensorArray.update_sensors();
        sensor_reading current_readings = sensorArray.current_readings();
        sensor_status current_status = sensorArray.current_status();
        sleep_ms(1000);

        MotorDirection chosen_direction = mazeSolver.choose_direction();

        motorController.move_to_direction(chosen_direction, speed_);
        //sleep_ms(1150); //adjustment for turn
        motorController.stop();

        motorController.move_to_direction(MotorDirection::D_FORWARD, speed_);
        sleep_ms(1000);

        mazeSolver.get_path_history().pop();

    }
    std::cout <<"-------\n";

    return true;

}

void Car::sensor_test(){

    sensorArray.update_sensors();
    //const sensor_reading current_readings = sensorArray.current_readings();
    //const sensor_status current_status = sensorArray.current_status();

    test_print_data();
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

        std::cout <<"Is now backtracking!\n";
    }

    //std::cout<< "Chosen Direction\n" << "--" << chosen_direction << "\n";
    sensorArray.print_current_readings();
    mazeSolver.print_current_junction();
    
    std::cout <<"\n";
    
}

void Car::test_forward(){

    motorController.move_to_direction(MotorDirection::D_FORWARD, speed_);
    //motorController.forward_move(speed_);
}


