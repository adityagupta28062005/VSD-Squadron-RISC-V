# API Reference

This document provides the API specifications for the hardware abstraction layer (HAL) drivers used in the LED Pattern Sequencer.

---

## 1. GPIO Driver (`gpio.h`)

The GPIO driver handles single-pin hardware configurations, allowing dynamic mode switching during runtime.

### `gpio_init`
```c
/**
 * @brief Initializes a specific GPIO pin with a designated mode.
 * @param port The GPIO port identifier (e.g., `PORT_A`, `PORT_C`, `PORT_D`).
 * @param pin The pin number (0-7).
 * @param mode The hardware mode (e.g., `GPIO_MODE_OUTPUT_PP`, `GPIO_MODE_INPUT_FLOATING`).
 * @return None
 */
void gpio_init(GPIO_Port_TypeDef port, uint8_t pin, GPIO_Mode_TypeDef mode);
```
**Notes/Constraints:** Calling this on an active peripheral pin (like UART RX/TX) will reconfigure the pin and may detach it from the peripheral hardware mapping.
**Example:** `gpio_init(PORT_D, PIN_6, GPIO_MODE_OUTPUT_PP);`

### `gpio_set`
```c
/**
 * @brief Drives an output pin HIGH (logic 1).
 * @param port The GPIO port identifier.
 * @param pin The pin number.
 * @return None
 */
void gpio_set(GPIO_Port_TypeDef port, uint8_t pin);
```

### `gpio_clear`
```c
/**
 * @brief Drives an output pin LOW (logic 0).
 * @param port The GPIO port identifier.
 * @param pin The pin number.
 * @return None
 */
void gpio_clear(GPIO_Port_TypeDef port, uint8_t pin);
```

---

## 2. UART Driver (`uart.h`)

The UART driver provides non-blocking data reception and blocking transmission specifically tailored for interactive terminal usage.

### `uart_init`
```c
/**
 * @brief Initializes USART1 for standard serial communication.
 * @param baudrate The desired baud rate (e.g., 115200).
 * @return None
 */
void uart_init(uint32_t baudrate);
```
**Notes/Constraints:** This maps USART1 to `PD5` (TX) and `PD6` (RX) by default.

### `uart_data_available`
```c
/**
 * @brief Checks if unread data is present in the UART receive register.
 * @return true if data is available, false otherwise.
 */
bool uart_data_available(void);
```
**Example:**
```c
if (uart_data_available()) {
    char c = uart_read_char();
}
```

### `uart_read_char`
```c
/**
 * @brief Reads a single character from the UART receive register.
 * @return The received 8-bit character.
 */
char uart_read_char(void);
```
**Notes/Constraints:** Should only be called if `uart_data_available()` returns true.

### `uart_write_string`
```c
/**
 * @brief Transmits a null-terminated string over UART.
 * @param str Pointer to the string to transmit.
 * @return None
 */
void uart_write_string(const char *str);
```

---

## 3. Timer Driver (`timer.h`)

Provides accurate hardware-level milliseconds ticking utilizing the core SysTick timer.

### `timer_init`
```c
/**
 * @brief Initializes the SysTick peripheral to generate 1ms interrupts.
 * @return None
 */
void timer_init(void);
```

### `timer_delay_ms`
```c
/**
 * @brief Blocks program execution for a specified number of milliseconds.
 * @param ms Delay time in milliseconds.
 * @return None
 */
void timer_delay_ms(uint32_t ms);
```
**Example:** `timer_delay_ms(150); // wait 150ms`

### `timer_get_ticks`
```c
/**
 * @brief Retrieves the total system uptime.
 * @return Total milliseconds elapsed since `timer_init()` was called.
 */
uint32_t timer_get_ticks(void);
```