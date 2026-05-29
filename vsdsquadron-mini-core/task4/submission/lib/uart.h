#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>

void uart_init(uint32_t baudrate);
void uart_write_char(char c);
void uart_write_string(const char *str);
bool uart_data_available(void);
char uart_read_char(void);

#endif // UART_H
