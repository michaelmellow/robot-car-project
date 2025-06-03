#include "ReactToDistance.h"

NavigateCar::NavigateCar()
{
    motor.stop();
}

void NavigateCar::decideTurn(float distance, float left_distance, float right_distance)
{

    
        if (distance >= 15)
        {
            motor.forward_move(80);

            // if it gets too close to a wall on each side it should move using lateral moving
            // to move slightly away from the wall to avoid hitting it

            if (right_distance < 10 && left_distance > 10)
            {

                motor.left_lateral(80);
                DEV_Delay_ms(400);
                motor.stop();
            }
            else if (left_distance < 10 && right_distance > 10)
            {
                motor.right_lateral(80);
                DEV_Delay_ms(400);
                motor.stop();
            }
        }

        else if (right_distance > 15 && distance < 15)
        {
            motor.stop();
            DEV_Delay_ms(50);
            printf("Always chose to turn right.");
            motor.turn_right(60);
            DEV_Delay_ms(100);

            // distance = front.getDistance();
            if (distance < 15)
            {
                motor.stop();
            }
        }

        else if (left_distance > 15 && distance < 15)
        {
            motor.stop();
            DEV_Delay_ms(50);
            printf("Path on the left is clear, turn left");
            motor.turn_left(60);
            DEV_Delay_ms(100);

            // distance = front.getDistance();
            if (distance < 15)
            {
                motor.stop();
            }
        }

             else if(distance < 15 && left_distance < 15 && right_distance < 15)
               {
                   printf("Dead end! No way out, make 180 degrees turn");
                   motor.stop();
                   DEV_Delay_ms(50);

                   if(distance < 15 && left_distance < 15 && right_distance < 15) {
                   motor.backward_move(70);
                   DEV_Delay_ms(200);
                   motor.turn_180(50);
                   DEV_Delay_ms(400);
                   motor.forward_move(70);
                   DEV_Delay_ms(1500);
                   motor.stop();
               // try to get the distance again it might not be updating
               //try having an else in which the motor stops and after that in the else having an if statement where checking for the 3 distances
               //and making all of the moves in this if, after that updating the distances again and having another if to stop the car
                   //distance = front.getDistance();
                   if (distance < 15)
                   {
                       motor.stop();
                   }
               }
               }
}