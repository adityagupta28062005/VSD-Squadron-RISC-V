// Task 4: LED Pattern Sequencer - Main Application
#include <ch32v00x.h>
#include <string.h>
#include <stdlib.h>
#include "gpio.h"
#include "uart.h"
#include "timer.h"

// --- Configuration & Constants ---
#define LED_PORT PORT_D
#define LED_PIN PIN_6 // Onboard LED
#define MAX_PATTERN_LEN 32
#define MAX_UART_CMD_LEN 32

// --- Sequencer State Machine ---
typedef enum
{
    STATE_STOPPED,
    STATE_PLAYING
} SequencerState;

// --- Global Variables ---
char pattern_buffer[MAX_PATTERN_LEN + 1] = "101010"; // Default pattern
uint8_t pattern_length = 6;
uint32_t step_delay_ms = 500; // Default speed: 500ms

char uart_rx_buffer[MAX_UART_CMD_LEN];
uint8_t uart_rx_index = 0;

SequencerState current_state = STATE_STOPPED;
uint8_t current_pattern_index = 0;
uint32_t last_step_time = 0;
uint8_t playback_cycles = 0; // To track how many times the pattern played

// --- Function Prototypes ---
void process_command(char *cmd);
void hardware_init(void);
void print_banner(void);

// --- Print Banner ---
void print_banner(void)
{
    uart_write_string("\r\n=================================\r\n");
    uart_write_string("  LED Sequencer (Onboard Mode)   \r\n");
    uart_write_string("=================================\r\n");
    uart_write_string(" Commands available:\r\n");
    uart_write_string("   pattern <str>  - Set an LED pattern (e.g. pattern 10110)\r\n");
    uart_write_string("   delay <ms>     - Set speed in ms (e.g. delay 250)\r\n");
    uart_write_string("   play           - Start blinking current pattern\r\n");
    uart_write_string("   exit           - Exit the application\r\n");
    uart_write_string("   help           - Show this menu again\r\n");
    uart_write_string("---------------------------------\r\n");
    uart_write_string(" Current Setup: Pattern = '");
    uart_write_string(pattern_buffer);
    uart_write_string("', Delay = ");

    // Quick uint_to_string
    char str[16];
    uint32_t temp = step_delay_ms;
    int i = 0;
    if (temp == 0)
        str[i++] = '0';
    while (temp > 0)
    {
        str[i++] = (temp % 10) + '0';
        temp /= 10;
    }
    str[i] = '\0';
    for (int j = 0; j < i / 2; j++)
    {
        char t = str[j];
        str[j] = str[i - 1 - j];
        str[i - 1 - j] = t;
    }
    uart_write_string(str);
    uart_write_string("ms\r\n");
    uart_write_string("=================================\r\n");
}

// --- Initialization ---
void hardware_init(void)
{
    SystemCoreClockUpdate();
    timer_init();
    uart_init(115200); // PD6 is RX by default
}

