#include "gpio.h"
#include "ch32v00x.h"

void gpio_init(char port, uint8_t pin, uint8_t mode)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    if (port == 'D')
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
        GPIO_InitStructure.GPIO_Pin = (1 << pin);
        GPIO_InitStructure.GPIO_Mode = (mode == GPIO_MODE_OUTPUT) ? GPIO_Mode_Out_PP : GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
    }
    else if (port == 'C')
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        GPIO_InitStructure.GPIO_Pin = (1 << pin);
        GPIO_InitStructure.GPIO_Mode = (mode == GPIO_MODE_OUTPUT) ? GPIO_Mode_Out_PP : GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
    else if (port == 'A')
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        GPIO_InitStructure.GPIO_Pin = (1 << pin);
        GPIO_InitStructure.GPIO_Mode = (mode == GPIO_MODE_OUTPUT) ? GPIO_Mode_Out_PP : GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
}

void gpio_set(char port, uint8_t pin)
{
    if (port == 'D')
        GPIOD->BSHR = (1 << pin);
    if (port == 'C')
        GPIOC->BSHR = (1 << pin);
    if (port == 'A')
        GPIOA->BSHR = (1 << pin);
}

void gpio_clear(char port, uint8_t pin)
{
    if (port == 'D')
        GPIOD->BCR = (1 << pin);
    if (port == 'C')
        GPIOC->BCR = (1 << pin);
    if (port == 'A')
        GPIOA->BCR = (1 << pin);
}

void gpio_toggle(char port, uint8_t pin)
{
    if (port == 'D')
        GPIOD->OUTDR ^= (1 << pin);
    if (port == 'C')
        GPIOC->OUTDR ^= (1 << pin);
    if (port == 'A')
        GPIOA->OUTDR ^= (1 << pin);
}