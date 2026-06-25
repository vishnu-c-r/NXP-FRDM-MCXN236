/*
 * rgb.h - RGB LED control via CTIMER3 hardware PWM (FRDM-MCXN236).
 *
 * The three onboard LEDs sit on CTIMER3 match outputs:
 *   blue = CT3_MAT1, red = CT3_MAT2, green = CT3_MAT3 (Match_0 = PWM period).
 */
#ifndef _RGB_H_
#define _RGB_H_

#include <stdint.h>

typedef struct
{
    uint8_t r, g, b;
} color_t;

void    RGB_Init(void);                           /* set up CTIMER3 PWM on the 3 LED pins */
void    RGB_Set(uint8_t r, uint8_t g, uint8_t b); /* 0-255 brightness per channel         */
color_t hue_to_rgb(uint16_t hue);                 /* hue 0..359 -> full-saturation color  */

#endif /* _RGB_H_ */
