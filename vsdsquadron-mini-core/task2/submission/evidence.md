# Task 2: UART and GPIO Bring-up Evidence

## 1. UART Evidence
*The terminal output below demonstrates that the board successfully booted and printed the initialization messages alongside a continuous counting sequence via UART.*

**Video Link:**
<!-- 🎥 Video showing the live scrolling output -->
<video src="./UART_Check.mp4" controls="controls" width="600"></video>

---

## 2. GPIO Evidence
*The evidence below shows the onboard LED blinking periodically, mapped to the correct firmware settings.*

**Video Link:**
<!-- 🎥 Video tracking the toggling LED -->
<video src="./GPIO_Check.mp4" controls="controls" width="600"></video>

---

## 3. Pin Configuration Details

* **Physical Pin Label:** PD6 (Onboard user LED)
* **Firmware GPIO Number:** GPIO_PIN_6 on Port D

---

## 4. Explanation & Verification

**How I verified correct behavior:**
1. **Compilation & Flashing:** I compiled the main.c and gpio.c files using the CH32V standard peripheral library (PlatformIO). I verified that the firmware successfully flashed to the 16KB CodeFlash using the onboard programmer.
2. **UART Output Validation:** I opened the PlatformIO Serial Monitor at a baud rate of 115200. After pressing the physical reset button, the terminal immediately displayed the expected initial boot headers (Board: VSDSquadron Mini, Firmware Version: 1.0.0), followed by the dynamically incrementing counter (Running count: 0, 1, etc.) precisely once per second.
3. **GPIO Validation:** Simultaneously, I monitored physical pin **PD6**. Given that the TEST_PORT was configured to D and TEST_PIN to GPIO_PIN_6, the onboard blue LED correctly toggled on and off every second in sync with the UART messages sequence, confirming that the abstraction layer (gpio_init, gpio_toggle) correctly manipulated the hardware BSHR/BCR registers.

