/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define SPLIT_HAND_PIN      B11  // high = left, low = right
#define USER_BUTTON_PIN     A15
#define DEBUG_LED_PIN       C13

// WS2812 RGB LED strip input and number of LEDs
#define WS2812_PWM_DRIVER        PWMD8
#define WS2812_PWM_CHANNEL       1
#define WS2812_PWM_PAL_MODE      3
#define WS2812_PWM_DMA_STREAM    STM32_DMA2_STREAM1
#define WS2812_PWM_DMA_CHANNEL   7
#define WS2812_EXTERNAL_PULLUP

#define BACKLIGHT_PWM_DRIVER     PWMD3
#define BACKLIGHT_PWM_CHANNEL    2
#define BACKLIGHT_PAL_MODE       2

/* Audio config */
#define AUDIO_PIN               A4
#define AUDIO_PIN_ALT           A5
#define AUDIO_PIN_ALT_AS_NEGATIVE

/* serial.c configuration for split keyboard */
#define SERIAL_USART_DRIVER      SD1
#define SERIAL_USART_TX_PIN      A10
#define SERIAL_USART_TX_PAL_MODE 7
#define SERIAL_USART_RX_PIN      A9
#define SERIAL_USART_RX_PAL_MODE 7
#define SERIAL_USART_TIMEOUT     10
#define SERIAL_USART_SPEED       (3 * 1024 * 1024)
#define SERIAL_USART_FULL_DUPLEX


/* i2c config for oleds */
#define I2C_DRIVER        I2CD1
#define I2C1_CLOCK_SPEED  400000
#define I2C1_DUTY_CYCLE   FAST_DUTY_CYCLE_16_9

/* spi config for eeprom and pmw3360 sensor */
#define SPI_DRIVER        SPID1
#define SPI_SCK_PIN       B3
#define SPI_SCK_PAL_MODE  5
#define SPI_MOSI_PIN      B5
#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN      B4
#define SPI_MISO_PAL_MODE 5


/* pmw3360 config  */
#define POINTING_DEVICE_CS_PIN B8
#define POINTING_DEVICE_ROTATION_270
#undef ROTATIONAL_TRANSFORM_ANGLE
#define PMW33XX_SPI_DIVISOR 8

// lcd
#define DISPLAY_RST_PIN B13
#define DISPLAY_DC_PIN B12
#define DISPLAY_CS_PIN B9
#define DISPLAY_SPI_DIVIDER 1

#if defined(OLED_ENABLE) && defined(OLED_TRANSPORT_SPI)
#define OLED_RST_PIN     DISPLAY_RST_PIN
#define OLED_DC_PIN      DISPLAY_DC_PIN
#define OLED_CS_PIN      DISPLAY_CS_PIN
#define OLED_SPI_DIVISOR DISPLAY_SPI_DIVIDER
#endif

#define DRV2605L_FB_ERM_LRA   0
#define DRV2605L_GREETING     DRV2605L_EFFECT_750_MS_ALERT_100
#define DRV2605L_DEFAULT_MODE DRV2605L_EFFECT_BUZZ_1_100
