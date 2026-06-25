# NXP FRDM-MCXN236 — Learning Projects

Hands-on projects on the **NXP FRDM-MCXN236** dev board (MCX N236, Arm Cortex-M33), built with the MCUXpresso SDK and MCUXpresso for VS Code. Each numbered folder is a self-contained program, in the order I built it — a record of learning the board from "blink an LED" up to hardware-PWM color control.

## Projects

| # | Folder | What it does | Key concepts |
|---|--------|--------------|--------------|
| 00 | [`00_button_toggle_led`](./00_button_toggle_led) | Button toggles the red LED | CMSIS GPIO, edge interrupt (baseline) |
| 01 | [`01_rgb_color_cycler`](./01_rgb_color_cycler) | Auto-cycle 8 colors (GPIO on/off) | GPIO outputs, color mixing, the 8-color ceiling |
| 02 | [`02_button_color_cycler`](./02_button_color_cycler) | Button steps a 24-color wheel | CTIMER3 **hardware PWM**, palette + index |
| 03 | [`03_auto_rainbow`](./03_auto_rainbow) | Smooth self-fading rainbow | `hue_to_rgb` generator, continuous fade |
| 04 | [`04_hold_color_picker`](./04_hold_color_picker) | Hold to scroll the rainbow, release to pick | button **level** (polling) vs edge, persistent state |

## The board (quick reference)

- **MCU:** MCX N236 (`MCXN236VDF`), Cortex-M33, core `cm33_core0`.
- **RGB LED:** on `GPIO4`, **active-low** (write 0 = on). Red = pin 18, Green = 17, Blue = 19.
  - For PWM these pins map to CTIMER3 match outputs: Blue = `CT3_MAT1`, Red = `CT3_MAT2`, Green = `CT3_MAT3`.
- **Button SW3:** `GPIO0` pin 6, active-low (pressed = 0 / falling edge).
- **Debug console:** LPUART4, 115200 baud (over the MCU-Link USB).

## Building any project

These are the application sources. Each is meant to be dropped into the mcuxsdk
`examples/cmsis_driver_examples/gpio/button_toggle_led` project:

1. Put `main.c` (and `rgb.c` if present) in the project's `src/`, and `rgb.h` in `inc/`.
2. If a project has `rgb.c`, add it to `SOURCES` in `CMakeLists.txt`.
3. Enable the drivers it needs in `prj.conf` (each folder's README lists them — GPIO and/or CTIMER).
4. Configure + build + flash with MCUXpresso for VS Code (LinkServer / MCU-Link).

## Notes / observations

- The LEDs are **active-low**, so PWM brightness is inverted into duty cycle (`duty = 100 − brightness%`).
- White (`255,255,255`) comes out slightly **blue-tinted** on this board — the blue die is the strongest. A real per-die efficiency lesson.

---

> 🌱 *This README is updated as new projects are added.* Next ideas: full HSV (saturation + brightness), gamma correction, white-balance tuning, and non-blocking timing via SysTick.

Licensed under the terms in [LICENSE](./LICENSE).
