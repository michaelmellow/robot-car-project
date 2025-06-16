#include "MazeSolver.h"

MazeSolver::MazeSolver(){}
//take data from sensors ~~ is_valid_junction() or something ~~ should also probally detect dead-ends

void MazeSolver::create_junction(sensor_status sensors){
    
    //keep moving forward for a little - expirement of times #todo
    //stop in the middle of junction #todo

    current_junction.reset();

    current_junction.forward = sensors.front_open ? 0 : 2;
    current_junction.left = sensors.back_left_open ? 0 : 2;
    current_junction.right = sensors.back_right_open ? 0 : 2;
    
    if (!path_history.empty()) {
        current_junction.backward = 1;
    }

    path_history.push(current_junction);


    //car needs to continue forward for a few seconds for the wheels to line up passed the junction - experiment
}


void MazeSolver::update_junction(junction &junc, MotorDirection &dir){
    //using enum MotorDirection;

    switch (dir){
        
        case MotorDirection::D_FORWARD: is_backtracking ? junc.backward++ : junc.forward++; break;
        case MotorDirection::D_TURN_LEFT: junc.left++; break;
        case MotorDirection::D_TURN_RIGHT: junc.right++; break;
        default: break;
    }
}


MotorDirection MazeSolver::choose_direction(){
    /*
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
    */
    
    MotorDirection chosen_direction = current_junction.least_traveled_path();

    if (is_backtracking){
        
        chosen_direction = flip_direction(chosen_direction);

    }

    update_junction(current_junction, chosen_direction);
    return chosen_direction;

} 

MotorDirection MazeSolver::flip_direction(MotorDirection &dir){
    //using enum MotorDirection;

    switch(dir) {
        case MotorDirection::D_TURN_LEFT: return MotorDirection::D_TURN_RIGHT;
        case MotorDirection::D_TURN_RIGHT: return MotorDirection::D_TURN_LEFT;
        
        default: return dir;
    }
}


void MazeSolver::check_backtracking_status() {
    
    if (current_junction.has_unexplored_paths()){
        
        is_backtracking = false;
    }

    else {
        
        path_history.pop();
        current_junction = path_history.top();
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

void MazeSolver::handle_deadend(){

    is_backtracking == true;
}


MotorDirection MazeSolver::adjust (sensor_reading sensors){
    //using enum MotorDirection;
    
    // if the car is close to the right wall
    if(sensors.forward_right > 0 && sensors.forward_right < ADJUST_SENSOR_DIFFERENCE){
        
        return MotorDirection::D_CURVED_LEFT;
    }
    // if the car is close to the left wall
    else if(sensors.forward_left > 0 && sensors.forward_left < ADJUST_SENSOR_DIFFERENCE){
        
        return MotorDirection::D_CURVED_RIGHT;
    }
    // if all sensors are clear
    else {
        
        return MotorDirection::D_FORWARD;
    }
}

std::stack<junction> MazeSolver::get_path_history(){

    return path_history;
}


