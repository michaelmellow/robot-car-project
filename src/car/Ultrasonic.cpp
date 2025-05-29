#include "Ultrasonic.h"
#include "MotorDriver.h"
#include <cstdio>

Ultrasonic::Ultrasonic(uint8_t triggerPin, uint8_t echoPin) : triggerPin_(triggerPin), echoPin_(echoPin), motorsRunning(true) {
    DEV_GPIO_Mode(triggerPin_, GPIO_OUT);
    DEV_GPIO_Mode(echoPin_, GPIO_IN);
}

float Ultrasonic::getDistance() {
    uint32_t pulseDuration;
    float distance;

    DEV_Digital_Write(triggerPin_, 0);
    DEV_Delay_us(2);
    DEV_Digital_Write(triggerPin_, 1);
    DEV_Delay_us(10);
    DEV_Digital_Write(triggerPin_, 0);

    uint32_t timeout = time_us_32() + 30000;

    // Wait for echo to go HIGH
    while (DEV_Digital_Read(echoPin_) == 0 && time_us_32() < timeout);
    if (time_us_32() >= timeout) {
        printf("Echo start timeout!\n");
        return -1;
    }
    uint32_t startTime = time_us_32();

    // Wait for echo to go LOW
    timeout = startTime + 30000;
    while (DEV_Digital_Read(echoPin_) == 1 && time_us_32() < timeout);
    if (time_us_32() >= timeout) {
        printf("Echo end timeout!\n");
        return -1;
    }
    uint32_t endTime = time_us_32();

    pulseDuration = endTime - startTime;
    printf("Pulse Duration: %d microseconds\n", pulseDuration);

    distance = pulseDuration * 0.0343 / 2.0;
    printf("Distance: %.2f cm\n", distance);

    return distance;
}

void Ultrasonic::TestSensor() {
    float distance = getDistance();

    if (distance < 25 && motorsRunning) {
        printf("Object too close! Stopping motors...\n");
        Motor_Stop(MOTORA);
        Motor_Stop(MOTORB);
        Motor_Stop(MOTORC);
        Motor_Stop(MOTORD);
        motorsRunning = false;
    } else if (distance >= 25 && !motorsRunning) {
        printf("Path clear. Resuming motors...\n");
        Motor_Run(MOTORA, FORWARD, 80);
        Motor_Run(MOTORB, FORWARD, 80);
        Motor_Run(MOTORC, FORWARD, 80);
        Motor_Run(MOTORD, FORWARD, 80);
        motorsRunning = true;
    }
}
