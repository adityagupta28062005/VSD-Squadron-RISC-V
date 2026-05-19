# Task 2 - VSDSquadron Mini Board Bring-Up

## Overview
This repository contains the firmware implementation for Task 2. It transitions to real hardware bring-up on the CH32V003 RISC-V microcontroller. The firmware successfully initializes the board, transmits debug messages via UART, and toggles a hardware GPIO pin using a custom firmware API layer, avoiding direct register manipulation in \main.c\.

## GPIO Pin Chosen
- **Physical Pin:** PD6 (Onboard LED)
- **Firmware GPIO number:** Port D, Pin 6 (\GPIOD\, \GPIO_PIN_6\)
- **Reason:** I chose PD6 because it controls the built-in onboard LED on the VSDSquadron Mini board. This provides immediate feedback to validate the GPIO logic without requiring external wires, breadboards, or oscilloscope probes.

## UART Message Description
Upon reset or power-up, the firmware outputs a clear startup identifier over UART at 115200 baud rate:
- It prints the Board Name ('VSDSquadron Mini') and Firmware Version ('1.0.0').
- It enters a continuous superloop where it outputs 'Running count: [x]' every 1000ms. This sequential counter proves that the processor is running a continuous timing loop and successfully maintaining the serial connection over time.

## How to Build and Flash
This project is built using PlatformIO in VS Code with the custom \sdip/vsdsquadron_pio\ platform.

**Option 1: Using VS Code PlatformIO GUI**
1. Open the folder in VS Code.
2. Click the **Build** (✓) icon on the bottom blue toolbar.
3. Click the **Upload** (→) icon to flash the board via the WCH-Link programmer.
4. Click the **Serial Monitor** (🔌) icon to view the UART output.

**Option 2: Using Command Line (CLI)**
To build and flash from the terminal, execute:
\\ash
# Build and Upload
C:\Users\adity\.platformio\penv\Scripts\platformio.exe run --target upload

# Open Serial Monitor
C:\Users\adity\.platformio\penv\Scripts\platformio.exe device monitor -p COM5 -b 115200
\