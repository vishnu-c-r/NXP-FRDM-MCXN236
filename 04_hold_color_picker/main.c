/*
 * 04_hold_color_picker — press-and-hold to pick a color.
 *
 * While the button is HELD, the rainbow scrolls (hue advances). Release to
 * freeze on the current color. Press again and it resumes from there -- the
 * "remember" behavior is automatic because `hue` is a persistent variable.
 *
 * New idea vs project 03: read the button's LEVEL (polling GetInput) instead of
 * an edge interrupt, because here we care whether it's held *right now*.
 *
 * FRDM-MCXN236. SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_gpio_cmsis.h"
#include "app.h"
#include "rgb.h"

int main(void)
{
    BOARD_InitHardware();
    PRINTF("\r\nHold-to-pick color picker (PWM)\r\n");

    RGB_Init();
    EXAMPLE_BUTTON_GPIO_INTERFACE.Setup(EXAMPLE_BUTTON_PIN, NULL); /* configure as input */

    uint16_t hue = 0;
    while (1)
    {
        /* active-low: GetInput == 0 means the button is held down */
        if (EXAMPLE_BUTTON_GPIO_INTERFACE.GetInput(EXAMPLE_BUTTON_PIN) == 0)
        {
            color_t c = hue_to_rgb(hue);
            RGB_Set(c.r, c.g, c.b);
            hue = (hue + 1) % 360;
            SDK_DelayAtLeastUs(50000, SystemCoreClock);
        }
        /* released -> do nothing -> LED holds the last color */
    }
}
