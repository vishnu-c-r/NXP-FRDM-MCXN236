# Project Roadmap — FRDM-MCXN236 (board-only)

A living checklist of projects I can build using **only the onboard hardware** —
the RGB LED, the two buttons (SW2 / SW3), the UART debug console, and the MCU's
*internal* peripherals. **No external sensors or wiring.**

Tick items off as I finish them, and add my own ideas at the bottom.
Most map to an example under `mcuxsdk/examples/.../driver_examples/` for reference.

> Legend: `[ ]` todo · `[x]` done · *(SDK: …)* = reference example in the SDK

---

## ✅ Done (already in this repo)

- [x] GPIO output — drive the RGB LED → [`01_rgb_color_cycler`](./01_rgb_color_cycler)
- [x] Button input via **interrupt** (edge) → [`00_button_toggle_led`](./00_button_toggle_led), [`02_button_color_cycler`](./02_button_color_cycler)
- [x] Button input via **polling** (level) → [`04_hold_color_picker`](./04_hold_color_picker)
- [x] Hardware **PWM** with CTIMER3 → [`02`](./02_button_color_cycler)–[`04`](./04_hold_color_picker)
- [x] Color-wheel generator (`hue_to_rgb`) → [`03_auto_rainbow`](./03_auto_rainbow)

---

## Tier 1 — Digital I/O + timing

- [ ] **Button debounce** — remove mechanical bounce (timer + input)
- [ ] **Single / double / long-press detector** — classify presses by timing
- [ ] **Reaction-time game** — random delay → LED on → measure press time, print ms 🎮 *(SDK: ctimer)*
- [ ] **Morse code blinker** — type a letter in the console, LED blinks its Morse
- [ ] **Two-button menu** — SW2 = next, SW3 = select; RGB shows the state (a state machine)

## Tier 2 — Timers & PWM mastery

- [ ] **SysTick non-blocking blink** — `millis()`-style timing, no busy-wait
- [ ] **Breathing LED** — smooth PWM fade in/out
- [ ] **Stopwatch** — start / stop / lap with buttons, elapsed time over UART *(SDK: ctimer, lptmr)*
- [ ] **Metronome** — buttons adjust BPM, LED ticks
- [ ] **Frequency meter** — CTIMER input capture on a looped-back signal *(SDK: ctimer/capture)*

## Tier 3 — Analog (internal signals only, zero wiring)

- [ ] **MCU temperature monitor** — internal temp sensor → °C over UART; RGB shifts with heat *(SDK: lpadc/temperature_measurement)*
- [ ] **Supply-voltage monitor** — measure VDD via the internal bandgap/VREF *(SDK: vref_1, lpadc)*
- [ ] **Analog comparator alarm** — LPCMP trips the LED when a level crosses a reference *(SDK: lpcmp)*
- [ ] **DAC → ADC loopback self-test** — generate a value, read it back internally, verify

## Tier 4 — Communication / build a console

- [ ] **UART command shell** — type `red`, `temp`, `blink 5` to drive the board (a real command parser) *(SDK: lpuart)*
- [ ] **UART echo + line editing** — serial I/O fundamentals

## Tier 5 — "Real firmware" system peripherals

- [ ] **Boot counter in flash** — persists across resets, "booted N times" *(SDK: romapi)*
- [ ] **Reset-cause reporter** — print *why* it reset (power-on / watchdog / pin)
- [ ] **Watchdog demo** — WWDT resets if not fed; LED = alive, button starves it *(SDK: wwdt)*
- [ ] **Real-time clock** — IRTC keeps HH:MM:SS, alarm blinks LED, set over UART *(SDK: irtc)*
- [ ] **Low-power sleep + button wake** — deep sleep, wake on a button, RGB shows the mode *(SDK: syspm)*
- [ ] **TRNG dice / random color** — true-random RGB on each press 🎲
- [ ] **CRC tool** — checksum whatever I type in the console *(SDK: crc)*

## Capstones (combine several peripherals)

- [ ] **Reaction game + flash high-score + UART leaderboard**
- [ ] **UART mood-lamp** with flash-saved color presets (CLI + PWM + flash)
- [ ] **Simon-style memory game** with RGB + 2 buttons

---

## 💡 My own ideas (add freely)

- [ ] …
- [ ] …
- [ ] …
