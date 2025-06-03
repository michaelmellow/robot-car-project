#include "MazeSolver.h"

MazeSolver::MazeSolver(){}
//take data from sensors ~~ is_valid_junction() or something ~~ should also probally detect dead-ends

void MazeSolver::create_junction(sensor_status sensors){
    
    //keep moving forward for a little - expirement of times #todo
    //stop in the middle of junction #todo


    if (!is_first_junction){
        
        path_history.push(current_junction);
    }

    else is_first_junction = false;

    current_junction.reset();

    current_junction.forward = sensors.front_open ? 0 : 2;
    current_junction.left = sensors.left_open ? 0 : 2;
    current_junction.right = sensors.right_open ? 0 : 2;
    
    if (!path_history.empty()) {
        current_junction.backward = 1;
    }

    //car needs to continue forward for a few seconds for the wheels to line up passed the junction - experiment
}


void MazeSolver::update_junction(junction &junc, MotorDirection &dir){
    using enum MotorDirection;

    switch (dir){
        
        case D_FORWARD: is_backtracking ? junc.backward++ : junc.forward++; break;
        case D_TURN_LEFT: junc.left++; break;
        case D_TURN_RIGHT: junc.right++; break;
        default: break;
    }
}


MotorDirection MazeSolver::choose_direction(){
    
    if (!current_junction.has_unexplored_paths()) {

        if (!path_history.empty()) {
            
            current_junction = path_history.top();
            path_history.pop();
            
            is_backtracking = true;
            return MotorDirection::D_TURN_BACKWARD;
        }

        //path is empty, maze is completed
        else {

            return MotorDirection::D_STOP;
        }
    }
    
    MotorDirection chosen_direction = current_junction.least_traveled_path();

    if (is_backtracking){
        
        chosen_direction = flip_direction(chosen_direction);

    }

    update_junction(current_junction, chosen_direction);
    return chosen_direction;

} 

MotorDirection MazeSolver::flip_direction(MotorDirection &dir){
    using enum MotorDirection;

    switch(dir) {
        case D_TURN_LEFT: return D_TURN_RIGHT;
        case D_TURN_RIGHT: return D_TURN_LEFT;
        
        default: return dir;
    }
}


void MazeSolver::check_backtracking_status() {
    if (is_backtracking && current_junction.has_unexplored_paths()) {
        
        is_backtracking = false;
    }

    if (!current_junction.has_unexplored_paths() && path_history.size() > 1) {
        
        path_history.pop(); 
    }
}

void MazeSolver::print_current_junction() {
    std::cout << "Current Junction State:\n";
    std::cout << "--Forward: " << current_junction.forward << "\n";
    std::cout << "--Left: " << current_junction.left << "\n";
    std::cout << "--Right: " << current_junction.right << "\n";
    std::cout << "--Backward: " << current_junction.backward << "\n";
}


junction MazeSolver::get_current_junction(){

    return current_junction;
}

bool MazeSolver::get_is_backtracking(){

    return is_backtracking;
}

MotorDirection MazeSolver::adjust (sensor_reading sensors){

    if(Front > WALL_DISTANCE){
            // if the car is close to the right wall
            if(F_Right < WALL_DISTANCE){
                motor.CurvedTurnLeft(40);
            }
            // if the car is close to the left wall
            else if(F_Left < WALL_DISTANCE){
                motor.CurvedTurnRight(40);
            }
            // if all sensors are clear
            else {
                motor.forward_move(40);
            }
        } 
        // if the front sensor detects a nearby wall
        else {
            // if the right side is clear
            if(Right > WALL_DISTANCE && Right > Left){
                motor.turn_right(40);
                sleep_ms(400);
                if(Front > WALL_DISTANCE){
                    motor.forward_move(40);
                }
            }
            // if the left side is clear
            else if(Left > WALL_DISTANCE && Left > Right){
                motor.turn_left(40);
                sleep_ms(400);
                if(Front > WALL_DISTANCE){
                    motor.forward_move(40);
                }
            }
        }

}


