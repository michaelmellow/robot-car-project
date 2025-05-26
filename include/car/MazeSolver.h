#include <Car.h>
#include <stack>
#include <array>
//choose minor for 2nd year
enum class MotorDirection; // forward declaration from MotorClass.h

//enum MazeSolverDirection { FORWARD, LEFT, RIGHT, BACK }; 

struct junction{
    
    int forward = -1;
    int left = -1;
    int right = -1;

    void reset() {
        forward = -1;
        left = -1;
        right = -1;
    }

    MotorDirection min(){
        
        MotorDirection direction = MotorDirection::D_TURN_RIGHT;
        int minimum = -1;
    
        if (forward > 0) {
            minimum = forward;
            direction = MotorDirection::D_FORWARD;
        }

        if (left > 0 && (minimum == -1 || left < minimum)) {
            minimum = left;
            direction = MotorDirection::D_TURN_LEFT;
        }

        if (right > 0 && (minimum == -1 || right < minimum)) {
            
            direction = MotorDirection::D_TURN_RIGHT;
        }

        return direction
    }
};


class MazeSolver{

    public:

        void create_junction(bool front_open, bool left_open, bool right_open);
        void update_junction();
        void choose_direction();
        void back_track_to_open_junction();
        int find_last_open_junction();    

    private:

        junction current_junction;
        std::stack<junction> path_history;
        

};