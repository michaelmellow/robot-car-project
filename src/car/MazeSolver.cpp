#include <MazeSolver.h>
#include <MotorClass.h>


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



void MazeSolver::update_junction(junction junc, MotorDirection dir){
    using enum MotorDirection;

    switch (dir){
        
        case D_FORWARD: is_backtracking ? junc.backward++ : junc.forward++; break;
        case D_TURN_LEFT: junc.left++; break;
        case D_TURN_RIGHT: junc.right++; break;
        default: break;
    }
}


MotorDirection MazeSolver::choose_direction(){
    
    if (is_backtracking && !current_junction.has_unexplored_paths()) {
        
        if (!path_history.empty()) {
            
            current_junction = path_history.top();
            path_history.pop();
        } 
        
        else {
            
        }
    }
    
    MotorDirection chosen_direction = get_best_path(current_junction);

    if (is_backtracking){
        
        chosen_direction = flip_direction(chosen_direction);

    }

    update_junction(current_junction, chosen_direction);
    return chosen_direction;

} 

MotorDirection MazeSolver::flip_direction(MotorDirection dir) const {
    
    switch(dir) {
        case MotorDirection::D_TURN_LEFT: return MotorDirection::D_TURN_RIGHT;
        case MotorDirection::D_TURN_RIGHT: return MotorDirection::D_TURN_LEFT;
        
        default: return dir;
    }
}

bool MazeSolver::handle_deadend(){
    
    //deadend found!
    create_junction(false, false, false);

    //turn 180 degrees
    is_backtracking = true;
}

MotorDirection MazeSolver::get_best_path(junction junc){
        
    if (junc.forward == 0) return MotorDirection::D_FORWARD;
    if (junc.left == 0) return MotorDirection::D_TURN_LEFT;
    if (junc.right == 0) return MotorDirection::D_TURN_RIGHT;
    
    if (junc.forward == 1 && junc.left != 1 && junc.right != 1) return MotorDirection::D_FORWARD;
    if (junc.left == 1 && junc.right != 1) return MotorDirection::D_TURN_LEFT;
    
    return MotorDirection::D_TURN_RIGHT;
}

void MazeSolver::check_backtracking_status() {
    if (is_backtracking && current_junction.has_unexplored_paths()) {
        
        is_backtracking = false;
    }
}





