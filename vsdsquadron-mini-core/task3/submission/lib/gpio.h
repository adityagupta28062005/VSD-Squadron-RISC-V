#ifndef ADVANCED_GPIO_H
#define ADVANCED_GPIO_H

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

/**
 * @brief Initialize a GPIO pin with a specific mode.
 * @param port The GPIO port (PORT_A, PORT_C, PORT_D).
 * @param pin The pin number (PIN_0 to PIN_7).
 * @param mode The mode to configure the pin.
 */
void gpio_init(GPIO_Port_TypeDef port, uint8_t pin, GPIO_Mode_TypeDef mode);

/**
 * @brief Set a GPIO output pin HIGH.
 * @param port The GPIO port.
 * @param pin The pin number.
 */
void gpio_set(GPIO_Port_TypeDef port, uint8_t pin);

/**
 * @brief Clear a GPIO output pin to LOW.
 * @param port The GPIO port.
 * @param pin The pin number.
 */
void gpio_clear(GPIO_Port_TypeDef port, uint8_t pin);

/**
 * @brief Toggle a GPIO output pin's state.
 * @param port The GPIO port.
 * @param pin The pin number.
 */
void gpio_toggle(GPIO_Port_TypeDef port, uint8_t pin);

/**
 * @brief Read the current state of a GPIO input pin.
 * @param port The GPIO port.
 * @param pin The pin number.
 * @return 1 if HIGH, 0 if LOW.
 */
uint8_t gpio_read(GPIO_Port_TypeDef port, uint8_t pin);

/**
 * @brief Debounce a GPIO button input.
 * @param port The GPIO port.
 * @param pin The pin number.
 * @param active_state The state when the button is pressed (0 for pull-up, 1 for pull-down).
 * @return true if uniquely pressed (debounced), false otherwise.
 */
bool gpio_debounce(GPIO_Port_TypeDef port, uint8_t pin, uint8_t active_state);

#endif // ADVANCED_GPIO_H
