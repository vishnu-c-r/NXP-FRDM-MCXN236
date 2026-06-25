# 02 — Button Color Cycler (PWM)

Press the button → step to the next color in a 24-color wheel. The first project on **hardware PWM**.

## What it demonstrates
- CTIMER3 PWM driving the RGB LED (`rgb.c` / `rgb.h`) — 256 levels per channel.
- A color palette + index, advanced by a button interrupt.
- In-between colors (orange, pink, azure…) that on/off GPIO can't make.

## Hardware (FRDM-MCXN236)
- RGB on `GPIO4` (active-low), driven via CTIMER3 match outputs CT3_MAT1/2/3.
- Button SW3 on `GPIO0` pin 6 (falling edge = press).

## How it works
`RGB_Init()` sets up CTIMER3 PWM. The button ISR sets a flag; the loop advances `g_colorIndex` (mod 26) and calls `RGB_Set` with that palette entry.

## Files
- `main.c` — palette + button logic
- `rgb.c` / `rgb.h` — the reusable PWM RGB module

## Build / run
Drop the files into the mcuxsdk `button_toggle_led` example: `main.c` and `rgb.c` in `src/`, `rgb.h` in `inc/`, and add `rgb.c` to `SOURCES` in `CMakeLists.txt`.
`prj.conf` needs:

    CONFIG_MCUX_COMPONENT_driver.cmsis_gpio=y
    CONFIG_MCUX_COMPONENT_driver.ctimer=y
