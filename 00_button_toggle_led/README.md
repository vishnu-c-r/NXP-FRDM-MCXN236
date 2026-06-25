# 00 — Button Toggle LED (baseline)

The NXP CMSIS-GPIO example this whole repo started from. Press the button → the red LED toggles on/off.

## What it demonstrates
- The CMSIS GPIO driver API: `Setup`, `SetDirection`, `SetOutput`, and an edge-triggered callback.
- A button as an **interrupt input**, an LED as an **output**.
- The interrupt-sets-a-flag / main-loop-does-the-work pattern.

## Hardware (FRDM-MCXN236)
- **LED:** red, `GPIO4` pin 18, **active-low** (`LOGIC_LED_ON` = 0).
- **Button:** SW3, `GPIO0` pin 6, active-low (falling edge = press).

## How it works
The button's falling-edge interrupt sets `g_ButtonPress`. The main loop sees the flag and flips the LED state on each press.

## Build / run
Drop `main.c` into the mcuxsdk `examples/cmsis_driver_examples/gpio/button_toggle_led` project (replacing its source), then build & flash with MCUXpresso for VS Code.
`prj.conf` needs: `CONFIG_MCUX_COMPONENT_driver.cmsis_gpio=y`

> This is NXP's BSD-3-Clause example — included as the starting point of the journey.
