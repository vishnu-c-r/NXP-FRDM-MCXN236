# 03 — Auto Rainbow (PWM)

The LED fades smoothly through the entire spectrum on its own — no button, no palette.

## What it demonstrates
- A **generated** color wheel via `hue_to_rgb(hue)` instead of a lookup table.
- Continuous hue sweep + small delay = smooth fade.
- One reusable function pays off twice: the same `hue_to_rgb` also drives project 04.

## How it works
`hue_to_rgb(hue)` maps an angle 0–359° to a full-saturation RGB using 6-segment color-wheel math. `main` increments `hue` each loop, sets the color, and delays ~50 ms (≈18 s for a full loop). Smaller delay = faster fade.

## Files
- `main.c` — the hue sweep loop
- `rgb.c` / `rgb.h` — PWM RGB module + `hue_to_rgb`

## Build / run
Drop into the mcuxsdk `button_toggle_led` example (`main.c`, `rgb.c` in `src/`, `rgb.h` in `inc/`; add `rgb.c` to `SOURCES`).
`prj.conf` needs:

    CONFIG_MCUX_COMPONENT_driver.ctimer=y

> No button here, so `cmsis_gpio` isn't required — harmless to leave on if you reuse the example's `prj.conf`.
