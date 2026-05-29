#include "gpio.h"
#include <ch32v00x.h>
#include <stddef.h>

void gpio_init(GPIO_Port_TypeDef port, uint8_t pin, GPIO_Mode_TypeDef mode)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_TypeDef *port_type = NULL;

    if (port == PORT_D)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
        port_type = GPIOD;
    }
    else if (port == PORT_C)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        port_type = GPIOC;
    }
    else if (port == PORT_A)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        port_type = GPIOA;
    }
    else
    {
        return;
    }

    GPIO_InitStructure.GPIO_Pin = (1 << pin);

    switch (mode)
    {
    case GPIO_MODE_INPUT_FLOATING:
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        break;
    case GPIO_MODE_INPUT_PULLUP:
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        break;
    case GPIO_MODE_INPUT_PULLDOWN:
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
        break;
    case GPIO_MODE_OUTPUT_PP:
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        break;
    case GPIO_MODE_OUTPUT_OD:
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
        break;
    }
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(port_type, &GPIO_InitStructure);
}

void gpio_set(GPIO_Port_TypeDef port, uint8_t pin)
{
    if (port == PORT_D)
        GPIOD->BSHR = (1 << pin);
    else if (port == PORT_C)
        GPIOC->BSHR = (1 << pin);
    else if (port == PORT_A)
        GPIOA->BSHR = (1 << pin);
}

void gpio_clear(GPIO_Port_TypeDef port, uint8_t pin)
{
    if (port == PORT_D)
        GPIOD->BCR = (1 << pin);
    else if (port == PORT_C)
        GPIOC->BCR = (1 << pin);
    else if (port == PORT_A)
        GPIOA->BCR = (1 << pin);
}

void gpio_toggle(GPIO_Port_TypeDef port, uint8_t pin)
{
    if (port == PORT_D)
        GPIOD->OUTDR ^= (1 << pin);
    else if (port == PORT_C)
        GPIOC->OUTDR ^= (1 << pin);
    else if (port == PORT_A)
        GPIOA->OUTDR ^= (1 << pin);
}

uint8_t gpio_read(GPIO_Port_TypeDef port, uint8_t pin)
{
    if (port == PORT_D)
        return (GPIOD->INDR & (1 << pin)) ? 1 : 0;
    if (port == PORT_C)
        return (GPIOC->INDR & (1 << pin)) ? 1 : 0;
    if (port == PORT_A)
        return (GPIOA->INDR & (1 << pin)) ? 1 : 0;
    return 0;
}
