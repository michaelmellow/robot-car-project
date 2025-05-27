#include <MazeSolver.h>

MazeSolver::MazeSolver(){}
//take data from sensors ~~ is_valid_junction() or something ~~ should also probally detect dead-ends
void MazeSolver::create_junction(bool front_open, bool left_open, bool right_open){
    
    if (!is_first_junction){
        
        path_history.push(current_junction);
    }

    else is_first_junction = false;

    current_junction.reset();

    current_junction.forward = front_open ? 0 : 2;
    current_junction.left = left_open ? 0 : 2;
    current_junction.right = right_open ? 0 : 2;
    
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
        
        handle_deadend();

        if (!path_history.empty()) {
            
            current_junction = path_history.top();
            path_history.pop();
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

void MazeSolver::handle_deadend(){
    
    //turn 180 degrees
    is_backtracking = true;
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
    std::cout << "Forward: " << current_junction.forward << "\n";
    std::cout << "Left: " << current_junction.left << "\n";
    std::cout << "Right: " << current_junction.right << "\n";
    std::cout << "Backward: " << current_junction.backward << "\n";
}

