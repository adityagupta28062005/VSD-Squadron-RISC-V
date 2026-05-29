#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>

// GPIO Mode Definitions
typedef enum
{
    GPIO_MODE_INPUT_FLOATING,
    GPIO_MODE_INPUT_PULLUP,
    GPIO_MODE_INPUT_PULLDOWN,
    GPIO_MODE_OUTPUT_PP, // Push-Pull
    GPIO_MODE_OUTPUT_OD  // Open-Drain
} GPIO_Mode_TypeDef;

// Port Identifiers
typedef enum
{
    PORT_A = 'A',
    PORT_C = 'C',
    PORT_D = 'D'
} GPIO_Port_TypeDef;

// Pin Definitions
#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7

void gpio_init(GPIO_Port_TypeDef port, uint8_t pin, GPIO_Mode_TypeDef mode);
void gpio_set(GPIO_Port_TypeDef port, uint8_t pin);
void gpio_clear(GPIO_Port_TypeDef port, uint8_t pin);
void gpio_toggle(GPIO_Port_TypeDef port, uint8_t pin);
uint8_t gpio_read(GPIO_Port_TypeDef port, uint8_t pin);

#endif // GPIO_H
