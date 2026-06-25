/*
 * rgb.c - RGB LED control via CTIMER3 hardware PWM (FRDM-MCXN236).
 *
 * Channel map:  Match_0 = period (no pin),  Match_1 = blue,  Match_2 = red,  Match_3 = green.
 * LEDs are active-low, so brightness is inverted into PWM duty (see to_duty()).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "rgb.h"
#include "board.h"
#include "fsl_port.h"
#include "fsl_ctimer.h"

#define RGB_CTIMER       CTIMER3
#define RGB_PERIOD_CH    kCTIMER_Match_0   /* no-pin channel -> defines PWM period */
#define RGB_PWM_FREQ_HZ  1000U             /* 1 kHz */

void RGB_Init(void)
{
    /* CTIMER3 has no clock by default -> attach one first.
       (Without this, CLOCK_GetCTimerClkFreq(3) returns 0 and the math breaks.) */
    CLOCK_SetClkDiv(kCLOCK_DivCtimer3Clk, 1u);
    CLOCK_AttachClk(kFRO_HF_to_CTIMER3);

    /* Mux all three LED pins to their CT3_MATx function (Alt4) */
    uint32_t Pins[3] = {BOARD_LED_RED_GPIO_PIN, BOARD_LED_GREEN_GPIO_PIN, BOARD_LED_BLUE_GPIO_PIN};
    for (int i = 0; i < 3; i++)
    {
        PORT_SetPinMux(PORT4, Pins[i], kPORT_MuxAlt4);
    }

    /* Init the timer */
    ctimer_config_t config;
    CTIMER_GetDefaultConfig(&config);          /* mode = timer, prescale = 0 */
    CTIMER_Init(RGB_CTIMER, &config);

    /* f_tick = source clock / (prescale + 1);  then  N = f_tick / freq - 1 */
    uint32_t timerClk = CLOCK_GetCTimerClkFreq(3U) / (config.prescale + 1U);
    uint32_t period   = (timerClk / RGB_PWM_FREQ_HZ) - 1U;   /* N */

    /* Each color shares Match_0 as the period channel; pins already muxed above. */
    CTIMER_SetupPwmPeriod(RGB_CTIMER, RGB_PERIOD_CH, kCTIMER_Match_1, period, 0U, false); /* blue  */
    CTIMER_SetupPwmPeriod(RGB_CTIMER, RGB_PERIOD_CH, kCTIMER_Match_3, period, 0U, false); /* green */
    CTIMER_SetupPwmPeriod(RGB_CTIMER, RGB_PERIOD_CH, kCTIMER_Match_2, period, 0U, false); /* red   */

    CTIMER_StartTimer(RGB_CTIMER);
}

/* brightness 0-255 -> PWM duty 0-100, inverted because the LED is active-low
   (255 brightness -> duty 0 -> pin low all period -> LED fully ON). */
static uint8_t to_duty(uint8_t brightness)
{
    return (uint8_t)(100U - (brightness * 100U / 255U));
}

void RGB_Set(uint8_t r, uint8_t g, uint8_t b)
{
    CTIMER_UpdatePwmDutycycle(RGB_CTIMER, RGB_PERIOD_CH, kCTIMER_Match_2, to_duty(r)); /* red   */
    CTIMER_UpdatePwmDutycycle(RGB_CTIMER, RGB_PERIOD_CH, kCTIMER_Match_3, to_duty(g)); /* green */
    CTIMER_UpdatePwmDutycycle(RGB_CTIMER, RGB_PERIOD_CH, kCTIMER_Match_1, to_duty(b)); /* blue  */
}

/* Map a hue angle (0..359) to a full-saturation, full-brightness RGB color.
   The wheel is 6 segments of 60 degrees; in each, one channel ramps while the
   others are pinned at 255 or 0. */
color_t hue_to_rgb(uint16_t hue)
{
    color_t c;
    uint8_t pos  = hue % 60;
    uint8_t up   = pos * 255 / 60;
    uint8_t down = 255 - up;

    switch (hue / 60)
    {
        case 0:  c.r = 255;  c.g = up;   c.b = 0;    break; /* red -> yellow   */
        case 1:  c.r = down; c.g = 255;  c.b = 0;    break; /* yellow -> green */
        case 2:  c.r = 0;    c.g = 255;  c.b = up;   break; /* green -> cyan   */
        case 3:  c.r = 0;    c.g = down; c.b = 255;  break; /* cyan -> blue    */
        case 4:  c.r = up;   c.g = 0;    c.b = 255;  break; /* blue -> magenta */
        case 5:  c.r = 255;  c.g = 0;    c.b = down; break; /* magenta -> red  */
        default: c.r = 0;    c.g = 0;    c.b = 0;    break; /* should never happen */
    }

    return c;
}
