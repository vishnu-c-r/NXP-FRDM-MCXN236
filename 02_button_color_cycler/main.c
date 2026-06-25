/*
 * 02_button_color_cycler — button press steps through a 24-color palette.
 *
 * Upgrade over project 01: the LEDs are now driven by CTIMER3 hardware PWM
 * (see rgb.c), so each channel has 256 brightness levels instead of on/off.
 * That unlocks the in-between colors (orange, pink, azure...) GPIO couldn't make.
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

/* A full hue wheel: 24 steps around the spectrum, then white and off. */
static const color_t colors[] = {
    {255,   0,   0}, /* red          */
    {255,  64,   0}, /* red-orange   */
    {255, 128,   0}, /* orange       */
    {255, 191,   0}, /* amber        */
    {255, 255,   0}, /* yellow       */
    {191, 255,   0}, /* chartreuse   */
    {128, 255,   0}, /* lime         */
    { 64, 255,   0}, /* green-yellow */
    {  0, 255,   0}, /* green        */
    {  0, 255,  64}, /* sea green    */
    {  0, 255, 128}, /* spring green */
    {  0, 255, 191}, /* aquamarine   */
    {  0, 255, 255}, /* cyan         */
    {  0, 191, 255}, /* sky blue     */
    {  0, 128, 255}, /* azure        */
    {  0,  64, 255}, /* cobalt       */
    {  0,   0, 255}, /* blue         */
    { 64,   0, 255}, /* indigo       */
    {128,   0, 255}, /* violet       */
    {191,   0, 255}, /* purple       */
    {255,   0, 255}, /* magenta      */
    {255,   0, 191}, /* fuchsia      */
    {255,   0, 128}, /* rose         */
    {255,   0,  64}, /* crimson      */
    {255, 255, 255}, /* white        */
    {  0,   0,   0}, /* off          */
};
#define NUM_COLORS (sizeof(colors) / sizeof(colors[0]))

static volatile bool g_buttonPressed = false;
static uint8_t       g_colorIndex    = 0;

static void BUTTON_EventCallback(uint32_t pin, uint32_t event)
{
    if (pin == EXAMPLE_BUTTON_PIN && event == ARM_GPIO_TRIGGER_FALLING_EDGE)
    {
        g_buttonPressed = true;
    }
}

int main(void)
{
    BOARD_InitHardware();
    PRINTF("\r\nButton color cycler (PWM)\r\n");

    RGB_Init();
    EXAMPLE_BUTTON_GPIO_INTERFACE.Setup(EXAMPLE_BUTTON_PIN, BUTTON_EventCallback);
    EXAMPLE_BUTTON_GPIO_INTERFACE.SetEventTrigger(EXAMPLE_BUTTON_PIN, ARM_GPIO_TRIGGER_FALLING_EDGE);

    RGB_Set(colors[0].r, colors[0].g, colors[0].b); /* show the first color */

    while (1)
    {
        if (g_buttonPressed)
        {
            g_buttonPressed = false;
            g_colorIndex = (g_colorIndex + 1) % NUM_COLORS;
            RGB_Set(colors[g_colorIndex].r, colors[g_colorIndex].g, colors[g_colorIndex].b);
        }
    }
}
