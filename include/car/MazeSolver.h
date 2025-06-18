#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include "MotorClass.h"  // Required for MotorDirection
#include "SensorArray.h" // Required for sensor_status

#include <stack>
#include <array>
#include <iostream>

enum Direction {
    
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

std::ostream& operator<<(std::ostream& os, Direction dir);

struct junction{

    int forward = 0;
    int left = 0;
    int right = 0;
    int backward = 0;
    Direction entered_from_heading;

    void reset() {
        forward = 0;
        left = 0;
        right = 0;
        backward = 0;
    }

    bool has_unexplored_paths() const {
        return (forward == 0) || (left == 0) || (right == 0);
    }

    MotorDirection least_traveled_path() {
        if (forward == 0) return MotorDirection::D_FORWARD;
        if (left == 0) return MotorDirection::D_TURN_LEFT;
        if (right == 0) return MotorDirection::D_TURN_RIGHT;
        if (backward == 0) return MotorDirection::D_TURN_BACKWARD;

        int min_val = backward;
        MotorDirection min_dir = MotorDirection::D_TURN_BACKWARD;

        if (forward < min_val) {
            min_val = forward;
            min_dir = MotorDirection::D_FORWARD;
        }
        if (left < min_val) {
            min_val = left;
            min_dir = MotorDirection::D_TURN_LEFT;
        }
        if (right < min_val) {
            min_val = right;
            min_dir = MotorDirection::D_TURN_RIGHT;
        }

        return min_dir;
    }

};


class MazeSolver{

    public:
        MazeSolver();

        void create_junction(sensor_status sensors);
        void update_junction(junction &junc, MotorDirection &dir);
        void handle_deadend();
        void check_backtracking_status();
        void print_current_junction();
        void pop_stack();
        void set_heading(Direction heading);
        
        bool is_path_history_empty();
        

        MotorDirection choose_direction();
        const MotorDirection flip_direction(MotorDirection dir);
        MotorDirection adjust (sensor_reading sensors);
        MotorDirection get_relative_direction(Direction from, Direction to);
        
        Direction get_absolute_direction(Direction current, MotorDirection move);
        Direction get_new_heading(Direction current_heading, MotorDirection move);
        Direction get_current_heading();
        Direction flip_heading(Direction dir);


        junction get_current_junction();
        bool get_is_backtracking();
       //std::stack<junction>& get_path_history();

    private:
        
        bool is_backtracking = false;
        bool is_first_junction = true;

        junction current_junction;
        std::stack<junction*> path_history;
        Direction current_heading = NORTH;

        const float ADJUST_SENSOR_DIFFERENCE = 10.0;

        
};

#endif