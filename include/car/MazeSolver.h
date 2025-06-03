#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include "MotorClass.h"  // Required for MotorDirection
#include "SensorArray.h" // Required for sensor_status

#include <stack>
#include <array>
#include <iostream>

struct junction{

    int forward = 0;
    int left = 0;
    int right = 0;
    int backward = 0;

    void reset() {
        forward = 0;
        left = 0;
        right = 0;
        backward = 0;
    }

    bool has_unexplored_paths() const {
        return (forward == 0) || (left == 0) || (right == 0);
    }

    MotorDirection least_traveled_path(){

        if (forward == 0) return MotorDirection::D_FORWARD;
        if (left == 0) return MotorDirection::D_TURN_LEFT;
        if (right == 0) return MotorDirection::D_TURN_RIGHT;
        
        if (forward <= left && forward <= right) return MotorDirection::D_FORWARD;
        if (left <= forward && left <= right) return MotorDirection::D_TURN_LEFT;
        
        return MotorDirection::D_TURN_RIGHT;
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

        MotorDirection get_best_path (junction &junc);
        MotorDirection choose_direction();
        MotorDirection flip_direction(MotorDirection &dir);
        MotorDirection adjust (sensor_reading sensors);


        junction get_current_junction();

        bool get_is_backtracking();

    private:
        
        bool is_backtracking = false;
        bool is_first_junction = true;

        junction current_junction;
        std::stack<junction> path_history;

        const float SENSOR_DIFFERENCE = 15.0;

        
};

#endif