#include "init.h"

void GPIO_Init_with_CMSIS(void)
{
    /////////////////////////////////////////////////////////////////////

    // Включаем тактирование GPIOA и GPIOB (бит 0 в RCC->AHB1ENR)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;

    /////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////

    // Настройка PB1 как вход с подтяжкой вверх (кнопка)
    GPIOB->MODER &= ~(0x3 << (1 * 2));  
    GPIOB->PUPDR &= ~(0x3 << (1 * 2));  
    GPIOB->PUPDR |= (0x1 << (1 * 2));   // режим подтяжки вверх

    /////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////

    // Настройка PB2 как вход с подтяжкой вверх (кнопка)
    GPIOB->MODER &= ~(0x3 << (2 * 2));  
    GPIOB->PUPDR &= ~(0x3 << (2 * 2));  
    GPIOB->PUPDR |= (0x1 << (2 * 2));   // режим подтяжки вверх

    /////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////

    // Настройка PB3 как вход с подтяжкой вверх (кнопка)
    GPIOB->MODER &= ~(0x3 << (3 * 2));  
    GPIOB->PUPDR &= ~(0x3 << (3 * 2));  
    GPIOB->PUPDR |= (0x1 << (3 * 2));   // режим подтяжки вверх

    /////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////

    // Настройка PB8 как вход с подтяжкой вверх (кнопка)
    GPIOB->MODER &= ~(0x3 << (8 * 2));  
    GPIOB->PUPDR &= ~(0x3 << (8 * 2));  
    GPIOB->PUPDR |= (0x1 << (8 * 2));   // режим подтяжки вверх

    /////////////////////////////////////////////////////////////////////

    // Настраиваем PA5 как выход (MODER5[1:0] = 01)
    GPIOA->MODER &= ~(0x3 << (5 * 2)); // Сбрасываем биты MODER5
    GPIOA->MODER |=  (0x1 << (5 * 2)); // Устанавливаем режим Output

    /////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////

    // A10

    // Настраиваем PA10 как выход (MODER10[1:0] = 01)
    GPIOA->MODER &= ~(0x3 << (10 * 2)); // Сбрасываем биты MODER10
    GPIOA->MODER |=  (0x1 << (10 * 2)); // Устанавливаем режим Output

    // Настраиваем тип выхода - push-pull (OTYPER10 = 0)
    GPIOA->OTYPER &= ~(1 << 10);

    // Настраиваем скорость вывода как высокую (OSPEEDR10 = 10)
    GPIOA->OSPEEDR &= ~(0x3 << (10 * 2));
    GPIOA->OSPEEDR |= (0x2 << (10 * 2));

    // Без подтягивающего резистора (PUPDR10 = 00)
    GPIOA->PUPDR &= ~(0x3 << (10 * 2));

    /////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////

    // A11

    // Настраиваем PA11 как выход (MODER11[1:0] = 01)
    GPIOA->MODER &= ~(0x3 << (11 * 2)); // Сбрасываем биты MODER3
    GPIOA->MODER |=  (0x1 << (11 * 2)); // Устанавливаем режим Output

    // Настраиваем тип выхода - push-pull (OTYPER11 = 0)
    GPIOA->OTYPER &= ~(1 << 11);

    // Настраиваем скорость вывода как высокую (OSPEEDR11 = 10)
    GPIOA->OSPEEDR &= ~(0x3 << (11 * 2));
    GPIOA->OSPEEDR |= (0x2 << (11 * 2));

    // Без подтягивающего резистора (PUPDR11 = 00)
    GPIOA->PUPDR &= ~(0x3 << (11 * 2));

    /////////////////////////////////////////////////////////////////////
}

