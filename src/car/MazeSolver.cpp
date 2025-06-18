#include "MazeSolver.h"

MazeSolver::MazeSolver(){

    path_history.push({1, 2, 2, 2, NORTH});
    current_junction = path_history.top();
}
//take data from sensors ~~ is_valid_junction() or something ~~ should also probally detect dead-ends

void MazeSolver::create_junction(sensor_status sensors){
    
    //keep moving forward for a little - expirement of times #todo
    //stop in the middle of junction #todo
    current_junction.reset();

    current_junction.entered_from_heading = current_heading;
    current_junction.forward = sensors.front_open ? 0 : 2;
    current_junction.left = sensors.back_left_open ? 0 : 2;
    current_junction.right = sensors.back_right_open ? 0 : 2;
    current_junction.backward = 1;

    /*
    if (!path_history.empty()) {
        current_junction.backward = 1;
    }
    */

    path_history.push(current_junction);

    //car needs to continue forward for a few seconds for the wheels to line up passed the junction - experiment
}


void MazeSolver::update_junction(junction &junc, MotorDirection &dir){
    //using enum MotorDirection;

    switch (dir){
        
        //case MotorDirection::D_FORWARD: is_backtracking ? junc.backward++ : junc.forward++; break;
        case MotorDirection::D_FORWARD:junc.forward++; break;
        case MotorDirection::D_TURN_LEFT: junc.left++; break;
        case MotorDirection::D_TURN_RIGHT: junc.right++; break;
        case MotorDirection::D_TURN_BACKWARD: junc.backward++; break;
        default: break;
    }
}
/*
void MazeSolver::update_junction(junction junc, Direction dir){

    switch (dir)
}
*/


MotorDirection MazeSolver::choose_direction(){
    //needs to update junction where it enters and where it leaves
    
    /*
    if (is_backtracking){
        
        //update junction when entering
        //get relative direction the car enters from : junction is observer
        MotorDirection entered_from_rel = get_relative_direction (current_heading, current_junction.entered_from_heading);
        update_junction(current_junction, entered_from_rel);

        //return entered_from_rel;
    }
    */
    
    std::cout << "Entered from: " << current_junction.entered_from_heading << "\n";
    std::cout << "Current Heading: " << current_heading << "\n";
    //choose direction
    //get least traveled path at junction : junction is observer
    MotorDirection least_traveled_path = current_junction.least_traveled_path();
    //get the absolute direction of the least traveled path
    Direction exit_to_direction_abs = get_absolute_direction(current_junction.entered_from_heading, least_traveled_path);
    //get the relative direction of the least travled path : car is observer
    MotorDirection exit_to_direction_rel = get_relative_direction(current_heading, exit_to_direction_abs);

    update_junction(current_junction, exit_to_direction_rel);

    return exit_to_direction_rel;
} 


void MazeSolver::check_backtracking_status() {
    
    if (current_junction.has_unexplored_paths()) {
        is_backtracking = false;
        std::cout << "Junction has unexplored paths — stopping backtrack.\n";
    } 
    
    else {
        std::cout << "All paths explored — popping stack.\n";
        pop_stack(); 
    }
}

void MazeSolver::pop_stack(){

    path_history.pop();
    
    if (!path_history.empty()){
        
        //current_heading = flip_heading(current_heading);
        current_junction = path_history.top();
        //current_junction.entered_from_heading = flip_heading(current_heading);
    }

    std::cout << "After pop, heading: " << current_heading << ", entered_from_heading: " << current_junction.entered_from_heading << "\n";

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

    is_backtracking = true;
    std::cout << "is_backtracking is now TRUE!\n";

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


void MazeSolver::set_heading(Direction heading) {
    current_heading = heading;
}


const MotorDirection MazeSolver::flip_direction(MotorDirection dir){
    //using enum MotorDirection;

    switch(dir) {
        case MotorDirection::D_TURN_LEFT: return MotorDirection::D_TURN_RIGHT;
        case MotorDirection::D_TURN_RIGHT: return MotorDirection::D_TURN_LEFT;
        case MotorDirection::D_FORWARD: return MotorDirection::D_TURN_BACKWARD;
        case MotorDirection::D_TURN_BACKWARD: return MotorDirection::D_FORWARD;
        
        default: return dir;
    }
}

MotorDirection MazeSolver::get_relative_direction(Direction from, Direction to) {
    int diff = (to - from + 4) % 4;

    switch (diff) {
        case 0:
            return MotorDirection::D_FORWARD;
        case 1:
            return MotorDirection::D_TURN_RIGHT;
        case 2:
            return MotorDirection::D_TURN_BACKWARD;
        case 3:
            return MotorDirection::D_TURN_LEFT;
        default:
            return MotorDirection::D_STOP;
    }
}

Direction MazeSolver::get_absolute_direction(Direction current, MotorDirection move) {
    int delta = 0;

    switch (move) {
        case MotorDirection::D_FORWARD:
            delta = 0;
            break;
        case MotorDirection::D_TURN_RIGHT:
            delta = 1;
            break;
        case MotorDirection::D_TURN_BACKWARD:
            delta = 2;
            break;
        case MotorDirection::D_TURN_LEFT:
            delta = 3;
            break;
    }

    return static_cast<Direction>((current + delta) % 4);
}

Direction MazeSolver::get_new_heading(Direction current_heading, MotorDirection move) {
    int delta = 0;

    switch (move) {
        case MotorDirection::D_FORWARD:
            delta = 0;
            break;
        case MotorDirection::D_TURN_RIGHT:
            delta = 1;
            break;
        case MotorDirection::D_TURN_BACKWARD:
            delta = 2;
            break;
        case MotorDirection::D_TURN_LEFT:
            delta = 3;
            break;
        default:
            return current_heading;
    }

    return static_cast<Direction>((current_heading + delta) % 4);
}
Direction MazeSolver::get_current_heading(){

    return current_heading;
}

std::ostream& operator<<(std::ostream& os, Direction dir) {
    switch (dir) {
        case NORTH: return os << "NORTH";
        case EAST:  return os << "EAST";
        case SOUTH: return os << "SOUTH";
        case WEST:  return os << "WEST";
        default:    return os << "UNKNOWN_DIRECTION";
    }
}

Direction MazeSolver::flip_heading(Direction dir) {
    return static_cast<Direction>((dir + 2) % 4);
}


