#include "Car.h"
// #include "testBasicMotors.cpp"

#define OUT(...) std::cout << #__VA_ARGS__ << " = " << __VA_ARGS__ << '\n'

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
    
    //test_print_data();

    motorController.move_to_direction(MotorDirection::D_FORWARD, speed_);

    MotorDirection adjustment_direction = mazeSolver.adjust(current_readings);
    
    if (adjustment_direction != MotorDirection::D_FORWARD){
        
        motorController.move_to_direction(adjustment_direction, speed_);
        
        std::cout <<"Adjustment detected!\n";
        std::cout << adjustment_direction << "\n";

        sleep_ms(50);

        if (current_status.front_open != false) return true;

    }

    //if junction is found
    if (current_status.back_left_open == true || current_status.back_right_open == true){
        
        std::cout << "Junction detected!\n";
        
        // Move to center of junction
        move_to_center();

        motorController.stop();

        sensorArray.update_sensors(); //Update sensors again
        current_readings = sensorArray.current_readings();
        current_status = sensorArray.current_status();

        //OUT(mazeSolver.get_is_backtracking());
        //if not currently backtracking, make new junction
        if (mazeSolver.get_is_backtracking() == true){
            
            mazeSolver.check_backtracking_status();
            //if the car is backtracking and the path history is empty, the maze is complete
            if (mazeSolver.is_path_history_empty()) {
                
                std::cout << "Stack is empty!\n";
            }
        }

        else {
            
            mazeSolver.create_junction(current_status);
        }
        test_print_data();
        std::cout << "Current Heading: " << mazeSolver.get_current_heading() << "\n";

        MotorDirection chosen_direction = mazeSolver.choose_direction();

        Direction new_heading = mazeSolver.get_new_heading(mazeSolver.get_current_heading(), chosen_direction);
        mazeSolver.set_heading(new_heading);

        std::cout << "New Heading: " << new_heading << "\n";

        motorController.move_to_direction(chosen_direction, speed_);

        std::cout <<"Chosen Direction: " << chosen_direction << "\n";
        
        motorController.stop();

        motorController.move_to_direction(MotorDirection::D_FORWARD, speed_);
        
        test_print_data();
        //std::cout <<"Junction Number: " << mazeSolver.get_path_history().size() << "\n";

        if (mazeSolver.get_is_backtracking() == true){

            mazeSolver.pop_stack(); 
        }

        // move out of junction
        move_out_from_center();

    }

    //if deadend is found
    else if (current_status.front_open == false && current_readings.front < 20 && current_status.back_left_open == false && current_status.back_right_open == false){

        std::cout <<"Deadend detected!\n";
        motorController.stop();
        sleep_ms(1000);
        mazeSolver.handle_deadend();
        
        motorController.move_to_direction(MotorDirection::D_TURN_BACKWARD, speed_);
        
        motorController.stop();

        Direction new_heading = mazeSolver.get_new_heading(mazeSolver.get_current_heading(), MotorDirection::D_TURN_BACKWARD);
        mazeSolver.set_heading(new_heading);

        
        //MotorDirection retrace_rel = get_relative_direction(mazeSolver.get_current_junction(), new_heading);
        //update_junction(mazeSolver.get_current_junction(), retrace_rel);

        std::cout << "Current Heading: " << new_heading << "\n";

        sleep_ms(1000);
        motorController.move_to_direction(MotorDirection::D_FORWARD, speed_);

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

void Car::move_to_center(){

    if (sensorArray.current_readings().front > 50){

        sleep_ms(800);
    }

    else {

        int count = 0;

        while (sensorArray.current_readings().front > 10.0 && count < 16){

            sleep_ms(50);
            sensorArray.update_sensors();
            count++;
        }
    }
}

void Car::move_out_from_center(){
    sensorArray.update_sensors();
    
    //test_print_data();

    while (sensorArray.current_status().back_left_open == true || sensorArray.current_status().back_right_open == true){
        
        sleep_ms(50);
        sensorArray.update_sensors();

    }

    sleep_ms(100);
}


bool Car::update_follow_stack(){
    
    if (bottomSensor.get_light_color_counter() == 3){

        return false;
    }
    
    // continue forward because there are no more junctions to detect
    if (mazeSolver.is_path_history_empty()) return true;
    
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
        
        sleep_ms(600);
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
        sleep_ms(600); // move out of junction

    }
    std::cout <<"-------\n";

    return true;

}

