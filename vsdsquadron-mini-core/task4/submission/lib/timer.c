#include "timer.h"
#include <ch32v00x.h>
#include <debug.h>

void timer_init(void)
{
    Delay_Init();
}

uint32_t timer_get_ticks(void)
{
    return (uint32_t)(SysTick->CNT / (SystemCoreClock / 8000));
}

void timer_delay_ms(uint32_t ms)
{
    Delay_Ms(ms);
}