// --- UART Command Parser ---
void process_command(char *cmd)
{
    char *token = strtok(cmd, " ");
    if (token == NULL)
        return;

    if (strcmp(token, "play") == 0)
    {
        if (pattern_length == 0)
        {
            uart_write_string("Error: Pattern is empty.\r\n");
            return;
        }
        current_state = STATE_PLAYING;
        current_pattern_index = 0;
        playback_cycles = 0;
        last_step_time = timer_get_ticks();

        uart_write_string("Playing pattern 3 times! (Keyboard locked during playback...)\r\n");

        // Wait for UART TX buffer to finish emptying before we mess with the shared pin!
        timer_delay_ms(50);

        // Use AFIO to clear the remap so that PD6 becomes UART RX/TX again when we restore it.
        // During play, we simply configure PD6 as an output.
        // We don't disable USART entirely, to avoid messing up the internal RCC state if possible.
        // Instead, we just take over the GPIO pin.
        gpio_init(LED_PORT, LED_PIN, GPIO_MODE_OUTPUT_PP);
    }
    else if (strcmp(token, "delay") == 0)
    {
        token = strtok(NULL, " ");
        if (token != NULL)
        {
            uint32_t ms = atoi(token);
            if (ms > 0)
            {
                step_delay_ms = ms;
                uart_write_string("Delay updated.\r\n");
            }
        }
    }
    else if (strcmp(token, "pattern") == 0)
    {
        token = strtok(NULL, " ");
        if (token != NULL)
        {
            uint8_t len = strlen(token);
            if (len <= MAX_PATTERN_LEN)
            {
                // Validate that pattern contains only '1' and '0'
                uint8_t i;
                for (i = 0; i < len; i++)
                {
                    if (token[i] != '0' && token[i] != '1')
                    {
                        uart_write_string("Error: Pattern must contain only '1' or '0'.\r\n");
                        return;
                    }
                }

                strcpy(pattern_buffer, token);
                pattern_length = len;
                uart_write_string("Pattern updated.\r\n");
            }
            else
            {
                uart_write_string("Error: Pattern exceeds max length of 32.\r\n");
            }
        }
        else
        {
            uart_write_string("Error: Missing pattern argument.\r\n");
        }
    }
    else if (strcmp(token, "help") == 0)
    {
        print_banner();
    }
    else if (strcmp(token, "exit") == 0)
    {
        uart_write_string("\r\nExiting Sequencer... Goodbye!\r\n");
        while (1)
            ; // Halt execution
    }
    else
    {
        uart_write_string("Unknown command. Type 'help'.\r\n");
    }
}

int main(void)
{
    hardware_init();

    print_banner();
    uart_write_string("> ");

    while (1)
    {
        // --- 1. UART Mode (Stopped) ---
        if (current_state == STATE_STOPPED)
        {
            if (uart_data_available())
            {
                char c = uart_read_char();
                if (c == '\b' || c == 0x7F)
                {
                    if (uart_rx_index > 0)
                    {
                        uart_rx_index--;
                        uart_write_string("\b \b");
                    }
                }
                else if (c == '\r' || c == '\n')
                {
                    uart_write_string("\r\n");
                    if (uart_rx_index > 0)
                    {
                        uart_rx_buffer[uart_rx_index] = '\0';
                        process_command(uart_rx_buffer);
                        uart_rx_index = 0;
                    }
                    if (current_state == STATE_STOPPED)
                        uart_write_string("> ");
                }
                else if (uart_rx_index < (MAX_UART_CMD_LEN - 1))
                {
                    uart_rx_buffer[uart_rx_index++] = c;
                    uart_write_char(c);
                }
            }
        }
        // --- 2. LED Playback Mode ---
        else if (current_state == STATE_PLAYING)
        {
            // Since PD6 is shared between UART RX and LED, we CANNOT receive UART commands
            // while playing. Thus, a blocking playback loop is perfectly fine and avoids
            // complexities with the SysTick timer configuration.
            for (uint8_t cycle = 0; cycle < 3; cycle++)
            {
                for (uint8_t bit_idx = 0; bit_idx < pattern_length; bit_idx++)
                {
                    char current_bit = pattern_buffer[bit_idx];
                    if (current_bit == '1')
                        gpio_set(LED_PORT, LED_PIN);
                    else
                        gpio_clear(LED_PORT, LED_PIN);

                    timer_delay_ms(step_delay_ms);
                }
            }

            // Stop after playing the pattern 3 full times
            current_state = STATE_STOPPED;

            // Reconfigure PD6 back to UART RX!
            // We must NOT call gpio_clear because that touches the BSHR registers and can break AFIO mapping.
            gpio_init(LED_PORT, LED_PIN, GPIO_MODE_INPUT_FLOATING);

            // Small delay to let UART hardware settle
            timer_delay_ms(10);

            // Flush any garbage that might have been received on the pin while we were toggling it
            while (uart_data_available())
            {
                uart_read_char();
            }
            uart_rx_index = 0; // Clear the current command buffer

            uart_write_string("\r\nPlayback finished. Keyboard unlocked.\r\n");
            print_banner();
            uart_write_string("> ");
        }
    }
}
