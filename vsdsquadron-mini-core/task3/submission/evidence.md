# Task 3 Evidence: Advanced GPIO Library

## 1. Application Hardware Execution

### What was verified on hardware
- **Input (Read) Verification**: Verified that `gpio_read()` accurately reads the state of internal pull-up (HIGH) and pull-down (LOW) configurations on pin PC4 without requiring physical jumper wires.
- **Output Verification**: Verified that `gpio_toggle()`, `gpio_set()`, and `gpio_clear()` successfully and reliably manipulate the onboard LED connected to PD6. This was demonstrated physically by producing a mathematically precise Rapid Strobe (using toggle) and an S-O-S Morse Code sequence (using set and clear).

**Video / Photo Link**:

[🎥 Watch Hardware Execution Video](./Task3_HW_evidence.mp4)

## 2. UART Logs

### Explanation: How the application uses the library
The application code (`main.c`) strictly relies on the implemented custom library (`gpio.h` / `gpio.c`) for all hardware interactions. No direct register modifications exist in the application code.
1. It uses `gpio_init()` to initialize the system core clocks for the requested ports, configure PC4 as an input, and PD6 as a push-pull output.
2. It uses `gpio_read()` to capture and print the logic level of PC4 over UART, proving the inputs work.
3. It uses `gpio_toggle()` inside `for` loops to rapidly invert the state of PD6, achieving the Strobe effect.
4. It uses explicit `gpio_set()` to turn on PD6 and `gpio_clear()` to turn off PD6 at specific timings to create the Morse Code pattern.

**Screenshot**:

![UART Logs Screenshot](./Task3_terminal_evidence.png)

**Raw Log Output**:

```text

System Initialized.
Starting Advanced GPIO Demo (Wire-Free Mode)...

--- Testing GPIO Input (Read) API ---
PC4 Configured as PULL-UP. Read State: HIGH (Expected: HIGH)
PC4 Configured as PULL-DOWN. Read State: LOW (Expected: LOW)

--- Testing GPIO Output APIs (LED Pattern) ---

=== [Execution Cycle 1] Complex LED Pattern Demo ===
-> Phase 1: Rapid Strobe (Testing gpio_toggle)
-> Phase 2: S-O-S Signal (Testing gpio_set & gpio_clear)
   Sending 'S' (...)
   Sending 'O' (---)
   Sending 'S' (...)
-> Cycle complete. Waiting before repeat...

=== [Execution Cycle 2] Complex LED Pattern Demo ===
-> Phase 1: Rapid Strobe (Testing gpio_toggle)
-> Phase 2: S-O-S Signal (Testing gpio_set & gpio_clear)
```