void GPIO_Init_with_my_macro(void)
{
    /////////////////////////////////////////////////////////////////////
    
    RCC_GPIO |= RCC_GPIOA_ON | RCC_GPIOB_ON; // включение тактирования портов GPIOA и GPIOB

    /////////////////////////////////////////////////////////////////////

    // Настройка всех кнопок

    GPIOB_MODER = (GPIOB_MODER & ~(0x3UL << (1 * 2)));
    GPIOB_MODER = (GPIOB_MODER & ~(0x3UL << (2 * 2)));
    GPIOB_MODER = (GPIOB_MODER & ~(0x3UL << (3 * 2)));
    GPIOB_MODER = (GPIOB_MODER & ~(0x3UL << (8 * 2)));
    GPIOB_MODER |= GPIOB_MODE_PIN1_IN | GPIOB_MODE_PIN2_IN | GPIOB_MODE_PIN3_IN | GPIOB_MODE_PIN8_IN; // изначально режим входа на пинах
    GPIOB_PUPDR = (GPIOB_PUPDR & ~(0x3UL << (1 * 2)));
    GPIOB_PUPDR = (GPIOB_PUPDR & ~(0x3UL << (2 * 2)));
    GPIOB_PUPDR = (GPIOB_PUPDR & ~(0x3UL << (3 * 2)));
    GPIOB_PUPDR = (GPIOB_PUPDR & ~(0x3UL << (8 * 2)));
    GPIOB_PUPDR |= GPIOB_PUPD_PIN1_PULL_UP | GPIOB_PUPD_PIN2_PULL_UP | GPIOB_PUPD_PIN3_PULL_UP | GPIOB_PUPD_PIN8_PULL_UP;

    /////////////////////////////////////////////////////////////////////

    // Настройка пользовательского светодиода

    GPIOA_MODER |= GPIOA_MODE_PIN5_OUT;

    // Настройка портов для внешних светодиодов

    GPIOA_MODER |= GPIOA_MODE_PIN10_OUT | GPIOA_MODE_PIN11_OUT;
    GPIOA_OTYPER |= GPIOA_OTYPE_PIN10_PP | GPIOA_OTYPE_PIN11_PP;
    GPIOA_OSPEEDR |= GPIOA_OSPEED_PIN10_HS | GPIOA_OSPEED_PIN11_HS;
    GPIOA_PUPDR |= GPIOA_PUPD_PIN10_NOPUPD | GPIOA_PUPD_PIN11_NOPUPD;

    /////////////////////////////////////////////////////////////////////
}

void delay(volatile uint32_t count)
{
    for (; count > 0; count--)
    {
        // пустая итерация
    }
}

void PB1_IN(void) // настройка на вход
{
    GPIOB_MODER = (GPIOB_MODER & ~(0x3UL << (1 * 2)));
    GPIOB_OTYPER = (GPIOB_OTYPER & ~(0x3UL << (1 * 2)));
    GPIOB_OSPEEDR = (GPIOB_OSPEEDR & ~(0x3UL << (1 * 2)));
    GPIOB_PUPDR = (GPIOB_PUPDR & ~(0x3UL << (1 * 2)));
    GPIOB_MODER |= GPIOB_MODE_PIN1_IN;
    GPIOB_PUPDR |= GPIOB_PUPD_PIN1_PULL_UP;
}

void PB2_IN(void) // настройка на вход
{
    GPIOB_MODER = (GPIOB_MODER & ~(0x3UL << (2 * 2)));
    GPIOB_OTYPER = (GPIOB_OTYPER & ~(0x3UL << (2 * 2)));
    GPIOB_OSPEEDR = (GPIOB_OSPEEDR & ~(0x3UL << (2 * 2)));
    GPIOB_PUPDR = (GPIOB_PUPDR & ~(0x3UL << (2 * 2)));
    GPIOB_MODER |= GPIOB_MODE_PIN2_IN;
    GPIOB_PUPDR |= GPIOB_PUPD_PIN2_PULL_UP;
}

void PB3_IN(void) // настройка на вход
{
    GPIOB_MODER = (GPIOB_MODER & ~(0x3UL << (3 * 2)));
    GPIOB_OTYPER = (GPIOB_OTYPER & ~(0x3UL << (3 * 2)));
    GPIOB_OSPEEDR = (GPIOB_OSPEEDR & ~(0x3UL << (3 * 2)));
    GPIOB_PUPDR = (GPIOB_PUPDR & ~(0x3UL << (3 * 2)));
    GPIOB_MODER |= GPIOB_MODE_PIN3_IN;
    GPIOB_PUPDR |= GPIOB_PUPD_PIN3_PULL_UP;
}

/////////////////////////////////////////////////////////////////////

