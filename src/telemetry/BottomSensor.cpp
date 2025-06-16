#include "BottomSensor.h"

BottomSensor::BottomSensor() {
    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);
    adc_gpio_init(28);
}

void BottomSensor::start_check () {
    // adc0 / pin 26
    adc_select_input(0);
    uint16_t sensor_left = adc_read();

    // ADC1 / pin 27
    adc_select_input(1);
    uint16_t sensor_middle = adc_read();

    // ADC2 / pin 28
    adc_select_input(2);
    uint16_t sensor_right = adc_read();

    // light surface
    if (sensor_left < 1000 || sensor_middle < 1000 || sensor_right < 1000) {
        
        light_color_counter_++;
    }

}

int BottomSensor::get_light_color_counter(){

    return light_color_counter_;
}
