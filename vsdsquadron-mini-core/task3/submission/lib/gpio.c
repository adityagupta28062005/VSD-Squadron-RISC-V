#include "gpio.h"
#include "ch32v00x.h"
#include "debug.h"

void gpio_init(GPIO_Port_TypeDef port, uint8_t pin, GPIO_Mode_TypeDef mode)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_TypeDef *port_type = NULL;

    // Enable Clock and Map Port
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
        return; // Invalid port
    }

    // Assign Pin
    GPIO_InitStructure.GPIO_Pin = (1 << pin);

    // Map Mode
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

    // Set high speed for outputs
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    // Apply configuration
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
    uint8_t state = 0;
    if (port == PORT_D)
        state = (GPIOD->INDR & (1 << pin)) ? 1 : 0;
    else if (port == PORT_C)
        state = (GPIOC->INDR & (1 << pin)) ? 1 : 0;
    else if (port == PORT_A)
        state = (GPIOA->INDR & (1 << pin)) ? 1 : 0;
    return state;
}

bool gpio_debounce(GPIO_Port_TypeDef port, uint8_t pin, uint8_t active_state)
{
    static uint32_t last_time = 0;
    static uint8_t last_state = 2; // Initial invalid state

    // We assume Delay_Ms and system time might not be strictly available as millis(),
    // replacing with a blocking debounce approach for simple microcontroller usage.

    uint8_t current_state = gpio_read(port, pin);

    if (current_state == active_state)
    {
        Delay_Ms(50); // Block for 50ms to debounce
        if (gpio_read(port, pin) == active_state)
        {
            if (last_state != active_state)
            {
                last_state = active_state;
                return true; // Valid press
            }
        }
    }
    else
    {
        last_state = !active_state; // Reset state when released
    }

    return false;
}