# LED Pattern Sequencer

## Project Overview

The **LED Pattern Sequencer** is an interactive, UART-scriptable firmware application built for the VSDSquadron Mini. It allows users to program dynamic blinking patterns and playback speeds via a serial terminal. Due to the hardware constraint where the onboard LED shares the pin (`PD6`) with the default UART RX line, this project utilizes a novel **Dynamic Pin-Multiplexing Hybrid State Machine**. It hot-swaps the pin's hardware configuration on the fly to bounce between acting as a serial communication listener and an output driver without crashing the microcontroller.

## Target Hardware

- **Board:** VSDSquadron Mini
- **Microcontroller:** CH32V003 (RISC-V)
- **Shared Resource:** `PD6` (Onboard LED / UART RX)

## Supported Drivers

- **GPIO:** Low-level port/pin manipulation including dynamic re-mapping between `INPUT_FLOATING` and `OUTPUT_PP`.
- **UART:** Non-blocking serial communication for standard 115200 baud interactive command parsing.
- **Timer:** SysTick-based timekeeper for precise 1ms ticks and reliable delays.

## Folder Structure

```text
task4/
├── app/
│   └── main.c           # Application state machine and command parser
├── lib/
│   ├── gpio.c           # GPIO driver implementation
│   ├── gpio.h           # GPIO driver API
│   ├── timer.c          # SysTick Timer driver implementation
│   ├── timer.h          # SysTick Timer driver API
│   ├── uart.c           # UART driver implementation
│   └── uart.h           # UART driver API
└── platformio.ini       # Build configuration
```

## Quick Start
To build and flash this to your hardware:

```bash
cd vsdsquadron-mini-core/task4/submission/
pio run
pio run -t upload
pio device monitor -b 115200
```