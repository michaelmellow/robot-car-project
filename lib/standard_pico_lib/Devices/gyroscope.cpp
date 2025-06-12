#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

class MPU6500 {
public:
    MPU6500(i2c_inst_t *i2c_instance = i2c_default, 
           uint8_t address = 0x68,
           //0x68 --> Resetting the mpu6500
           uint sda_pin = PICO_DEFAULT_I2C_SDA_PIN,
           uint scl_pin = PICO_DEFAULT_I2C_SCL_PIN,
           uint baudrate = 400000)
        : i2c(i2c_instance), i2c_addr(address), 
          sda(sda_pin), scl(scl_pin), baud(baudrate) {
        initialize();
    }

    // Initialize I2C and sensor
    bool initialize() {
        i2c_init(i2c, baud);
        gpio_set_function(sda, GPIO_FUNC_I2C);
        gpio_set_function(scl, GPIO_FUNC_I2C);
        gpio_pull_up(sda);
        gpio_pull_up(scl);
        
        return reset();
    }

    // Reset the device
    bool reset() {
        const uint8_t reset_cmd[] = {PWR_MGMT_1, 0x80}; // Trigger reset
        if(!i2c_write_blocking(i2c, i2c_addr, reset_cmd, 2, false)) {
            return false;
        }
        sleep_ms(100); // Wait for reset to complete
        
        const uint8_t wake_cmd[] = {PWR_MGMT_1, 0x00}; // Wake up
        if(!i2c_write_blocking(i2c, i2c_addr, wake_cmd, 2, false)) {
            return false;
        }
        sleep_ms(10);
        
        return true;
    }

    //accelerometer data
    bool read_accel(int16_t accel[3]) {
        return read_sensor(ACCEL_XOUT_H, accel, 3);
    }

    //gyroscope data
    bool read_gyro(int16_t gyro[3]) {
        return read_sensor(GYRO_XOUT_H, gyro, 3);
    }

    // Read all sensor data
    bool read_all(int16_t accel[3], int16_t gyro[3], int16_t *temp) {
        return read_accel(accel) && 
               read_gyro(gyro);
    }

private:
    // Register addresses from MPU6050/MPU6500 datasheet
    enum Registers {
        PWR_MGMT_1   = 0x6B,
        ACCEL_XOUT_H = 0x3B,
        GYRO_XOUT_H  = 0x43
    };
    //register map - 0x6B --> Power Management 1 
    // 0x3B --> Accelerometer measurents (from 59 to 64)
    //0x43 --> Gyroscope measurements (from 67(0x43) to 72)

    bool read_sensor(uint8_t start_reg, int16_t *data, uint8_t count) {
        uint8_t buffer[6]; // Max 6 bytes needed (3 axes * 2 bytes each)
        
        // Write starting register
        if(!i2c_write_blocking(i2c, i2c_addr, &start_reg, 1, true)) {
            return false;
        }
        
        uint8_t bytes_to_read = count * 2;
        if(!i2c_read_blocking(i2c, i2c_addr, buffer, bytes_to_read, false)) {
            return false;
        }
        
        for(uint8_t i = 0; i < count; i++) {
            data[i] = (buffer[i*2] << 8) | buffer[(i*2)+1];
        }
        
        return true;
    }

    // Member variables
    i2c_inst_t *i2c;
    uint8_t i2c_addr;
    uint sda;
    uint scl;
    uint baud;
};

//https://github.com/raspberrypi/pico-examples/blob/master/i2c/mpu6050_i2c/mpu6050_i2c.c