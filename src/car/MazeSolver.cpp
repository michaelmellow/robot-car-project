#include <MazeSolver.h>
#include <MotorClass.h>

//take data from sensors
void MazeSolver::create_junction(bool front_open, bool left_open, bool right_open){
    
    if (path_history.size() != 0) path_history.push(current_junction);
    
    current_junction.reset();

    if (front_open) current_junction.forward = 0;
    if (left_open)  current_junction.left = 0;
    if (right_open) current_junction.right = 0;
} 

void MazeSolver::update_junction(junction junc, MotorDirection dir){
    using enum MotorDirection;

    switch (dir){
        
        case D_FORWARD: junc.forward++; break;
        case D_TURN_LEFT: junc.left++; break;
        case D_TURN_RIGHT: junc.right++; break;
        default: break;
    }

}
MotorDirection MazeSolver::choose_direction(){
    
    MotorDirection chosen_direction = current_junction.min(); 

    update_junction(current_junction, chosen_direction);
    return chosen_direction;


    /*if (chosen_direction == D_FORWARD){

        update_junction(current_junction, D_FORWARD);
        return D_FORWARD;
    }

    else if (chosen_direction == D_TURN_LEFT){

        update_junction(current_junction, D_TURN_LEFT);
        return D_TURN_LEFT;
    }

    else if (chosen_direction == D_TURN_RIGHT){

        update_junction(current_junction, D_TURN_RIGHT);
        return D_TURN_RIGHT;
    }*/

} 



