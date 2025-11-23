/* #include "init.h"
//#include "task.h"
//#include "handlers.h"
#include <stdint.h>

volatile uint32_t tick_count = 0;
volatile uint8_t btn9_pressed = 0; // PB9  смена частоты   
volatile uint32_t btn9_press_time = 0;   // время нажатия PB9
volatile uint8_t counter1 = 0;

volatile uint8_t  btn8_pressed = 0; // PB8 переключение LED
volatile uint32_t btn8_press_time = 0;
volatile uint8_t pwm_mode = 0;
volatile uint8_t counter = 0;


int main(void)
{
    GPIO_Ini();
    //RCC_Init();
    IRO_INInt();
    TIM10_Init();
    //TIM2_PWM_Init();
    //TIM3_PWM_Init();
    TIM1_PWM_Init();

    while (1)
    {
        if (BUTTON_READ())
        {
            delay(1000000);
            MODIFY_REG(TIM1->CCR1, TIM_CCR1_CCR1_Msk, 250UL); // ПЕРВЫЙ двигатель - тот что ближе к драйверу
            MODIFY_REG(TIM1->CCR4, TIM_CCR4_CCR4_Msk, 250UL); // ВТОРОЙ двигатель - тот что ближе к преобразователю
            delay(2000000);
        }
        else
        {
            MODIFY_REG(TIM1->CCR1, TIM_CCR1_CCR1_Msk, 0UL); // ПЕРВЫЙ двигатель - тот что ближе к драйверу
            MODIFY_REG(TIM1->CCR4, TIM_CCR4_CCR4_Msk, 0UL); // ВТОРОЙ двигатель - тот что ближе к преобразователю
        }
    }
}

// второй двигатель крутится лучше */

#include "mpu6050.h"

MPU6050_Data mpu_data;

int main(void) {
    // Твоя инициализация системы с любой частотой
    // Например: 84 MHz, 100 MHz, etc...
    
    // Инициализация MPU6050 
    MPU6050_Init();  // Автоматически подстроится под твою частоту
    
    while(1) {
        MPU6050_Read(&mpu_data);
        // Используй данные...
        
        //delay_ms(100);
    }
}