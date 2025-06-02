#include "TestFunctions.h"

void full_movement_test(){

    uint current_time = to_ms_since_boot(get_absolute_time());
    Car car;

    while (current_time <= 2000) {
        car.getMotorController().forward_move(100);
        current_time = to_ms_since_boot(get_absolute_time());
    }
    car.getMotorController().stop();

    while (current_time <= 4000) {
        car.getMotorController().backward_move(100);
        current_time = to_ms_since_boot(get_absolute_time());
    }
    car.getMotorController().stop();

    while (current_time <= 6000) {
        car.getMotorController().left_lateral(100);
        current_time = to_ms_since_boot(get_absolute_time());
    }
    car.getMotorController().stop();

    while (current_time <= 8000) {
        car.getMotorController().right_lateral(100);
        current_time = to_ms_since_boot(get_absolute_time());
    }


    car.getMotorController().stop();
}

void new_test(Car car){
    sleep_ms(5000);

    car.getMotorController().forward_move(100);

    sleep_ms(1000);

    car.getMotorController().stop();

    sleep_ms(1000);

    car.getMotorController().turn_right();

    sleep_ms(1000);
    car.getMotorController().turn_180();
    sleep_ms(15000);
    
}

/*void turn_test() {
    MotorClass a;
    a.turn_left();
    sleep_ms(2000);
    a.turn_right();
    sleep_ms(2000);
    a.turn_180();
    sleep_ms(5000);
}*/


void maze_solver_test(Car car){

    
}

void Navigate()
{
    stdio_init_all(); 
    printf("Program started...\n");

    MotorClass motor;
    // setup sensors trigger, echo
    Ultrasonic s_front(15, 16); 
    Ultrasonic s_F_right(14, 17);
    Ultrasonic s_F_left(13, 18);
    Ultrasonic s_right(12, 19);
    Ultrasonic s_left(11, 10);

    float WALL_DISTANCE = 15.0f;
    float SAFE_DISTANCE = 17.0f;

    while(true)
    {
        float Front = s_front.getDistance(); // front distance
        float F_Right = s_F_right.getDistance(); // front distance
        float F_Left = s_F_left.getDistance(); // front distance
        float Right = s_right.getDistance(); // right distance
        float Left = s_left.getDistance(); // left distance

        printf("Front: %.2f cm, Left: %.2f cm, Right: %.2f cm\n", Front, Left, Right);
        printf("######## ENTERED #######\n");
        
        // if the front is clear
        if(Front > WALL_DISTANCE){
            // if the car is close to the right wall
            if(F_Right < SAFE_DISTANCE){
                motor.CurvedTurnLeft(40);
            }
            // if the car is close to the left wall
            else if(F_Left < SAFE_DISTANCE){
                motor.CurvedTurnRight(40);
            }
            // if all sensors are clear
            else {
                motor.forward_move(40);
            }
        } 
        // if the front sensor detect wall closer 
        else {
            // if the right side is clear turn right 
            if(Right > WALL_DISTANCE && Right > Left){
                motor.turn_right(40);
                sleep_ms(400);
                if(Front > WALL_DISTANCE){
                    motor.forward_move(40);
                }
            }
            // if the left side is clear turn left
            else if(Left > WALL_DISTANCE && Left > Right){
                motor.turn_left(40);
                sleep_ms(400);
                if(Front > WALL_DISTANCE){
                    motor.forward_move(40);
                }
            }
        }

        sleep_ms(400);  
    }
}
