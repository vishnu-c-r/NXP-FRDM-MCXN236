/*
 * 03_auto_rainbow — smooth self-fading rainbow.
 *
 * Sweeps hue 0..359 continuously and converts each to RGB with hue_to_rgb()
 * (see rgb.c). With CTIMER3 PWM behind RGB_Set, the LED fades smoothly through
 * the whole spectrum -- no button, no fixed palette.
 *
 * FRDM-MCXN236. SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "pin_mux.h"
#include "board.h"
#include "app.h"
#include "rgb.h"

int main(void)
{
    BOARD_InitHardware();
    PRINTF("\r\nAuto rainbow (PWM)\r\n");

    RGB_Init();

    uint16_t hue = 0;
    while (1)
    {
        color_t c = hue_to_rgb(hue);
        RGB_Set(c.r, c.g, c.b);
        hue = (hue + 1) % 360;
        SDK_DelayAtLeastUs(50000, SystemCoreClock); /* ~50 ms/step -> ~18 s per loop */
    }
}
