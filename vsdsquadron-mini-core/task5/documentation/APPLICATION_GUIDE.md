# Application Guide

This guide explains the inner logic, state tracking, and edge-case handling of the `main.c` Application.

## Application States

The core logic revolves around two primary states handled by `SequencerState`:

1. **`STATE_STOPPED` (Command Mode):**
   - This is the interactive phase.
   - The main `while(1)` loop constantly queries the non-blocking UART receiver.
   - Supported commands include: `pattern`, `delay`, `help`, `exit`, and `play`.
   - The application manages a 32-character buffer (`uart_rx_buffer`) that processes characters, handles backspace/delete visually, and parses substrings using `strtok()`.

2. **`STATE_PLAYING` (Playback Mode):**
   - Transcends the interactive session to execute the requested visual blinking pattern.
   - Operates in a highly constrained, blocking `for` loop across 3 explicit playback cycles.
   - All keyboard input is intentionally ignored during this phase.

## Task Flow

1. **Hardware Init:** `hardware_init()` spins up the Core Clock, SysTick, and USART registers.
2. **Prompt Phase:** The system drops into `STATE_STOPPED` and prints a `>` prompt.
3. **Parse & Configure:** The user dictates settings (e.g., `delay 100`). The global variables `pattern_buffer` and `step_delay_ms` update dynamically.
4. **Trigger & Flush:** User types `play`. The system flushes pending TX data (`timer_delay_ms(50)`), shifts the state to `STATE_PLAYING`, and alters the `PD6` hardware mapping.
5. **Execute Pattern:** The app iterates through the binary elements of `pattern_buffer` (`'1'` = high; `'0'` = low) for the set delay milliseconds.
6. **Recovery & Unlock:** Once the cycles terminate, the system forces `PD6` back to a floating input. By performing a while-loop over `uart_data_available()`, the system discards "phantom" keystrokes that generated magnetically during toggling, successfully returning to `STATE_STOPPED`.

## Orchestrating Drivers

- The Application **never** modifies hardware registers directly. It strictly calls abstract methods (`gpio_init()`, `gpio_set()`).
- Time intervals are managed strictly via the `timer_delay_ms()` API referencing the SysTick timer, avoiding unreliable compiler-based delay loops.

## Handled Edge Cases

- **Character Erasing:** Supports `\b` and `0x7F` terminal deletions. It updates standard-out cleanly (`\b \b`) and shrinks the `uart_rx_index` pointer concurrently.
- **Buffer Overflows:** Capped to `MAX_UART_CMD_LEN`. Exceeding this boundary safely eats additional keys without corrupting memory logic.
- **Invalid Pattern Content:** Before accepting a `pattern` string, the `process_command` function loops aggressively through the token checking for anything that isn't `'0'` or `'1'`, actively rejecting the command if contamination is found.
- **Floating De-bounce:** After playback finishes, an intentional `timer_delay_ms(10)` combined with `while(uart_data_available()) { uart_read_char(); }` ensures no stray transient signals are routed to the parser.