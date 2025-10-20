#include "stdint.h"
#include "stm32f4xx.h"
#include "stm32f411xe.h"
void delay(volatile uint32_t count);
void GPIO_Init_with_CMSIS(void);
void GPIO_Init_with_my_macro(void);

// ВКЛЮЧЕНИЕ ТАКТИРОВАНИЯ
#define RCC_GPIO (*(uint32_t*)(0x40023800UL + 0x30UL)) // обращение к регистру AHB1ENR
#define RCC_GPIOA_ON 0x01UL // обращение к первому биту регистра AHB1ENR
#define RCC_GPIOB_ON 0x02UL // обращение ко второму биту регистра AHB1ENR

// ЧТЕНИЕ С КНОПОК
#define READ_GPIO_B1 (*(uint32_t*)(0x40020400 + 0x10UL) & 0x2) // чтение PB1
#define READ_GPIO_B2 (*(uint32_t*)(0x40020400 + 0x10UL) & 0x4) // чтение PB2
#define READ_GPIO_B3 (*(uint32_t*)(0x40020400 + 0x10UL) & 0x8) // чтение PB3
#define READ_GPIO_B8 (*(uint32_t*)(0x40020400 + 0x10UL) & 0x100) // чтение PB8

// ИЗМЕНЕНИЕ БИТОВ
#define SET_GPIO_A5 (*(uint32_t*)(0x40020000 + 0x18UL) = 0x20) // установка бита PA5
#define SET_GPIO_A10 (*(uint32_t*)(0x40020000 + 0x18UL) = 0x400) // установка бита PA10
#define SET_GPIO_A11 (*(uint32_t*)(0x40020000 + 0x18UL) = 0x800) // установка бита PA11
#define RESET_GPIO_A5 (*(uint32_t*)(0x40020000 + 0x18UL) = 0x200000) // снятие бита PA5
#define RESET_GPIO_A10 (*(uint32_t*)(0x40020000 + 0x18UL) = 0x4000000) // снятие бита PA10
#define RESET_GPIO_A11 (*(uint32_t*)(0x40020000 + 0x18UL) = 0x8000000) // снятие бита PA11

// НАСТРОЙКА ДЛЯ КНОПОК
#define GPIOB_MODER (*(uint32_t*)(0x40020400UL + 0x00UL)) // определение режима работы
#define GPIOB_MODER_CLEAR (*(uint32_t*)(0x40020400UL + 0x00UL))
#define GPIOB_PUPDR (*(uint32_t*)(0x40020400UL + 0x0CUL)) // подтягивающий резистор

// НАСТРОЙКА ДЛЯ СВЕТОДИОДОВ
#define GPIOA_MODER (*(uint32_t*)(0x40020000UL + 0x00UL)) // определение режима работы
#define GPIOA_OTYPER (*(uint32_t*)(0x40020000UL + 0x04UL)) // выбираем тип выхода 
#define GPIOA_OSPEEDR (*(uint32_t*)(0x40020000UL + 0x08UL)) // выбираем скорость работы
#define GPIOA_PUPDR (*(uint32_t*)(0x40020000UL + 0x0CUL)) // подтягивающий резистор

// КОНКРЕТНЫЕ БИТЫ ДЛЯ КНОПОК
#define GPIOB_MODE_PIN1_OUT 0x4UL // PB1 на вход
#define GPIOB_MODE_PIN2_OUT 0x10UL // PB2 на вход
#define GPIOB_MODE_PIN3_OUT 0x40UL // PB3 на вход
#define GPIOB_MODE_PIN8_OUT 0x10000UL // PB8 на вход

#define GPIOB_PUPD_PIN1_PULL_UP 0x4UL // PB1 pull-up
#define GPIOB_PUPD_PIN2_PULL_UP 0x10UL // PB2 pull-up
#define GPIOB_PUPD_PIN3_PULL_UP 0x40UL // PB3 pull-up
#define GPIOB_PUPD_PIN8_PULL_UP 0x10000UL // PB8 pull-up

// КОНКРЕТНЫЕ БИТЫ ДЛЯ СВЕТОДИОДОВ
#define GPIOA_MODE_PIN5_OUT 0x400UL // PA5 на выход

#define GPIOA_MODE_PIN10_OUT 0x100000UL // PA10 на выход
#define GPIOA_MODE_PIN11_OUT 0x400000UL // PA11 на выход

#define GPIOA_OTYPE_PIN10_PP 0x0000UL // PA10 push-pull
#define GPIOA_OTYPE_PIN11_PP 0x0000UL // PA11 push-pull

#define GPIOA_OSPEED_PIN10_HS 0x300000UL // PA10 высокая скорость
#define GPIOA_OSPEED_PIN11_HS 0xC00000UL // PA11 высокая скорость

#define GPIOA_PUPD_PIN10_NOPUPD 0x0000UL // PA10 без подтягивающего резистора
#define GPIOA_PUPD_PIN11_NOPUPD 0x0000UL // PA11 без подтягивающего резистора

// КОМАНДА ДЛЯ ТЕСТА
