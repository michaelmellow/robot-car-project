#include <Car.h>
#include <stack>
#include <array>

enum class MotorDirection; // forward declaration from MotorClass.h

//enum MazeSolverDirection { FORWARD, LEFT, RIGHT, BACK }; 

struct junction{

    int forward = 0;
    int left = 0;
    int right = 0;
    int backward = 0

    void reset() {
        forward = 0;
        left = 0;
        right = 0;
        backward = 0
    }

    bool has_unexplored_paths() const {
        return (forward == 0) || (left == 0) || (right == 0);
    }
};


class MazeSolver{

    public:
        MazeSolver();

        void create_junction(bool front_open, bool left_open, bool right_open);
        void update_junction(junction junc, MotorDirection dir);
        
        MotorDirection get_best_path (junction junc);
        MotorDirection choose_direction();
        
        bool handle_deadend();

        MotorDirection flip_direction(MotorDirection dir);
        void check_backtracking_status

    private:
        
        MotorClass motorController;

        bool is_backtracking;
        bool is_first_junction = true;

        junction current_junction;
        std::stack<junction> path_history;
        

};