#include "mpu6050.h"

// Автоматическое определение частоты APB1
static uint32_t get_apb1_frequency(void) {
    return SystemCoreClock / (((RCC->CFGR >> 10) & 0x7) + 1);
}

// Инициализация I2C1 с любой частотой
void I2C1_Init(uint32_t i2c_speed_khz) {
    uint32_t apb1_freq = get_apb1_frequency();
    uint32_t ccr_value;
    
    // Включаем тактирование
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    
    // Настройка PB8 (SCL) и PB9 (SDA)
    GPIOB->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9);
    GPIOB->MODER |= (2 << GPIO_MODER_MODER8_Pos) | (2 << GPIO_MODER_MODER9_Pos);
    GPIOB->OTYPER |= GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_9;
    GPIOB->PUPDR |= (1 << (2 * 8)) | (1 << (2 * 9));
    GPIOB->AFR[1] |= (4 << (4 * 0)) | (4 << (4 * 1));
    
    // Сброс I2C
    I2C1->CR1 &= ~I2C_CR1_PE;
    I2C1->CR1 = I2C_CR1_SWRST;
    I2C1->CR1 = 0;
    
    // Настройка частоты I2C
    I2C1->CR2 = (apb1_freq / 1000000) & I2C_CR2_FREQ;
    
    // Расчет CCR для Standard Mode (100 kHz)
    ccr_value = apb1_freq / (i2c_speed_khz * 2000);
    if(ccr_value < 4) ccr_value = 4;
    I2C1->CCR = ccr_value;
    
    // Расчет TRISE
    I2C1->TRISE = (apb1_freq / 1000000) + 1;
    
    // Включаем I2C
    I2C1->CR1 |= I2C_CR1_PE;
}

// Остальные функции остаются такими же...
static void I2C_WaitFlag(uint32_t flag) {
    uint32_t timeout = 100000;
    while(!(I2C1->SR1 & flag) && timeout--);
}

static void MPU6050_WriteReg(uint8_t reg, uint8_t value) {
    I2C1->CR1 |= I2C_CR1_START;
    I2C_WaitFlag(I2C_SR1_SB);
    I2C1->DR = MPU6050_ADDR << 1;
    I2C_WaitFlag(I2C_SR1_ADDR);
    (void)I2C1->SR2;
    
    I2C_WaitFlag(I2C_SR1_TXE);
    I2C1->DR = reg;
    
    I2C_WaitFlag(I2C_SR1_TXE);
    I2C1->DR = value;
    
    I2C_WaitFlag(I2C_SR1_BTF);
    I2C1->CR1 |= I2C_CR1_STOP;
}

static void MPU6050_ReadBytes(uint8_t reg, uint8_t *data, uint8_t len) {
    I2C1->CR1 |= I2C_CR1_START;
    I2C_WaitFlag(I2C_SR1_SB);
    I2C1->DR = MPU6050_ADDR << 1;
    I2C_WaitFlag(I2C_SR1_ADDR);
    (void)I2C1->SR2;
    
    I2C_WaitFlag(I2C_SR1_TXE);
    I2C1->DR = reg;
    
    I2C_WaitFlag(I2C_SR1_TXE);
    I2C1->CR1 |= I2C_CR1_START;
    I2C_WaitFlag(I2C_SR1_SB);
    I2C1->DR = (MPU6050_ADDR << 1) | 1;
    I2C_WaitFlag(I2C_SR1_ADDR);
    (void)I2C1->SR2;
    
    for(uint8_t i = 0; i < len; i++) {
        if(i == len - 1) {
            I2C1->CR1 &= ~I2C_CR1_ACK;
            I2C_WaitFlag(I2C_SR1_RXNE);
            data[i] = I2C1->DR;
            I2C1->CR1 |= I2C_CR1_STOP;
        } else {
            I2C_WaitFlag(I2C_SR1_RXNE);
            data[i] = I2C1->DR;
        }
    }
    I2C1->CR1 |= I2C_CR1_ACK;
}

void MPU6050_Init(void) {
    // Инициализация I2C на 100 kHz
    I2C1_Init(100);
    
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x00);
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x08);
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x08);
    
    for(volatile int i = 0; i < 100000; i++);
}

void MPU6050_Read(MPU6050_Data *data) {
    uint8_t buffer[14];
    MPU6050_ReadBytes(MPU6050_ACCEL_XOUT_H, buffer, 14);
    
    data->accel_x = (buffer[0] << 8) | buffer[1];
    data->accel_y = (buffer[2] << 8) | buffer[3];
    data->accel_z = (buffer[4] << 8) | buffer[5];
    data->gyro_x = (buffer[8] << 8) | buffer[9];
    data->gyro_y = (buffer[10] << 8) | buffer[11];
    data->gyro_z = (buffer[12] << 8) | buffer[13];
}