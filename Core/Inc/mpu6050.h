#ifndef MPU6050_H
#define MPU6050_H


#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f411xe.h"

#define MPU6050_ADDR 0x68

// Регистры MPU6050
#define MPU6050_WHO_AM_I     0x75
#define MPU6050_PWR_MGMT_1   0x6B
#define MPU6050_GYRO_CONFIG  0x1B
#define MPU6050_ACCEL_CONFIG 0x1C
#define MPU6050_ACCEL_XOUT_H 0x3B

typedef struct {
    int16_t accel_x, accel_y, accel_z;
    int16_t gyro_x, gyro_y, gyro_z;
} MPU6050_Data;

void I2C1_Init(uint32_t i2c_speed_khz);
void MPU6050_Init(void);
void MPU6050_Read(MPU6050_Data *data);

#endif