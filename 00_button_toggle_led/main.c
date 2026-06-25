/*
 * 00_button_toggle_led — baseline example (NXP).
 *
 * Press SW3 -> toggle the red LED. This is the NXP CMSIS-GPIO example we
 * started from; everything else in this repo grew out of it.
 *
 * Copyright 2024 NXP
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_gpio_cmsis.h"
#include "app.h"

/* Whether the SW button is pressed */
volatile bool g_ButtonPress = false;
uint32_t LEDLevel = LOGIC_LED_OFF;

static void BUTTON_EventCallback(uint32_t pin, uint32_t event)
{
    if (pin == EXAMPLE_BUTTON_PIN && event == ARM_GPIO_TRIGGER_FALLING_EDGE)
    {
        g_ButtonPress = true;
        PRINTF("\r\nBUTTON Pressed! \r\n");
    }
}

int main(void)
{
    BOARD_InitHardware();

    PRINTF("\r\nCMSIS GPIO Example! \r\n");
    PRINTF("\r\nUse Button to toggle LED! \r\n");

    /* BUTTON pin set up */
    EXAMPLE_BUTTON_GPIO_INTERFACE.Setup(EXAMPLE_BUTTON_PIN, BUTTON_EventCallback);
    EXAMPLE_BUTTON_GPIO_INTERFACE.SetEventTrigger(EXAMPLE_BUTTON_PIN, ARM_GPIO_TRIGGER_FALLING_EDGE);
    /* LED pin set up */
    EXAMPLE_LED_GPIO_INTERFACE.Setup(EXAMPLE_LED_PIN, NULL);
    EXAMPLE_LED_GPIO_INTERFACE.SetDirection(EXAMPLE_LED_PIN, ARM_GPIO_OUTPUT);
    EXAMPLE_LED_GPIO_INTERFACE.SetOutput(EXAMPLE_LED_PIN, LOGIC_LED_OFF);

    while (1)
    {
        if (g_ButtonPress)
        {
            if (LEDLevel == LOGIC_LED_OFF)
            {
                EXAMPLE_LED_GPIO_INTERFACE.SetOutput(EXAMPLE_LED_PIN, LOGIC_LED_ON);
                LEDLevel = LOGIC_LED_ON;
            }
            else
            {
                EXAMPLE_LED_GPIO_INTERFACE.SetOutput(EXAMPLE_LED_PIN, LOGIC_LED_OFF);
                LEDLevel = LOGIC_LED_OFF;
            }
            g_ButtonPress = false;
        }
    }
}
