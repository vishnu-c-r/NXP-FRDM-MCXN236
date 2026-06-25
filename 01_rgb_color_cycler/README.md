# 01 — RGB Color Cycler (GPIO) · *first custom code*

The first program written from scratch: auto-cycles the onboard RGB LED through 8 colors using plain GPIO on/off.

## What it demonstrates
- Driving the three RGB channels (R/G/B) as independent GPIO outputs.
- **Color mixing** by combining channels: red+green = yellow, all three = white.
- The hard ceiling of GPIO: each channel is on/off, so 2³ = **8 colors only**.

## Hardware (FRDM-MCXN236)
- RGB LED on `GPIO4`, **active-low** (`LOGIC_LED_ON` = 0): red = 18, green = 17, blue = 19.

## How it works
`rgb_set(r, g, b)` writes each pin (inverting for active-low). `main` walks red → green → blue → yellow → cyan → magenta → white → off, each held by a busy-wait `delay()`.

## Limitation → next step
On/off gives no **brightness** control, so no orange/pink/pastels — just 8 fixed mixes. Projects 02–04 use **CTIMER hardware PWM** to get ~16M colors.

## Build / run
Replace the source in the mcuxsdk `button_toggle_led` example with `main.c`.
`prj.conf` needs: `CONFIG_MCUX_COMPONENT_driver.cmsis_gpio=y`
