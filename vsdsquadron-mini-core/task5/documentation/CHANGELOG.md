# Changelog

All notable changes to the LED Pattern Sequencer project will be documented in this file.

## [v1.0.0] - Initial Release

### Added
- **GPIO Driver (`gpio.c/h`)**: Implemented low-level port manipulation supporting fully dynamic pin mode remapping.
- **UART Driver (`uart.c/h`)**: Engineered non-blocking serial communication driver designed for fast command parsing without halting the CPU.
- **Timer Driver (`timer.c/h`)**: Integrated SysTick-based timekeeper for precise 1 millisecond execution delays.
- **Application Logic (`main.c`)**: Developed core state machine controlling User CLI input tracking and interactive pattern loading.
- **Dynamic Pin-Multiplexing Architecture**: Implemented a sophisticated transition mechanism allowing `PD6` to alternate rapidly between serving as a serial RX ingress line and an active hardware LED Power Source without causing bus crashes or MCU framing loops.
- **Command CLI**: Added terminal support for tracking variables: `pattern <bin>`, `delay <ms>`, `play`, `help`, `exit`.