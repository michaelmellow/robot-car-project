#include "BottomSensor.h"

BottomSensor::BottomSensor() {
    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);
    adc_gpio_init(28);
}

bool BottomSensor::start_check () {
    // adc0 / pin 26
    adc_select_input(0);
    uint16_t sensor_left = adc_read();

    // ADC1 / pin 27
    adc_select_input(1);
    uint16_t sensor_middle = adc_read();

    // ADC2 / pin 28
    adc_select_input(2);
    uint16_t sensor_right = adc_read();


    MotorClass c;

    // likely a white or light surface
    if (sensor_left > 3000 || sensor_middle > 3000 || sensor_right > 3000) {
        light_color_counter_++;
        c.turn_right();

    }
    // likely a black or dark surface
    else if (sensor_left > 1000 || sensor_middle > 1000 || sensor_right > 1000) {
        c.forward_move(100);
    }

    if (light_color_counter_ >= 3) {
        return true;
    }
    return false;
}