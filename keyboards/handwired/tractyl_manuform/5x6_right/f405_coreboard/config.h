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

// #define USB_VBUS_PIN        B12
#define SPLIT_HAND_PIN      A13  // high = left, low = right
#define USER_BUTTON_PIN     C13

// WS2812 RGB LED strip input and number of LEDs
#define WS2812_PWM_DRIVER   PWMD1  // default: PWMD2
#define WS2812_PWM_CHANNEL  2      // default: 2
#define WS2812_PWM_PAL_MODE 1      // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#define WS2812_EXTERNAL_PULLUP
#define WS2812_PWM_COMPLEMENTARY_OUTPUT // Define for a complementary timer output (TIMx_CHyN); omit for a normal timer output (TIMx_CHy).
#define WS2812_PWM_DMA_STREAM   STM32_DMA2_STREAM5  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_PWM_DMA_CHANNEL  6                   // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_PWM_TARGET_PERIOD 800000

//#define DEBUG_LED_PIN      B2

/* Audio config */
#define AUDIO_PIN          A4
#define AUDIO_PIN_ALT      A5
#define AUDIO_PIN_ALT_AS_NEGATIVE

/* serial.c configuration for split keyboard */
#define SERIAL_USART_FULL_DUPLEX  // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN      A9
#define SERIAL_USART_RX_PIN      A10
#define SERIAL_USART_DRIVER      SD1
#define SERIAL_USART_TX_PAL_MODE 7    // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_RX_PAL_MODE 7    // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TIMEOUT     100  // USART driver timeout. default 100
#define SERIAL_USART_SPEED       921600

#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

/* i2c config for oleds */
#define I2C_DRIVER        I2CD1
#define I2C1_CLOCK_SPEED  400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_16_9

/* spi config for eeprom and pmw3360 sensor */
#define SPI_DRIVER                           SPID2
#define SPI_SCK_PIN                          B13
#define SPI_SCK_PAL_MODE                     5
#define SPI_MOSI_PIN                         B14
#define SPI_MOSI_PAL_MODE                    5
#define SPI_MISO_PIN                         B15
#define SPI_MISO_PAL_MODE                    5


/* pmw3360 config  */
#define PMW33XX_CS_PIN                       C6

// lcd
/*
RST C8
DC  C7
CS  C9

*/
