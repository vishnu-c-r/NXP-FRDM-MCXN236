/*
 * 01_rgb_color_cycler — the first custom program.
 *
 * Auto-cycles the onboard RGB LED through 8 colors using plain GPIO (on/off).
 * Because each channel is only on or off, this can make exactly 2^3 = 8 colors.
 * (Projects 02+ switch to hardware PWM to get millions.)
 *
 * FRDM-MCXN236. SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_gpio_cmsis.h"
#include "app.h"

#define RGB_GPIO   Driver_GPIO_PORT4        /* all 3 LEDs live on port 4 */
#define RED_PIN    BOARD_LED_RED_GPIO_PIN   /* 18 */
#define GREEN_PIN  BOARD_LED_GREEN_GPIO_PIN /* 17 */
#define BLUE_PIN   BOARD_LED_BLUE_GPIO_PIN  /* 19 */

#define COLOR_DELAY_LOOPS 4000000U          /* crude busy-wait; bigger = slower */

static void delay(void)
{
    for (volatile uint32_t i = 0; i < COLOR_DELAY_LOOPS; i++)
    {
        __NOP();
    }
}

/* 1 = light a color, 0 = off. Inverted here because the LED is active-low. */
static void rgb_set(uint8_t r, uint8_t g, uint8_t b)
{
    RGB_GPIO.SetOutput(RED_PIN,   r ? LOGIC_LED_ON : LOGIC_LED_OFF);
    RGB_GPIO.SetOutput(GREEN_PIN, g ? LOGIC_LED_ON : LOGIC_LED_OFF);
    RGB_GPIO.SetOutput(BLUE_PIN,  b ? LOGIC_LED_ON : LOGIC_LED_OFF);
}

int main(void)
{
    BOARD_InitHardware();
    PRINTF("\r\nRGB color cycler (GPIO)\r\n");

    /* Set up each LED pin as a GPIO output, start off. */
    const uint32_t pins[] = {RED_PIN, GREEN_PIN, BLUE_PIN};
    for (uint32_t i = 0; i < ARRAY_SIZE(pins); i++)
    {
        RGB_GPIO.Setup(pins[i], NULL);
        RGB_GPIO.SetDirection(pins[i], ARM_GPIO_OUTPUT);
        RGB_GPIO.SetOutput(pins[i], LOGIC_LED_OFF);
    }

    while (1)
    {
        /*      R  G  B */
        rgb_set(1, 0, 0); delay(); /* red     */
        rgb_set(0, 1, 0); delay(); /* green   */
        rgb_set(0, 0, 1); delay(); /* blue    */
        rgb_set(1, 1, 0); delay(); /* yellow  */
        rgb_set(0, 1, 1); delay(); /* cyan    */
        rgb_set(1, 0, 1); delay(); /* magenta */
        rgb_set(1, 1, 1); delay(); /* white   */
        rgb_set(0, 0, 0); delay(); /* off     */
    }
}
