# 04 — Hold-to-Pick Color Picker (PWM)

Press **and hold** the button to scroll the rainbow; **release** to freeze on a color. Press again to resume from where you left off.

## What it demonstrates
- Reading a button's **level** (`GetInput`, polling) vs. an **edge** (interrupt) — the key new idea.
- State that persists "for free": `hue` is only advanced while the button is held, so releasing just stops it and the next hold continues from the same value. No save/restore code needed.

## Hardware (FRDM-MCXN236)
- RGB on `GPIO4` via CTIMER3 PWM. Button SW3 on `GPIO0` pin 6, **active-low** (held = reads 0).

## How it works
`main` polls the button every loop. Held → step `hue`, `RGB_Set`, delay (rainbow runs). Released → the `if` is false, so the LED sits on the last color.

> If the frozen color flickers, the button line may need a pull-up: add
> `EXAMPLE_BUTTON_GPIO_INTERFACE.SetPullResistor(EXAMPLE_BUTTON_PIN, ARM_GPIO_PULL_UP);` after `Setup`.

## Files
- `main.c` — the hold-to-scroll loop
- `rgb.c` / `rgb.h` — PWM RGB module + `hue_to_rgb`

## Build / run
Same as projects 02–03 (drop into the `button_toggle_led` example; add `rgb.c` to `SOURCES`).
`prj.conf` needs:

    CONFIG_MCUX_COMPONENT_driver.cmsis_gpio=y
    CONFIG_MCUX_COMPONENT_driver.ctimer=y
