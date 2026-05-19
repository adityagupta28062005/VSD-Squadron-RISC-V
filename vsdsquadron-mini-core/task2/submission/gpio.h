#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define GPIO_PIN_0 0
#define GPIO_PIN_1 1
#define GPIO_PIN_2 2
#define GPIO_PIN_3 3
#define GPIO_PIN_4 4
#define GPIO_PIN_5 5
#define GPIO_PIN_6 6
#define GPIO_PIN_7 7

// Pin mode configurations
#define GPIO_MODE_INPUT 0
#define GPIO_MODE_OUTPUT 1

// GPIO API Functions

void gpio_init(char port, uint8_t pin, uint8_t mode);

// Set the pin HIGH
void gpio_set(char port, uint8_t pin);

// Set the pin LOW
void gpio_clear(char port, uint8_t pin);

// Toggle the pin state
void gpio_toggle(char port, uint8_t pin);

#endif