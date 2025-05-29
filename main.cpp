#include "pico/stdlib.h"
#include <stdio.h>

#include "Car.h"
#include "Ultrasonic.h"
#include "MotorClass.h"
#include "ReactToDistance.h"

int main()
{
    stdio_init_all(); 
    printf("Program started...\n");

    MotorClass motor;
    // setup sensors trigger, echo
    Ultrasonic s_front(15, 16); 
    Ultrasonic s_right(14, 17);
    Ultrasonic s_left(13, 18);

    float WALL_DISTANCE = 15.0f;

    while(true)
    {
        float Front = s_front.getDistance(); // front distance
        float Right = s_right.getDistance(); // right distance
        float Left = s_left.getDistance(); // left distance

        printf("Front: %.2f cm, Left: %.2f cm, Right: %.2f cm\n", Front, Left, Right);
        printf("######## ENTERED #######\n");
        
        // if the front is clear
        if(Front > WALL_DISTANCE){
            // if the car is close to the right wall
            if(Right < WALL_DISTANCE){
                motor.CurvedTurnLeftt(40);
            }
            // if the car is close to the left wall
            else if(Left < WALL_DISTANCE){
                motor.CurvedTurnRight(40);
            }
            // if all sensors are clear
            else {
                motor.forward_move(40);
            }
        } 
        // if the front sensor detects a nearby wall
        else {
            // if the right side is clear
            if(Right > WALL_DISTANCE && Right > Left){
                motor.turn_right(50);
                sleep_ms(400);
                if(Front > WALL_DISTANCE){
                    motor.forward_move(40);
                }
            }
            // if the left side is clear
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
