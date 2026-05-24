#include "ch32v00x.h"
#include "debug.h"
#include "gpio.h"

// Define Pins
// PD6 is the Onboard LED (as per context)
// PC4 will be used as a test internal pin since no jumper wires are available
#define LED_PORT PORT_D
#define LED_PIN PIN_6

#define TEST_PORT PORT_C
#define TEST_PIN PIN_4

int main(void)
{
    // Initialize system core and standard delays
    Delay_Init();

    // Initialize UART at 115200 baud for logging (TX on PD5)
    USART_Printf_Init(115200);
    printf("System Initialized.\n");
    printf("Starting Advanced GPIO Demo (Wire-Free Mode)...\n");

    // ---------------------------------------------------------
    // PART 1: Proving GPIO Read API works (No wires needed!)
    // ---------------------------------------------------------
    printf("\n--- Testing GPIO Input (Read) API ---\n");

    // We can configure a floating pin with an internal Pull-Up and read it (should be 1/HIGH)
    gpio_init(TEST_PORT, TEST_PIN, GPIO_MODE_INPUT_PULLUP);
    Delay_Ms(10); // Let voltage settle
    uint8_t state = gpio_read(TEST_PORT, TEST_PIN);
    printf("PC4 Configured as PULL-UP. Read State: %s (Expected: HIGH)\n", state ? "HIGH" : "LOW");

    // Next, we configure the same pin with an internal Pull-Down and read it (should be 0/LOW)
    gpio_init(TEST_PORT, TEST_PIN, GPIO_MODE_INPUT_PULLDOWN);
    Delay_Ms(10); // Let voltage settle
    state = gpio_read(TEST_PORT, TEST_PIN);
    printf("PC4 Configured as PULL-DOWN. Read State: %s (Expected: LOW)\n", state ? "HIGH" : "LOW");

    // ---------------------------------------------------------
    // PART 2: Proving Output APIs (Complex LED Pattern)
    // ---------------------------------------------------------
    printf("\n--- Testing GPIO Output APIs (LED Pattern) ---\n");

    // Initialize the LED output using the custom library API
    gpio_init(LED_PORT, LED_PIN, GPIO_MODE_OUTPUT_PP);

    uint32_t cycle_count = 1;

    while (1)
    {
        printf("\n=== [Execution Cycle %lu] Complex LED Pattern Demo ===\n", cycle_count++);

        // Phase 1: Rapid Strobe (Tests Toggle API)
        printf("-> Phase 1: Rapid Strobe (Testing gpio_toggle)\n");
        for (int i = 0; i < 6; i++)
        { // 6 toggles = 3 fast blinks
            gpio_toggle(LED_PORT, LED_PIN);
            Delay_Ms(100);
        }
        gpio_clear(LED_PORT, LED_PIN); // Ensure off state
        Delay_Ms(500);

        // Phase 2: S-O-S Signal (Tests Set/Clear APIs)
        printf("-> Phase 2: S-O-S Signal (Testing gpio_set & gpio_clear)\n");

        // 'S' (3 short blinks)
        printf("   Sending 'S' (...)\n");
        for (int i = 0; i < 3; i++)
        {
            gpio_set(LED_PORT, LED_PIN);
            Delay_Ms(150);
            gpio_clear(LED_PORT, LED_PIN);
            Delay_Ms(150);
        }
        Delay_Ms(300);

        // 'O' (3 long blinks)
        printf("   Sending 'O' (---)\n");
        for (int i = 0; i < 3; i++)
        {
            gpio_set(LED_PORT, LED_PIN);
            Delay_Ms(600);
            gpio_clear(LED_PORT, LED_PIN);
            Delay_Ms(150);
        }
        Delay_Ms(300);

        // 'S' (3 short blinks)
        printf("   Sending 'S' (...)\n");
        for (int i = 0; i < 3; i++)
        {
            gpio_set(LED_PORT, LED_PIN);
            Delay_Ms(150);
            gpio_clear(LED_PORT, LED_PIN);
            Delay_Ms(150);
        }

        printf("-> Cycle complete. Waiting before repeat...\n");
        Delay_Ms(2000);
    }
}