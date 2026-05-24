# Task 3: Advanced GPIO Library & Application Demo

## Overview

This task demonstrates the creation of a reusable, modular peripheral driver library for GPIO manipulation on the VSDSquadron Mini RISC-V board (CH32V003). All hardware/register-level operations are strictly encapsulated within the library.

## Implemented Library

**Library Name**: `Advanced GPIO Library` (`gpio.h` / `gpio.c`)

### API Reference

| API Function | Description |

|---|---|
| `void gpio_init(GPIO_Port_TypeDef port, uint8_t pin, GPIO_Mode_TypeDef mode)` | Initializes a specific GPIO pin (input/output/pullup/open-drain). Clocks are automatically enabled. |
| `void gpio_set(GPIO_Port_TypeDef port, uint8_t pin)` | Sets an output pin to a HIGH state. |
| `void gpio_clear(GPIO_Port_TypeDef port, uint8_t pin)` | Clears an output pin to a LOW state. |
| `void gpio_toggle(GPIO_Port_TypeDef port, uint8_t pin)` | Toggles the state of an output pin (e.g. for blinking). |
| `uint8_t gpio_read(GPIO_Port_TypeDef port, uint8_t pin)` | Reads and returns the digital state (0 or 1) of an input pin. |
| `bool gpio_debounce(GPIO_Port_TypeDef port, uint8_t pin, uint8_t active_state)` | Validates a button press while filtering out mechanical noise (debouncing). |

## Demo Application Description (Wire-Free Mode)

Because no external jumper wires or buttons are available, the application (`app/main.c`) demonstrates the library functionality solely using the onboard components and internal CH32V003 features.

- **Input (Read) Test**: The app configures pin **PC4** first with an internal pull-up and reads it (checking for HIGH). Then it configures the same pin with an internal pull-down and reads it (checking for LOW), printing the results to UART. This proves `gpio_read()` works without hardware wires.
- **Output (Pattern) Test**: The app blinks the Onboard LED (**PD6**) continuously in a complex observable sequence specifically designed to use every library function:
  - **Phase 1 (Rapid Strobe)**: Uses the `gpio_toggle()` API in a tight loop to produce a rapid flashing effect.
  - **Phase 2 (S-O-S Signal)**: Uses explicit `gpio_set()` and `gpio_clear()` API calls to broadcast an accurate Morse Code "S-O-S" distress signal (3 short, 3 long, 3 short).
  - This provides a highly distinct and observable LED pattern that perfectly validates the implementation over a basic blink.

## Board Setup & Pinout

- **VSDSquadron Mini (CH32V003)**
- **LED**: Onboard LED is connected directly to `PD6`. (Note: this overrides UART RX functionality, taking Tx only for Serial Output).
- **Test Pin**: `PC4` (Internal test, leave it unconnected).
- **UART TX**: `PD5` (Connect to your serial monitor's RX).

## Firmware Configuration & Execution

### 1. Build and Flash

Use your preferred environment (VSCode + PlatformIO with CH32V extension) to build the program.
Ensure you have the CH32V board definition properly included.
Run `pio run -t upload` or use the IDE button to build and push to the board.

### 2. UART Configuration

- **Baud Rate**: `115200`
- **Data Bits**: 8
- **Stop Bits**: 1
- **Parity**: None
Use PuTTY, screen, or the PlatformIO Serial Monitor to view the output.
