#include "debug.h"
#include "gpio.h"
#include <stdio.h>

// Define the physical pin we are testing.
#define TEST_PORT 'D'
#define TEST_PIN GPIO_PIN_6

void delay(volatile uint32_t count)
{
    while (count--)
    {
        __asm__ volatile("nop");
    }
}

int main(void)
{
    Delay_Init();
    USART_Printf_Init(115200);

    printf("Board: VSDSquadron Mini\n");
    printf("Firmware Version: 1.0.0\n");

    gpio_init(TEST_PORT, TEST_PIN, GPIO_MODE_OUTPUT);

    int counter = 0;

    while (1)
    {
        gpio_toggle(TEST_PORT, TEST_PIN);

        printf("Running count: %d\n", counter++);

        Delay_Ms(1000);
    }
}