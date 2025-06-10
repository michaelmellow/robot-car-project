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

    car.getMotorController().turn_right(100);

    sleep_ms(1000);
    car.getMotorController().turn_180(100);
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

    BottomSensor bottomsensor;

    float WALL_DISTANCE = 15.0f;
    float SAFE_DISTANCE = 17.0f;
    float clear_rout = 30.0f;

    Route currentRoute = ROUTE_A;

    while(true)
    {
        bottomsensor.start_check();

        if(bottomsensor.get_light_counter() > 0){
            printf("Treasure chamber detected! Stopping car...\n");
            motor.stop();
            break;
        }

        float Front = s_front.getDistance(); // front distance
        float F_Right = s_F_right.getDistance(); // front distance
        float F_Left = s_F_left.getDistance(); // front distance
        float Right = s_right.getDistance(); // right distance
        float Left = s_left.getDistance(); // left distance

        printf("Front: %.2f cm, Left: %.2f cm, Right: %.2f cm\n", Front, Left, Right);
        printf("######## ENTERED #######\n");
        
        // if the front is not clear
        if(Front < WALL_DISTANCE){
            // turn left to avoid collision
            motor.turn_left(40);
            sleep_ms(400);
        } 
        // if the right side is clear to turn
        else if(Right > clear_rout){
            if (currentRoute == ROUTE_A) {
                motor.forward_move(40); // Move forward a bit to align the back of the car
                sleep_ms(400);  

                // Turn to the right and switch to ROUTE_B
                motor.turn_right(40);
                sleep_ms(400);
                
                motor.forward_move(40);
                sleep_ms(400);

                // Now we're on Route B
                currentRoute = ROUTE_B;
            }
            else {
                motor.forward_move(40);
            }
        }
        else {
            // switched to the rout A 
            currentRoute = ROUTE_A;

            if (currentRoute == ROUTE_A){
                // Too close to right wall, align the car
                if (F_Right < SAFE_DISTANCE) {
                    motor.CurvedTurnLeft(40);
                }
                // Too close to left wall, align the car
                else if (F_Left < SAFE_DISTANCE) {
                    motor.CurvedTurnRight(40);
                }
                else {
                    // Just right, go straight
                    motor.forward_move(40);
                }
            }
        }

        sleep_ms(400);  
    }
}