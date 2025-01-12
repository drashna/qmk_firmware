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

#define USER_BUTTON_PIN     E2
#define DEBUG_LED_PIN       E3
// #define USB_VBUS_PIN        A7

#define USB_DRIVER USBD2

// WS2812 RGB LED strip input and number of LEDs
#define WS2812_PWM_DRIVER        PWMD8
#define WS2812_PWM_CHANNEL       4
#define WS2812_PWM_PAL_MODE      3
#define WS2812_PWM_DMA_STREAM    STM32_DMA2_STREAM1
#define WS2812_PWM_DMA_CHANNEL   7
// #define WS2812_EXTERNAL_PULLUP

#define BACKLIGHT_PWM_DRIVER     PWMD3
#define BACKLIGHT_PWM_CHANNEL    3
#define BACKLIGHT_PAL_MODE       3

/* Audio config */
#define AUDIO_PIN               A4
#define AUDIO_PIN_ALT           A5
#define AUDIO_PIN_ALT_AS_NEGATIVE

/* serial.c configuration for split keyboard */
#define SERIAL_USART_DRIVER      SD1
#define SERIAL_USART_TX_PIN      B6
#define SERIAL_USART_RX_PIN      B7
#define SERIAL_USART_TIMEOUT     10
#define SERIAL_USART_SPEED       (2 * 1024 * 1024)
#define SERIAL_USART_FULL_DUPLEX


/* i2c config for oleds */
#define I2C_DRIVER        I2CD1
#define I2C1_SCL_PIN      B8
#define I2C1_SDA_PIN      B9
#define I2C1_CLOCK_SPEED  400000
#define I2C1_DUTY_CYCLE   FAST_DUTY_CYCLE_16_9

/* spi config for eeprom and pmw3360 sensor */
#define SPI_DRIVER        SPID1
#define SPI_SCK_PIN       B3
#define SPI_MOSI_PIN      B5
#define SPI_MISO_PIN      B4

#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN G13
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR    2
#define EXTERNAL_FLASH_SIZE                 (8 * 1024 * 1024)

/* pmw3360 config  */
#define POINTING_DEVICE_CS_PIN G14
#define POINTING_DEVICE_ROTATION_270
#undef ROTATIONAL_TRANSFORM_ANGLE
#define PMW33XX_SPI_DIVISOR 16

// lcd
#define DISPLAY_RST_PIN C12
#define DISPLAY_DC_PIN C11
#define DISPLAY_CS_PIN C10
#define DISPLAY_SPI_DIVIDER 1

#define DRV2605L_FB_ERM_LRA   0
#define DRV2605L_GREETING     DRV2605L_EFFECT_750_MS_ALERT_100
#define DRV2605L_DEFAULT_MODE DRV2605L_EFFECT_BUZZ_1_100

#if HAL_USE_FSMC == TRUE && HAL_USE_SDRAM == TRUE
#define SDRAM_DATA __attribute__((section(".sdram")))
#else
#define SDRAM_DATA
#endif