void PB1_OUT(void) // настройка на выход
{
    GPIOB_MODER = (GPIOB_MODER & ~(0x3UL << (1 * 2)));
    GPIOB_OTYPER = (GPIOB_OTYPER & ~(0x3UL << (1 * 2)));
    GPIOB_OSPEEDR = (GPIOB_OSPEEDR & ~(0x3UL << (1 * 2)));
    GPIOB_PUPDR =(GPIOB_PUPDR & ~(0x3UL << (1 * 2)));

    GPIOB_MODER |= GPIOB_MODE_PIN1_OUT;
    GPIOB->OTYPER &= ~(1 << 1);
    GPIOB->OSPEEDR |= (0x2 << (1 * 2));
}

void PB2_OUT(void) // настройка на выход
{
    GPIOB_MODER = (GPIOB_MODER & ~(0x3UL << (2 * 2)));
    GPIOB_OTYPER = (GPIOB_OTYPER & ~(0x3UL << (2 * 2)));
    GPIOB_OSPEEDR = (GPIOB_OSPEEDR & ~(0x3UL << (2 * 2)));
    GPIOB_PUPDR =(GPIOB_PUPDR & ~(0x3UL << (2 * 2)));

    GPIOB_MODER |= GPIOB_MODE_PIN2_OUT;
    GPIOB->OTYPER &= ~(1 << 2);
    GPIOB->OSPEEDR |= (0x2 << (2 * 2));
}

void PB3_OUT(void) // настройка на выход
{
    GPIOB_MODER = (GPIOB_MODER & ~(0x3UL << (3 * 2)));
    GPIOB_OTYPER = (GPIOB_OTYPER & ~(0x3UL << (3 * 2)));
    GPIOB_OSPEEDR = (GPIOB_OSPEEDR & ~(0x3UL << (3 * 2)));
    GPIOB_PUPDR =(GPIOB_PUPDR & ~(0x3UL << (3 * 2)));

    GPIOB_MODER |= GPIOB_MODE_PIN3_OUT;
    GPIOB->OTYPER &= ~(1 << 3);
    GPIOB->OSPEEDR |= (0x2 << (3 * 2));
}

void ITR_Init(void)
{
    // Благодаря этому при нажатии и отпускании кнопки подключённой к пину PB1 будет вызываться функция обработчика прерывания
    // и будет происходить то что в ней написано
    
    SET_BIT(RCC->APB2ENR,RCC_APB2ENR_SYSCFGEN); // включение тактирования периферии SYSCFG
    MODIFY_REG(SYSCFG->EXTICR[0], SYSCFG_EXTICR1_EXTI1_Msk, SYSCFG_EXTICR1_EXTI1_PB); // настраиваем на работу с линией PB1
    SET_BIT(EXTI->IMR, EXTI_IMR_MR1); // настройка маскирования 1 линии
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR1); // включаем генерацию прерываний по нарастающему фронту сигнала на линии EXTI1. 
    // прерывание будет срабатывать при переходе сигнала с низкого уровня на высокий
    SET_BIT(EXTI->FTSR, EXTI_FTSR_TR1); // включаем генерацию прерываний по спадающему фронту сигнала на линии EXTI1
    // прерывание будет срабатывать при переходе сигнала с высокого уровня на низкий
    NVIC_SetPriority(EXTI1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0)); // задаём приоритет
    NVIC_EnableIRQ(EXTI1_IRQn); // разрешаем прерывания

}



/* 
// A11

    // Настраиваем PA11 как выход (MODER11[1:0] = 01)
    GPIOA->MODER &= ~(0x3 << (11 * 2)); // Сбрасываем биты MODER3
    GPIOA->MODER |=  (0x1 << (11 * 2)); // Устанавливаем режим Output

    // Настраиваем тип выхода - push-pull (OTYPER11 = 0)
    GPIOA->OTYPER &= ~(1 << 11);

    // Настраиваем скорость вывода как высокую (OSPEEDR11 = 10)
    GPIOA->OSPEEDR &= ~(0x3 << (11 * 2));
    GPIOA->OSPEEDR |= (0x2 << (11 * 2));

    // Без подтягивающего резистора (PUPDR11 = 00)
    GPIOA->PUPDR &= ~(0x3 << (11 * 2));

*/