# Demo & Verification Guide

This functional guide acts as a reproducible walk-through, enabling a reviewer to interact with the device completely within **5 minutes**.

## Prerequisites
- A **VSDSquadron Mini** (CH32V003 based) connected via standard USB.
- The `PlatformIO` extension installed in VS Code.

## 1. Build and Flash
Run the following commands in the terminal from the `vsdsquadron-mini-core/task4/submission/` directory:

```bash
pio run
pio run -t upload
```
*Wait for the `[SUCCESS]` notification before continuing.*

## 2. UART Serial Setup
Connect to the serial port. You may use PlatformIO's built-in serial monitor (`pio device monitor`) or an external terminal emulator (like Tera Term or PuTTY). Verify the settings exactly as below:

- **Baud Rate:** 115200
- **Data Bits:** 8
- **Stop Bits:** 1
- **Parity:** None
- **Flow Control:** None

## 3. Execution Commands
Interact with your VSDSquadron Mini Terminal.

1. **Wake up the Terminal**
   Press **Enter** once to bring up the default prompt (`>`).
2. **Set the Playback Speed**
   Type: `delay 150` and press **Enter**.
   *Observation:* The console displays: "Delay updated."
3. **Register a Custom Pattern**
   Type: `pattern 1110001010` and press **Enter**.
   *Observation:* The console displays: "Pattern updated."
4. **Trigger Playback**
   Type: `play` and press **Enter**.

### Expected Hardware / System Observations (Critical)
* Once `play` is entered, the **Terminal Interface will freeze**. Typing random keys will not immediately appear on screen.
* The physical blue onboard LED (`PD6`) will begin pulsing rapidly according to the programmed ones (`1` = ON) and zeros (`0` = OFF) sequence you provided.
* It will cycle the pattern **exactly 3 times**.
* Once the 3rd loop completes, the system unlocks, spits out a clean configuration banner reflecting your latest settings, and reactivates the `>` interactive shell.

## 4. Halt Execution
To test the hard-exit handler:
Type: `exit`
*Observation:* The system says goodbye and drops into an infinite hold loop, functionally shutting down the board.