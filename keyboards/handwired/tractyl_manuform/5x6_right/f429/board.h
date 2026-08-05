/*
    ChibiOS - Copyright (C) 2006-2026 Giovanni Di Sirio.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * This file has been automatically generated using ChibiStudio board
 * generator plugin. Do not edit manually.
 */

#ifndef BOARD_H
#define BOARD_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 * Setup for handwired Tractyl Manuform (5x6) F429 board.
 */

/*
 * Board identifier.
 */
#define BOARD_HANDWIRED_TRACTYL_MANUFORM_5X6_RIGHT_F429
#define BOARD_NAME                  "handwired/tractyl_manuform/5x6_right/f429"

#define BOARD_OTG_NOVBUSSENS

/*
 * Board oscillators-related settings.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                32768U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                25000000U
#endif

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   300U

/*
 * MCU type as defined in the ST header.
 */
#undef STM32F429xx
#define STM32F429xx

/*
 * IO pins assignments.
 */
#define GPIOA_BUTTON                0U
#define GPIOA_MEMS_INT1             1U
#define GPIOA_MEMS_INT2             2U
#define GPIOA_PIN3                3U
#define GPIOA_PIN4             4U
#define GPIOA_PIN5                  5U
#define GPIOA_PIN6                6U
#define GPIOA_ACP_RST               7U
#define GPIOA_I2C3_SCL              8U
#define GPIOA_UART_TX               9U
#define GPIOA_UART_RX               10U
#define GPIOA_PIN11                11U
#define GPIOA_PIN12                12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_TP_INT                15U

#define GPIOB_PIN0                0U
#define GPIOB_PIN1                1U
#define GPIOB_BOOT1                 2U
#define GPIOB_SWO                   3U
#define GPIOB_PIN4                  4U
#define GPIOB_PIN5                  5U
#define GPIOB_PIN6                  6U
#define GPIOB_PIN7                  7U
#define GPIOB_PIN8                8U
#define GPIOB_PIN9                9U
#define GPIOB_PIN10                10U
#define GPIOB_PIN11                11U
#define GPIOB_OTG_HS_ID             12U
#define GPIOB_FMC_NWAIT             13U
#define GPIOB_OTG_HS_DM             14U
#define GPIOB_OTG_HS_DP             15U

#define GPIOC_FMC_SDNWE             0U
#define GPIOC_SPI5_MEMS_CS          1U
#define GPIOC_PIN2                  2U
#define GPIOC_PIN3                  3U
#define GPIOC_OTG_HS_PSO            4U
#define GPIOC_OTG_HS_OC             5U
#define GPIOC_PIN6                  6U
#define GPIOC_PIN7                  7U
#define GPIOC_PIN8                  8U
#define GPIOC_I2C3_SDA              9U
#define GPIOC_PIN10                 10U
#define GPIOC_PIN11                 11U
#define GPIOC_PIN12                 12U
#define GPIOC_PIN13                 13U
#define GPIOC_OSC32_IN              14U
#define GPIOC_OSC32_OUT             15U

#define GPIOD_FMC_D2                0U
#define GPIOD_FMC_D3                1U
#define GPIOD_PIN2                  2U
#define GPIOD_PIN3                  3U
#define GPIOD_FMC_NRE               4U
#define GPIOD_FMC_NWE               5U
#define GPIOD_PIN6                 6U
#define GPIOD_PIN7                  7U
#define GPIOD_FMC_D13               8U
#define GPIOD_FMC_D14               9U
#define GPIOD_FMC_D15               10U
#define GPIOD_FMC_CLE               11U
#define GPIOD_FMC_ALE               12U
#define GPIOD_PIN13               13U
#define GPIOD_FMC_D0                14U
#define GPIOD_FMC_D1                15U

#define GPIOE_FMC_NBL0              0U
#define GPIOE_FMC_NBL1              1U
#define GPIOE_PIN2                  2U
#define GPIOE_PIN3                  3U
#define GPIOE_PIN4                  4U
#define GPIOE_PIN5                  5U
#define GPIOE_PIN6                  6U
#define GPIOE_FMC_D4                7U
#define GPIOE_FMC_D5                8U
#define GPIOE_FMC_D6                9U
#define GPIOE_FMC_D7                10U
#define GPIOE_FMC_D8                11U
#define GPIOE_FMC_D9                12U
#define GPIOE_FMC_D10               13U
#define GPIOE_FMC_D11               14U
#define GPIOE_FMC_D12               15U

#define GPIOF_FMC_A0                0U
#define GPIOF_FMC_A1                1U
#define GPIOF_FMC_A2                2U
#define GPIOF_FMC_A3                3U
#define GPIOF_FMC_A4                4U
#define GPIOF_FMC_A5                5U
#define GPIOF_PIN6                  6U
#define GPIOF_PIN7                  7U
#define GPIOF_SPI5_MISO             8U
#define GPIOF_SPI5_MOSI             9U
#define GPIOF_PIN10                 10U
#define GPIOF_FMC_SDNRAS            11U
#define GPIOF_FMC_A6                12U
#define GPIOF_FMC_A7                13U
#define GPIOF_FMC_A8                14U
#define GPIOF_FMC_A9                15U

#define GPIOG_FMC_A10               0U
#define GPIOG_FMC_A11               1U
#define GPIOG_FMC_A12                  2U
#define GPIOG_PIN3                  3U
#define GPIOG_FMC_BA0               4U
#define GPIOG_FMC_BA1               5U
#define GPIOG_PIN6                6U
#define GPIOG_PIN7               7U
#define GPIOG_FMC_SDCLK             8U
#define GPIOG_FMC_NCE               9U
#define GPIOG_PIN10                10U
#define GPIOG_PIN11                11U
#define GPIOG_PIN12                12U
#define GPIOG_LED3_GREEN            13U
#define GPIOG_LED4_RED              14U
#define GPIOG_FMC_SDNCAS            15U

#define GPIOH_OSC_IN                0U
#define GPIOH_OSC_OUT               1U
#define GPIOH_PIN2                  2U
#define GPIOH_PIN3                  3U
#define GPIOH_PIN4                  4U
#define GPIOH_PIN5                  5U
#define GPIOH_FMC_SDNE1             6U
#define GPIOH_FMC_SDCKE1            7U
#define GPIOH_PIN8                  8U
#define GPIOH_PIN9                  9U
#define GPIOH_PIN10                 10U
#define GPIOH_PIN11                 11U
#define GPIOH_PIN12                 12U
#define GPIOH_PIN13                 13U
#define GPIOH_PIN14                 14U
#define GPIOH_PIN15                 15U

#define GPIOI_PIN0                  0U
#define GPIOI_PIN1                  1U
#define GPIOI_PIN2                  2U
#define GPIOI_PIN3                  3U
#define GPIOI_PIN4                  4U
#define GPIOI_PIN5                  5U
#define GPIOI_PIN6                  6U
#define GPIOI_PIN7                  7U
#define GPIOI_PIN8                  8U
#define GPIOI_PIN9                  9U
#define GPIOI_PIN10                 10U
#define GPIOI_PIN11                 11U
#define GPIOI_PIN12                 12U
#define GPIOI_PIN13                 13U
#define GPIOI_PIN14                 14U
#define GPIOI_PIN15                 15U

/*
 * Tractyl Manuform (5x6) F429 pin aliases.
 * These aliases map keyboard function names to the active MCU pins.
 */
#define GPIOA_MATRIX_ROW1           1U
#define GPIOA_MATRIX_ROW2           2U
#define GPIOA_AUDIO_POWER           3U
#define GPIOA_AUDIO_OUT             4U
#define GPIOA_AUDIO_OUT_ALT         5U
#define GPIOA_MATRIX_ROW5           6U

#define GPIOB_SPI1_SCK_TM           3U
#define GPIOB_SPI1_MISO_TM          4U
#define GPIOB_SPI1_MOSI_TM          5U
#define GPIOB_SPLIT_SERIAL_TX       6U
#define GPIOB_SPLIT_SERIAL_RX       7U
#define GPIOB_I2C1_SCL_TM           8U
#define GPIOB_I2C1_SDA_TM           9U
#define GPIOB_ENCODER_A             10U
#define GPIOB_ENCODER_B             11U
#define GPIOB_USB_DM_FS             14U
#define GPIOB_USB_DP_FS             15U

#define GPIOC_MATRIX_COL4           1U
#define GPIOC_MATRIX_COL5           2U
#define GPIOC_MATRIX_ROW0           3U
#define GPIOC_SPLIT_HAND            4U
#define GPIOC_BACKLIGHT             8U
#define GPIOC_WS2812                9U
#define GPIOC_DISPLAY_CS            10U
#define GPIOC_DISPLAY_DC            11U
#define GPIOC_DISPLAY_RST           12U

#define GPIOE_USER_BUTTON           2U
#define GPIOE_DEBUG_LED             3U

#define GPIOF_MATRIX_COL0           6U
#define GPIOF_MATRIX_COL1           7U
#define GPIOF_MATRIX_COL2           8U
#define GPIOF_MATRIX_COL3           9U

#define GPIOG_FLASH_CS              13U
#define GPIOG_POINTING_CS           14U

#define GPIOH_MATRIX_ROW3           4U
#define GPIOH_MATRIX_ROW4           5U

#define LINE_MATRIX_COL0            PAL_LINE(GPIOF, 6U)
#define LINE_MATRIX_COL1            PAL_LINE(GPIOF, 7U)
#define LINE_MATRIX_COL2            PAL_LINE(GPIOF, 8U)
#define LINE_MATRIX_COL3            PAL_LINE(GPIOF, 9U)
#define LINE_MATRIX_COL4            PAL_LINE(GPIOC, 1U)
#define LINE_MATRIX_COL5            PAL_LINE(GPIOC, 2U)

#define LINE_MATRIX_ROW0            PAL_LINE(GPIOC, 3U)
#define LINE_MATRIX_ROW1            PAL_LINE(GPIOA, 1U)
#define LINE_MATRIX_ROW2            PAL_LINE(GPIOA, 2U)
#define LINE_MATRIX_ROW3            PAL_LINE(GPIOH, 4U)
#define LINE_MATRIX_ROW4            PAL_LINE(GPIOH, 5U)
#define LINE_MATRIX_ROW5            PAL_LINE(GPIOA, 6U)

#define LINE_SPLIT_HAND             PAL_LINE(GPIOC, 4U)
#define LINE_SPLIT_SERIAL_TX        PAL_LINE(GPIOB, 6U)
#define LINE_SPLIT_SERIAL_RX        PAL_LINE(GPIOB, 7U)

#define LINE_I2C1_SCL_TM            PAL_LINE(GPIOB, 8U)
#define LINE_I2C1_SDA_TM            PAL_LINE(GPIOB, 9U)

#define LINE_SPI1_SCK_TM            PAL_LINE(GPIOB, 3U)
#define LINE_SPI1_MISO_TM           PAL_LINE(GPIOB, 4U)
#define LINE_SPI1_MOSI_TM           PAL_LINE(GPIOB, 5U)
#define LINE_FLASH_CS               PAL_LINE(GPIOG, 13U)
#define LINE_POINTING_CS            PAL_LINE(GPIOG, 14U)

#define LINE_WS2812                 PAL_LINE(GPIOC, 9U)
#define LINE_BACKLIGHT              PAL_LINE(GPIOC, 8U)

#define LINE_DISPLAY_CS             PAL_LINE(GPIOC, 10U)
#define LINE_DISPLAY_DC             PAL_LINE(GPIOC, 11U)
#define LINE_DISPLAY_RST            PAL_LINE(GPIOC, 12U)

#define LINE_AUDIO_POWER            PAL_LINE(GPIOA, 3U)
#define LINE_AUDIO_OUT              PAL_LINE(GPIOA, 4U)
#define LINE_AUDIO_OUT_ALT          PAL_LINE(GPIOA, 5U)

#define LINE_ENCODER_A              PAL_LINE(GPIOB, 10U)
#define LINE_ENCODER_B              PAL_LINE(GPIOB, 11U)

#define LINE_USER_BUTTON            PAL_LINE(GPIOE, 2U)
#define LINE_DEBUG_LED              PAL_LINE(GPIOE, 3U)

/*
 * IO lines assignments.
 */
#define LINE_BUTTON                 PAL_LINE(GPIOA, 0U)
#define LINE_MEMS_INT1              PAL_LINE(GPIOA, 1U)
#define LINE_MEMS_INT2              PAL_LINE(GPIOA, 2U)
#define LINE_ACP_RST                PAL_LINE(GPIOA, 7U)
#define LINE_I2C3_SCL               PAL_LINE(GPIOA, 8U)
#define LINE_UART_TX                PAL_LINE(GPIOA, 9U)
#define LINE_UART_RX                PAL_LINE(GPIOA, 10U)
#define LINE_PIN11                 PAL_LINE(GPIOA, 11U)
#define LINE_PIN12                 PAL_LINE(GPIOA, 12U)
#define LINE_SWDIO                  PAL_LINE(GPIOA, 13U)
#define LINE_SWCLK                  PAL_LINE(GPIOA, 14U)
#define LINE_TP_INT                 PAL_LINE(GPIOA, 15U)
#define LINE_BOOT1                  PAL_LINE(GPIOB, 2U)
#define LINE_SWO                    PAL_LINE(GPIOB, 3U)
#define LINE_FMC_SDCKE1             PAL_LINE(GPIOH, 7U)
#define LINE_FMC_SDNE1              PAL_LINE(GPIOH, 6U)
#define LINE_OTG_HS_ID              PAL_LINE(GPIOB, 12U)
#define LINE_FMC_NWAIT              PAL_LINE(GPIOB, 13U)
#define LINE_OTG_HS_DM              PAL_LINE(GPIOB, 14U)
#define LINE_OTG_HS_DP              PAL_LINE(GPIOB, 15U)
#define LINE_FMC_SDNWE              PAL_LINE(GPIOC, 0U)
#define LINE_OTG_HS_PSO             PAL_LINE(GPIOC, 4U)
#define LINE_OTG_HS_OC              PAL_LINE(GPIOC, 5U)
#define LINE_I2C3_SDA               PAL_LINE(GPIOC, 9U)
#define LINE_OSC32_IN               PAL_LINE(GPIOC, 14U)
#define LINE_OSC32_OUT              PAL_LINE(GPIOC, 15U)
#define LINE_FMC_D2                 PAL_LINE(GPIOD, 0U)
#define LINE_FMC_D3                 PAL_LINE(GPIOD, 1U)
#define LINE_FMC_NRE                PAL_LINE(GPIOD, 4U)
#define LINE_FMC_NWE                PAL_LINE(GPIOD, 5U)
#define LINE_FMC_D13                PAL_LINE(GPIOD, 8U)
#define LINE_FMC_D14                PAL_LINE(GPIOD, 9U)
#define LINE_FMC_D15                PAL_LINE(GPIOD, 10U)
#define LINE_FMC_CLE                PAL_LINE(GPIOD, 11U)
#define LINE_FMC_ALE                PAL_LINE(GPIOD, 12U)
#define LINE_FMC_D0                 PAL_LINE(GPIOD, 14U)
#define LINE_FMC_D1                 PAL_LINE(GPIOD, 15U)
#define LINE_FMC_NBL0               PAL_LINE(GPIOE, 0U)
#define LINE_FMC_NBL1               PAL_LINE(GPIOE, 1U)
#define LINE_FMC_D4                 PAL_LINE(GPIOE, 7U)
#define LINE_FMC_D5                 PAL_LINE(GPIOE, 8U)
#define LINE_FMC_D6                 PAL_LINE(GPIOE, 9U)
#define LINE_FMC_D7                 PAL_LINE(GPIOE, 10U)
#define LINE_FMC_D8                 PAL_LINE(GPIOE, 11U)
#define LINE_FMC_D9                 PAL_LINE(GPIOE, 12U)
#define LINE_FMC_D10                PAL_LINE(GPIOE, 13U)
#define LINE_FMC_D11                PAL_LINE(GPIOE, 14U)
#define LINE_FMC_D12                PAL_LINE(GPIOE, 15U)
#define LINE_FMC_A0                 PAL_LINE(GPIOF, 0U)
#define LINE_FMC_A1                 PAL_LINE(GPIOF, 1U)
#define LINE_FMC_A2                 PAL_LINE(GPIOF, 2U)
#define LINE_FMC_A3                 PAL_LINE(GPIOF, 3U)
#define LINE_FMC_A4                 PAL_LINE(GPIOF, 4U)
#define LINE_FMC_A5                 PAL_LINE(GPIOF, 5U)
#define LINE_FMC_SDNRAS             PAL_LINE(GPIOF, 11U)
#define LINE_FMC_A6                 PAL_LINE(GPIOF, 12U)
#define LINE_FMC_A7                 PAL_LINE(GPIOF, 13U)
#define LINE_FMC_A8                 PAL_LINE(GPIOF, 14U)
#define LINE_FMC_A9                 PAL_LINE(GPIOF, 15U)
#define LINE_FMC_A10                PAL_LINE(GPIOG, 0U)
#define LINE_FMC_A11                PAL_LINE(GPIOG, 1U)
#define LINE_FMC_BA0                PAL_LINE(GPIOG, 4U)
#define LINE_FMC_BA1                PAL_LINE(GPIOG, 5U)
#define LINE_FMC_SDCLK              PAL_LINE(GPIOG, 8U)
#define LINE_FMC_NCE                PAL_LINE(GPIOG, 9U)
#define LINE_LED3_GREEN             PAL_LINE(GPIOG, 13U)
#define LINE_LED4_RED               PAL_LINE(GPIOG, 14U)
#define LINE_FMC_SDNCAS             PAL_LINE(GPIOG, 15U)
#define LINE_OSC_IN                 PAL_LINE(GPIOH, 0U)
#define LINE_OSC_OUT                PAL_LINE(GPIOH, 1U)

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 *
 * PA0  - BUTTON                    (input floating).
 * PA1  - MATRIX_ROW1               (input pullup).
 * PA2  - MATRIX_ROW2               (input pullup).
 * PA3  - AUDIO_POWER               (output pushpull).
 * PA4  - AUDIO_OUT                 (analog).
 * PA5  - AUDIO_OUT_ALT             (analog).
 * PA6  - MATRIX_ROW5               (input pullup).
 * PA7  - ACP_RST                   (input pullup).
 * PA8  - I2C3_SCL                  (alternate 4 open-drain).
 * PA9  - UART_TX                   (alternate 7).
 * PA10 - UART_RX                   (alternate 7).
 * PA11 - PIN11                     (input pullup).
 * PA12 - PIN12                     (input pullup).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 * PA15 - TP_INT                    (input floating).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_INPUT(GPIOA_BUTTON) |         \
                                     PIN_MODE_INPUT(GPIOA_MATRIX_ROW1) |    \
                                     PIN_MODE_INPUT(GPIOA_MATRIX_ROW2) |    \
                                     PIN_MODE_OUTPUT(GPIOA_AUDIO_POWER) |   \
                                     PIN_MODE_ANALOG(GPIOA_AUDIO_OUT) |     \
                                     PIN_MODE_ANALOG(GPIOA_AUDIO_OUT_ALT) | \
                                     PIN_MODE_INPUT(GPIOA_MATRIX_ROW5) |    \
                                     PIN_MODE_INPUT(GPIOA_ACP_RST) |        \
                                     PIN_MODE_ALTERNATE(GPIOA_I2C3_SCL) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_UART_TX) |    \
                                     PIN_MODE_ALTERNATE(GPIOA_UART_RX) |    \
                                     PIN_MODE_INPUT(GPIOA_PIN11) |     \
                                     PIN_MODE_INPUT(GPIOA_PIN12) |     \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_INPUT(GPIOA_TP_INT))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_BUTTON) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_MATRIX_ROW1) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_MATRIX_ROW2) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_AUDIO_POWER) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_AUDIO_OUT) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_AUDIO_OUT_ALT) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_MATRIX_ROW5) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_ACP_RST) |    \
                                     PIN_OTYPE_OPENDRAIN(GPIOA_I2C3_SCL) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_UART_TX) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_UART_RX) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN11) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN12) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_TP_INT))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOA_BUTTON) |     \
                                     PIN_OSPEED_VERYLOW(GPIOA_MATRIX_ROW1) |\
                                     PIN_OSPEED_VERYLOW(GPIOA_MATRIX_ROW2) |\
                                     PIN_OSPEED_VERYLOW(GPIOA_AUDIO_POWER) |\
                                     PIN_OSPEED_VERYLOW(GPIOA_AUDIO_OUT) |  \
                                     PIN_OSPEED_VERYLOW(GPIOA_AUDIO_OUT_ALT) |\
                                     PIN_OSPEED_VERYLOW(GPIOA_MATRIX_ROW5) |\
                                     PIN_OSPEED_VERYLOW(GPIOA_ACP_RST) |    \
                                     PIN_OSPEED_HIGH(GPIOA_I2C3_SCL) |      \
                                     PIN_OSPEED_VERYLOW(GPIOA_UART_TX) |    \
                                     PIN_OSPEED_VERYLOW(GPIOA_UART_RX) |    \
                                     PIN_OSPEED_VERYLOW(GPIOA_PIN11) |        \
                                     PIN_OSPEED_VERYLOW(GPIOA_PIN12) |        \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_VERYLOW(GPIOA_TP_INT))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_BUTTON) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_MATRIX_ROW1) |  \
                                     PIN_PUPDR_PULLUP(GPIOA_MATRIX_ROW2) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_AUDIO_POWER) |\
                                     PIN_PUPDR_FLOATING(GPIOA_AUDIO_OUT) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_AUDIO_OUT_ALT) |\
                                     PIN_PUPDR_PULLUP(GPIOA_MATRIX_ROW5) |  \
                                     PIN_PUPDR_PULLUP(GPIOA_ACP_RST) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_I2C3_SCL) |   \
                                     PIN_PUPDR_PULLUP(GPIOA_UART_TX) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_UART_RX) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN11) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN12) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_SWDIO) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_TP_INT))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_BUTTON) |           \
                                     PIN_ODR_HIGH(GPIOA_MATRIX_ROW1) |      \
                                     PIN_ODR_HIGH(GPIOA_MATRIX_ROW2) |      \
                                     PIN_ODR_HIGH(GPIOA_AUDIO_POWER) |      \
                                     PIN_ODR_HIGH(GPIOA_AUDIO_OUT) |        \
                                     PIN_ODR_HIGH(GPIOA_AUDIO_OUT_ALT) |    \
                                     PIN_ODR_HIGH(GPIOA_MATRIX_ROW5) |      \
                                     PIN_ODR_HIGH(GPIOA_ACP_RST) |          \
                                     PIN_ODR_HIGH(GPIOA_I2C3_SCL) |         \
                                     PIN_ODR_HIGH(GPIOA_UART_TX) |          \
                                     PIN_ODR_HIGH(GPIOA_UART_RX) |          \
                                     PIN_ODR_HIGH(GPIOA_PIN11) |           \
                                     PIN_ODR_HIGH(GPIOA_PIN12) |           \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_HIGH(GPIOA_TP_INT))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_BUTTON, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_MATRIX_ROW1, 0U) |   \
                                     PIN_AFIO_AF(GPIOA_MATRIX_ROW2, 0U) |   \
                                     PIN_AFIO_AF(GPIOA_AUDIO_POWER, 0U) |   \
                                     PIN_AFIO_AF(GPIOA_AUDIO_OUT, 0U) |     \
                                     PIN_AFIO_AF(GPIOA_AUDIO_OUT_ALT, 0U) | \
                                     PIN_AFIO_AF(GPIOA_MATRIX_ROW5, 0U) |   \
                                     PIN_AFIO_AF(GPIOA_ACP_RST, 0U))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_I2C3_SCL, 4U) |      \
                                     PIN_AFIO_AF(GPIOA_UART_TX, 7U) |       \
                                     PIN_AFIO_AF(GPIOA_UART_RX, 7U) |       \
                                     PIN_AFIO_AF(GPIOA_PIN11, 0U) |       \
                                     PIN_AFIO_AF(GPIOA_PIN12, 0U) |       \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_TP_INT, 0U))

/*
 * GPIOB setup:
 *
 * PB0  - PIN0                      (input pullup).
 * PB1  - PIN1                      (input pullup).
 * PB2  - BOOT1                     (input pullup).
 * PB3  - SPI1_SCK_TM               (alternate 5).
 * PB4  - SPI1_MISO_TM              (alternate 5).
 * PB5  - SPI1_MOSI_TM              (alternate 5).
 * PB6  - SPLIT_SERIAL_TX           (alternate 7).
 * PB7  - SPLIT_SERIAL_RX           (alternate 7).
 * PB8  - I2C1_SCL_TM               (alternate 4 open-drain).
 * PB9  - I2C1_SDA_TM               (alternate 4 open-drain).
 * PB10 - ENCODER_A                 (input pullup).
 * PB11 - ENCODER_B                 (input pullup).
 * PB12 - OTG_HS_ID                 (alternate 12).
 * PB13 - FMC_NWAIT                 (alternate 12).
 * PB14 - USB_DM_FS                 (alternate 12).
 * PB15 - USB_DP_FS                 (alternate 12).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_INPUT(GPIOB_PIN0) |     \
                                     PIN_MODE_INPUT(GPIOB_PIN1) |     \
                                     PIN_MODE_INPUT(GPIOB_BOOT1) |          \
                                     PIN_MODE_ALTERNATE(GPIOB_SPI1_SCK_TM) |\
                                     PIN_MODE_ALTERNATE(GPIOB_SPI1_MISO_TM) |\
                                     PIN_MODE_ALTERNATE(GPIOB_SPI1_MOSI_TM) |\
                                     PIN_MODE_ALTERNATE(GPIOB_SPLIT_SERIAL_TX) |\
                                     PIN_MODE_ALTERNATE(GPIOB_SPLIT_SERIAL_RX) |\
                                     PIN_MODE_ALTERNATE(GPIOB_I2C1_SCL_TM) |\
                                     PIN_MODE_ALTERNATE(GPIOB_I2C1_SDA_TM) |\
                                     PIN_MODE_INPUT(GPIOB_ENCODER_A) |      \
                                     PIN_MODE_INPUT(GPIOB_ENCODER_B) |      \
                                     PIN_MODE_ALTERNATE(GPIOB_OTG_HS_ID) |  \
                                     PIN_MODE_ALTERNATE(GPIOB_FMC_NWAIT) |  \
                                     PIN_MODE_ALTERNATE(GPIOB_USB_DM_FS) |  \
                                     PIN_MODE_ALTERNATE(GPIOB_USB_DP_FS))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_PIN0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_BOOT1) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SPI1_SCK_TM) |\
                                     PIN_OTYPE_PUSHPULL(GPIOB_SPI1_MISO_TM) |\
                                     PIN_OTYPE_PUSHPULL(GPIOB_SPI1_MOSI_TM) |\
                                     PIN_OTYPE_PUSHPULL(GPIOB_SPLIT_SERIAL_TX) |\
                                     PIN_OTYPE_PUSHPULL(GPIOB_SPLIT_SERIAL_RX) |\
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C1_SCL_TM) |\
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C1_SDA_TM) |\
                                     PIN_OTYPE_PUSHPULL(GPIOB_ENCODER_A) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ENCODER_B) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_OTG_HS_ID) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_FMC_NWAIT) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USB_DM_FS) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USB_DP_FS))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOB_PIN0) |        \
                                     PIN_OSPEED_VERYLOW(GPIOB_PIN1) |        \
                                     PIN_OSPEED_HIGH(GPIOB_BOOT1) |         \
                                     PIN_OSPEED_HIGH(GPIOB_SPI1_SCK_TM) |   \
                                     PIN_OSPEED_HIGH(GPIOB_SPI1_MISO_TM) |  \
                                     PIN_OSPEED_HIGH(GPIOB_SPI1_MOSI_TM) |  \
                                     PIN_OSPEED_HIGH(GPIOB_SPLIT_SERIAL_TX) |\
                                     PIN_OSPEED_HIGH(GPIOB_SPLIT_SERIAL_RX) |\
                                     PIN_OSPEED_HIGH(GPIOB_I2C1_SCL_TM) |   \
                                     PIN_OSPEED_HIGH(GPIOB_I2C1_SDA_TM) |   \
                                     PIN_OSPEED_VERYLOW(GPIOB_ENCODER_A) |  \
                                     PIN_OSPEED_VERYLOW(GPIOB_ENCODER_B) |  \
                                     PIN_OSPEED_HIGH(GPIOB_OTG_HS_ID) |     \
                                     PIN_OSPEED_HIGH(GPIOB_FMC_NWAIT) |     \
                                     PIN_OSPEED_HIGH(GPIOB_USB_DM_FS) |     \
                                     PIN_OSPEED_HIGH(GPIOB_USB_DP_FS))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLUP(GPIOB_PIN0) |     \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN1) |     \
                                     PIN_PUPDR_PULLUP(GPIOB_BOOT1) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_SPI1_SCK_TM) |\
                                     PIN_PUPDR_FLOATING(GPIOB_SPI1_MISO_TM) |\
                                     PIN_PUPDR_FLOATING(GPIOB_SPI1_MOSI_TM) |\
                                     PIN_PUPDR_FLOATING(GPIOB_SPLIT_SERIAL_TX) |\
                                     PIN_PUPDR_FLOATING(GPIOB_SPLIT_SERIAL_RX) |\
                                     PIN_PUPDR_FLOATING(GPIOB_I2C1_SCL_TM) |\
                                     PIN_PUPDR_FLOATING(GPIOB_I2C1_SDA_TM) |\
                                     PIN_PUPDR_PULLUP(GPIOB_ENCODER_A) |    \
                                     PIN_PUPDR_PULLUP(GPIOB_ENCODER_B) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_OTG_HS_ID) |  \
                                     PIN_PUPDR_FLOATING(GPIOB_FMC_NWAIT) |  \
                                     PIN_PUPDR_FLOATING(GPIOB_USB_DM_FS) |  \
                                     PIN_PUPDR_FLOATING(GPIOB_USB_DP_FS))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_PIN0) |           \
                                     PIN_ODR_HIGH(GPIOB_PIN1) |           \
                                     PIN_ODR_HIGH(GPIOB_BOOT1) |            \
                                     PIN_ODR_HIGH(GPIOB_SPI1_SCK_TM) |      \
                                     PIN_ODR_HIGH(GPIOB_SPI1_MISO_TM) |     \
                                     PIN_ODR_HIGH(GPIOB_SPI1_MOSI_TM) |     \
                                     PIN_ODR_HIGH(GPIOB_SPLIT_SERIAL_TX) |  \
                                     PIN_ODR_HIGH(GPIOB_SPLIT_SERIAL_RX) |  \
                                     PIN_ODR_HIGH(GPIOB_I2C1_SCL_TM) |      \
                                     PIN_ODR_HIGH(GPIOB_I2C1_SDA_TM) |      \
                                     PIN_ODR_HIGH(GPIOB_ENCODER_A) |        \
                                     PIN_ODR_HIGH(GPIOB_ENCODER_B) |        \
                                     PIN_ODR_HIGH(GPIOB_OTG_HS_ID) |        \
                                     PIN_ODR_HIGH(GPIOB_FMC_NWAIT) |        \
                                     PIN_ODR_HIGH(GPIOB_USB_DM_FS) |        \
                                     PIN_ODR_HIGH(GPIOB_USB_DP_FS))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_PIN0, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_PIN1, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_BOOT1, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_SPI1_SCK_TM, 5U) |   \
                                     PIN_AFIO_AF(GPIOB_SPI1_MISO_TM, 5U) |  \
                                     PIN_AFIO_AF(GPIOB_SPI1_MOSI_TM, 5U) |  \
                                     PIN_AFIO_AF(GPIOB_SPLIT_SERIAL_TX, 7U) |\
                                     PIN_AFIO_AF(GPIOB_SPLIT_SERIAL_RX, 7U))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_I2C1_SCL_TM, 4U) |   \
                                     PIN_AFIO_AF(GPIOB_I2C1_SDA_TM, 4U) |   \
                                     PIN_AFIO_AF(GPIOB_ENCODER_A, 0U) |     \
                                     PIN_AFIO_AF(GPIOB_ENCODER_B, 0U) |     \
                                     PIN_AFIO_AF(GPIOB_OTG_HS_ID, 12U) |    \
                                     PIN_AFIO_AF(GPIOB_FMC_NWAIT, 12U) |    \
                                     PIN_AFIO_AF(GPIOB_USB_DM_FS, 12U) |    \
                                     PIN_AFIO_AF(GPIOB_USB_DP_FS, 12U))

/*
 * GPIOC setup:
 *
 * PC0  - FMC_SDNWE                 (alternate 12).
 * PC1  - MATRIX_COL4               (input pullup).
 * PC2  - MATRIX_COL5               (input pullup).
 * PC3  - MATRIX_ROW0               (input pullup).
 * PC4  - SPLIT_HAND                (input pullup).
 * PC5  - OTG_HS_OC                 (input floating).
 * PC6  - PIN6                      (input pullup).
 * PC7  - PIN7                      (input pullup).
 * PC8  - BACKLIGHT                 (alternate 3).
 * PC9  - WS2812                    (alternate 3).
 * PC10 - DISPLAY_CS                (output pushpull).
 * PC11 - DISPLAY_DC                (output pushpull).
 * PC12 - DISPLAY_RST               (output pushpull).
 * PC13 - PIN13                     (input pullup).
 * PC14 - OSC32_IN                  (input floating).
 * PC15 - OSC32_OUT                 (input floating).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_ALTERNATE(GPIOC_FMC_SDNWE) |  \
                                     PIN_MODE_INPUT(GPIOC_MATRIX_COL4) |    \
                                     PIN_MODE_INPUT(GPIOC_MATRIX_COL5) |    \
                                     PIN_MODE_INPUT(GPIOC_MATRIX_ROW0) |    \
                                     PIN_MODE_INPUT(GPIOC_SPLIT_HAND) |     \
                                     PIN_MODE_INPUT(GPIOC_OTG_HS_OC) |      \
                                     PIN_MODE_INPUT(GPIOC_PIN6) |  \
                                     PIN_MODE_INPUT(GPIOC_PIN7) |     \
                                     PIN_MODE_ALTERNATE(GPIOC_BACKLIGHT) |  \
                                     PIN_MODE_ALTERNATE(GPIOC_WS2812) |     \
                                     PIN_MODE_OUTPUT(GPIOC_DISPLAY_CS) |    \
                                     PIN_MODE_OUTPUT(GPIOC_DISPLAY_DC) |    \
                                     PIN_MODE_OUTPUT(GPIOC_DISPLAY_RST) |   \
                                     PIN_MODE_INPUT(GPIOC_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOC_OSC32_IN) |       \
                                     PIN_MODE_INPUT(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_FMC_SDNWE) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_MATRIX_COL4) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_MATRIX_COL5) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_MATRIX_ROW0) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_SPLIT_HAND) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OTG_HS_OC) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN6) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_BACKLIGHT) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_WS2812) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_DISPLAY_CS) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_DISPLAY_DC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_DISPLAY_RST) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_IN) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_FMC_SDNWE) |     \
                                     PIN_OSPEED_VERYLOW(GPIOC_MATRIX_COL4) |\
                                     PIN_OSPEED_VERYLOW(GPIOC_MATRIX_COL5) |\
                                     PIN_OSPEED_VERYLOW(GPIOC_MATRIX_ROW0) |\
                                     PIN_OSPEED_VERYLOW(GPIOC_SPLIT_HAND) | \
                                     PIN_OSPEED_HIGH(GPIOC_OTG_HS_OC) |     \
                                     PIN_OSPEED_VERYLOW(GPIOC_PIN6) |     \
                                     PIN_OSPEED_VERYLOW(GPIOC_PIN7) |        \
                                     PIN_OSPEED_HIGH(GPIOC_BACKLIGHT) |     \
                                     PIN_OSPEED_HIGH(GPIOC_WS2812) |        \
                                     PIN_OSPEED_VERYLOW(GPIOC_DISPLAY_CS) | \
                                     PIN_OSPEED_VERYLOW(GPIOC_DISPLAY_DC) | \
                                     PIN_OSPEED_VERYLOW(GPIOC_DISPLAY_RST) |\
                                     PIN_OSPEED_VERYLOW(GPIOC_PIN13) |      \
                                     PIN_OSPEED_HIGH(GPIOC_OSC32_IN) |      \
                                     PIN_OSPEED_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_FLOATING(GPIOC_FMC_SDNWE) |  \
                                     PIN_PUPDR_PULLUP(GPIOC_MATRIX_COL4) |  \
                                     PIN_PUPDR_PULLUP(GPIOC_MATRIX_COL5) |  \
                                     PIN_PUPDR_PULLUP(GPIOC_MATRIX_ROW0) |  \
                                     PIN_PUPDR_PULLUP(GPIOC_SPLIT_HAND) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_OTG_HS_OC) |  \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN6) |  \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN7) |     \
                                     PIN_PUPDR_FLOATING(GPIOC_BACKLIGHT) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_WS2812) |     \
                                     PIN_PUPDR_FLOATING(GPIOC_DISPLAY_CS) | \
                                     PIN_PUPDR_FLOATING(GPIOC_DISPLAY_DC) | \
                                     PIN_PUPDR_FLOATING(GPIOC_DISPLAY_RST) |\
                                     PIN_PUPDR_PULLUP(GPIOC_PIN13) |        \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_IN) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_OUT))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_FMC_SDNWE) |        \
                                     PIN_ODR_HIGH(GPIOC_MATRIX_COL4) |      \
                                     PIN_ODR_HIGH(GPIOC_MATRIX_COL5) |      \
                                     PIN_ODR_HIGH(GPIOC_MATRIX_ROW0) |      \
                                     PIN_ODR_HIGH(GPIOC_SPLIT_HAND) |       \
                                     PIN_ODR_HIGH(GPIOC_OTG_HS_OC) |        \
                                     PIN_ODR_HIGH(GPIOC_PIN6) |        \
                                     PIN_ODR_HIGH(GPIOC_PIN7) |           \
                                     PIN_ODR_HIGH(GPIOC_BACKLIGHT) |        \
                                     PIN_ODR_HIGH(GPIOC_WS2812) |           \
                                     PIN_ODR_HIGH(GPIOC_DISPLAY_CS) |       \
                                     PIN_ODR_HIGH(GPIOC_DISPLAY_DC) |       \
                                     PIN_ODR_HIGH(GPIOC_DISPLAY_RST) |      \
                                     PIN_ODR_HIGH(GPIOC_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOC_OSC32_IN) |         \
                                     PIN_ODR_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_FMC_SDNWE, 12U) |    \
                                     PIN_AFIO_AF(GPIOC_MATRIX_COL4, 0U) |   \
                                     PIN_AFIO_AF(GPIOC_MATRIX_COL5, 0U) |   \
                                     PIN_AFIO_AF(GPIOC_MATRIX_ROW0, 0U) |   \
                                     PIN_AFIO_AF(GPIOC_SPLIT_HAND, 0U) |    \
                                     PIN_AFIO_AF(GPIOC_OTG_HS_OC, 0U) |     \
                                     PIN_AFIO_AF(GPIOC_PIN6, 0U) |    \
                                     PIN_AFIO_AF(GPIOC_PIN7, 0U))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_BACKLIGHT, 3U) |     \
                                     PIN_AFIO_AF(GPIOC_WS2812, 3U) |        \
                                     PIN_AFIO_AF(GPIOC_DISPLAY_CS, 0U) |    \
                                     PIN_AFIO_AF(GPIOC_DISPLAY_DC, 0U) |    \
                                     PIN_AFIO_AF(GPIOC_DISPLAY_RST, 0U) |   \
                                     PIN_AFIO_AF(GPIOC_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_OSC32_IN, 0U) |      \
                                     PIN_AFIO_AF(GPIOC_OSC32_OUT, 0U))

/*
 * GPIOD setup:
 *
 * PD0  - FMC_D2                    (alternate 12).
 * PD1  - FMC_D3                    (alternate 12).
 * PD2  - PIN2                      (input pullup).
 * PD3  - PIN3                      (input pullup).
 * PD4  - FMC_NRE                   (alternate 12).
 * PD5  - FMC_NWE                   (alternate 12).
 * PD6  - PIN6                      (input pullup).
 * PD7  - PIN7                      (input pullup).
 * PD8  - FMC_D13                   (alternate 12).
 * PD9  - FMC_D14                   (alternate 12).
 * PD10 - FMC_D15                   (alternate 12).
 * PD11 - FMC_CLE                   (alternate 12).
 * PD12 - FMC_ALE                   (alternate 12).
 * PD13 - PIN13                     (input pullup).
 * PD14 - FMC_D0                    (alternate 12).
 * PD15 - FMC_D1                    (alternate 12).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_ALTERNATE(GPIOD_FMC_D2) |     \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D3) |     \
                                     PIN_MODE_INPUT(GPIOD_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN3) |     \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_NRE) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_NWE) |    \
                                     PIN_MODE_INPUT(GPIOD_PIN6) |     \
                                     PIN_MODE_INPUT(GPIOD_PIN7) |           \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D13) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D14) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D15) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_CLE) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_ALE) |    \
                                     PIN_MODE_INPUT(GPIOD_PIN13) |       \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D0) |     \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D1))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_FMC_D2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_NRE) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_NWE) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN6) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D13) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D14) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D15) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_CLE) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_ALE) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN13) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D1))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_HIGH(GPIOD_FMC_D2) |        \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D3) |        \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN3) |        \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_NRE) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_NWE) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN6) |        \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN7) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D13) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D14) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D15) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_CLE) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_ALE) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN13) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D0) |        \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D1))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_FLOATING(GPIOD_FMC_D2) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D3) |     \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN3) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_NRE) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_NWE) |    \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN6) |     \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN7) |         \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D13) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D14) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D15) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_CLE) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_ALE) |    \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN13) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D0) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D1))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_FMC_D2) |           \
                                     PIN_ODR_HIGH(GPIOD_FMC_D3) |           \
                                     PIN_ODR_HIGH(GPIOD_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN3) |           \
                                     PIN_ODR_HIGH(GPIOD_FMC_NRE) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_NWE) |          \
                                     PIN_ODR_HIGH(GPIOD_PIN6) |           \
                                     PIN_ODR_HIGH(GPIOD_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOD_FMC_D13) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_D14) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_D15) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_CLE) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_ALE) |          \
                                     PIN_ODR_HIGH(GPIOD_PIN13) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_D0) |           \
                                     PIN_ODR_HIGH(GPIOD_FMC_D1))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_FMC_D2, 12U) |       \
                                     PIN_AFIO_AF(GPIOD_FMC_D3, 12U) |       \
                                     PIN_AFIO_AF(GPIOD_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN3, 0U) |       \
                                     PIN_AFIO_AF(GPIOD_FMC_NRE, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_FMC_NWE, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_PIN6, 0U) |       \
                                     PIN_AFIO_AF(GPIOD_PIN7, 0U))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_FMC_D13, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_FMC_D14, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_FMC_D15, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_FMC_CLE, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_FMC_ALE, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_PIN13, 0U) |       \
                                     PIN_AFIO_AF(GPIOD_FMC_D0, 12U) |       \
                                     PIN_AFIO_AF(GPIOD_FMC_D1, 12U))

/*
 * GPIOE setup:
 *
 * PE0  - FMC_NBL0                  (alternate 12).
 * PE1  - FMC_NBL1                  (alternate 12).
 * PE2  - USER_BUTTON               (input pullup).
 * PE3  - DEBUG_LED                 (output pushpull).
 * PE4  - PIN4                      (input pullup).
 * PE5  - PIN5                      (input pullup).
 * PE6  - PIN6                      (input pullup).
 * PE7  - FMC_D4                    (alternate 12).
 * PE8  - FMC_D5                    (alternate 12).
 * PE9  - FMC_D6                    (alternate 12).
 * PE10 - FMC_D7                    (alternate 12).
 * PE11 - FMC_D8                    (alternate 12).
 * PE12 - FMC_D9                    (alternate 12).
 * PE13 - FMC_D10                   (alternate 12).
 * PE14 - FMC_D11                   (alternate 12).
 * PE15 - FMC_D12                   (alternate 12).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_ALTERNATE(GPIOE_FMC_NBL0) |   \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_NBL1) |   \
                                     PIN_MODE_INPUT(GPIOE_USER_BUTTON) |    \
                                     PIN_MODE_OUTPUT(GPIOE_DEBUG_LED) |     \
                                     PIN_MODE_INPUT(GPIOE_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN6) |           \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D4) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D5) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D6) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D7) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D8) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D9) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D10) |    \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D11) |    \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D12))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_FMC_NBL0) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_NBL1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_USER_BUTTON) |\
                                     PIN_OTYPE_PUSHPULL(GPIOE_DEBUG_LED) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D5) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D6) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D8) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D9) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D10) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D11) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D12))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_HIGH(GPIOE_FMC_NBL0) |      \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_NBL1) |      \
                                     PIN_OSPEED_VERYLOW(GPIOE_USER_BUTTON) |\
                                     PIN_OSPEED_VERYLOW(GPIOE_DEBUG_LED) |  \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN6) |       \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D4) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D5) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D6) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D7) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D8) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D9) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D10) |       \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D11) |       \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D12))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_FLOATING(GPIOE_FMC_NBL0) |   \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_NBL1) |   \
                                     PIN_PUPDR_PULLUP(GPIOE_USER_BUTTON) |  \
                                     PIN_PUPDR_FLOATING(GPIOE_DEBUG_LED) |  \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN6) |         \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D4) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D5) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D6) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D7) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D8) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D9) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D10) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D11) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D12))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_FMC_NBL0) |         \
                                     PIN_ODR_HIGH(GPIOE_FMC_NBL1) |         \
                                     PIN_ODR_HIGH(GPIOE_USER_BUTTON) |      \
                                     PIN_ODR_HIGH(GPIOE_DEBUG_LED) |        \
                                     PIN_ODR_HIGH(GPIOE_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOE_FMC_D4) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D5) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D6) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D7) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D8) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D9) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D10) |          \
                                     PIN_ODR_HIGH(GPIOE_FMC_D11) |          \
                                     PIN_ODR_HIGH(GPIOE_FMC_D12))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_FMC_NBL0, 12U) |     \
                                     PIN_AFIO_AF(GPIOE_FMC_NBL1, 12U) |     \
                                     PIN_AFIO_AF(GPIOE_USER_BUTTON, 0U) |   \
                                     PIN_AFIO_AF(GPIOE_DEBUG_LED, 0U) |     \
                                     PIN_AFIO_AF(GPIOE_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_FMC_D4, 12U))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_FMC_D5, 12U) |       \
                                     PIN_AFIO_AF(GPIOE_FMC_D6, 12U) |       \
                                     PIN_AFIO_AF(GPIOE_FMC_D7, 12U) |       \
                                     PIN_AFIO_AF(GPIOE_FMC_D8, 12U) |       \
                                     PIN_AFIO_AF(GPIOE_FMC_D9, 12U) |       \
                                     PIN_AFIO_AF(GPIOE_FMC_D10, 12U) |      \
                                     PIN_AFIO_AF(GPIOE_FMC_D11, 12U) |      \
                                     PIN_AFIO_AF(GPIOE_FMC_D12, 12U))

/*
 * GPIOF setup:
 *
 * PF0  - FMC_A0                    (alternate 12).
 * PF1  - FMC_A1                    (alternate 12).
 * PF2  - FMC_A2                    (alternate 12).
 * PF3  - FMC_A3                    (alternate 12).
 * PF4  - FMC_A4                    (alternate 12).
 * PF5  - FMC_A5                    (alternate 12).
 * PF6  - MATRIX_COL0               (input pullup).
 * PF7  - MATRIX_COL1               (input pullup).
 * PF8  - MATRIX_COL2               (input pullup).
 * PF9  - MATRIX_COL3               (input pullup).
 * PF10 - PIN10                     (input pullup).
 * PF11 - FMC_SDNRAS                (alternate 12).
 * PF12 - FMC_A6                    (alternate 12).
 * PF13 - FMC_A7                    (alternate 12).
 * PF14 - FMC_A8                    (alternate 12).
 * PF15 - FMC_A9                    (alternate 12).
 */
#define VAL_GPIOF_MODER             (PIN_MODE_ALTERNATE(GPIOF_FMC_A0) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A1) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A2) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A3) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A4) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A5) |     \
                                     PIN_MODE_INPUT(GPIOF_MATRIX_COL0) |    \
                                     PIN_MODE_INPUT(GPIOF_MATRIX_COL1) |    \
                                     PIN_MODE_INPUT(GPIOF_MATRIX_COL2) |    \
                                     PIN_MODE_INPUT(GPIOF_MATRIX_COL3) |    \
                                     PIN_MODE_INPUT(GPIOF_PIN10) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_SDNRAS) | \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A6) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A7) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A8) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A9))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_FMC_A0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A5) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_MATRIX_COL0) |\
                                     PIN_OTYPE_PUSHPULL(GPIOF_MATRIX_COL1) |\
                                     PIN_OTYPE_PUSHPULL(GPIOF_MATRIX_COL2) |\
                                     PIN_OTYPE_PUSHPULL(GPIOF_MATRIX_COL3) |\
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN10) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_SDNRAS) | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A6) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A8) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A9))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_HIGH(GPIOF_FMC_A0) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A1) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A2) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A3) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A4) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A5) |        \
                                     PIN_OSPEED_VERYLOW(GPIOF_MATRIX_COL0) |\
                                     PIN_OSPEED_VERYLOW(GPIOF_MATRIX_COL1) |\
                                     PIN_OSPEED_VERYLOW(GPIOF_MATRIX_COL2) |\
                                     PIN_OSPEED_VERYLOW(GPIOF_MATRIX_COL3) |\
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN10) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_SDNRAS) |    \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A6) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A7) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A8) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A9))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_FLOATING(GPIOF_FMC_A0) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A1) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A2) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A3) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A4) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A5) |     \
                                     PIN_PUPDR_PULLUP(GPIOF_MATRIX_COL0) |  \
                                     PIN_PUPDR_PULLUP(GPIOF_MATRIX_COL1) |  \
                                     PIN_PUPDR_PULLUP(GPIOF_MATRIX_COL2) |  \
                                     PIN_PUPDR_PULLUP(GPIOF_MATRIX_COL3) |  \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN10) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_SDNRAS) | \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A6) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A7) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A8) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A9))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_FMC_A0) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A1) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A2) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A3) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A4) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A5) |           \
                                     PIN_ODR_HIGH(GPIOF_MATRIX_COL0) |      \
                                     PIN_ODR_HIGH(GPIOF_MATRIX_COL1) |      \
                                     PIN_ODR_HIGH(GPIOF_MATRIX_COL2) |      \
                                     PIN_ODR_HIGH(GPIOF_MATRIX_COL3) |      \
                                     PIN_ODR_HIGH(GPIOF_PIN10) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_SDNRAS) |       \
                                     PIN_ODR_HIGH(GPIOF_FMC_A6) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A7) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A8) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A9))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_FMC_A0, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A1, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A2, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A3, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A4, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A5, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_MATRIX_COL0, 0U) |   \
                                     PIN_AFIO_AF(GPIOF_MATRIX_COL1, 0U))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_MATRIX_COL2, 0U) |   \
                                     PIN_AFIO_AF(GPIOF_MATRIX_COL3, 0U) |   \
                                     PIN_AFIO_AF(GPIOF_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_FMC_SDNRAS, 12U) |   \
                                     PIN_AFIO_AF(GPIOF_FMC_A6, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A7, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A8, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A9, 12U))

/*
 * GPIOG setup:
 *
 * PG0  - FMC_A10                   (alternate 12).
 * PG1  - FMC_A11                   (alternate 12).
 * PG2  - FMC_A12                   (alternate 12).
 * PG3  - PIN3                      (input pullup).
 * PG4  - FMC_BA0                   (alternate 12).
 * PG5  - FMC_BA1                   (alternate 12).
 * PG6  - PIN6                      (input pullup).
 * PG7  - PIN7                      (input pullup).
 * PG8  - FMC_SDCLK                 (alternate 12).
 * PG9  - FMC_NCE                   (alternate 12).
 * PG10 - PIN10                     (input pullup).
 * PG11 - PIN11                     (input pullup).
 * PG12 - PIN12                     (input pullup).
 * PG13 - FLASH_CS                  (output pushpull, high).
 * PG14 - POINTING_CS               (output pushpull, high).
 * PG15 - FMC_SDNCAS                (alternate 12).
 */
#define VAL_GPIOG_MODER             (PIN_MODE_ALTERNATE(GPIOG_FMC_A10) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A11) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A12) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN3) |           \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_BA0) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_BA1) |    \
                                     PIN_MODE_INPUT(GPIOG_PIN6) |     \
                                     PIN_MODE_INPUT(GPIOG_PIN7) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_SDCLK) |  \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_NCE) |    \
                                     PIN_MODE_INPUT(GPIOG_PIN10) |     \
                                     PIN_MODE_INPUT(GPIOG_PIN11) |     \
                                     PIN_MODE_INPUT(GPIOG_PIN12) |     \
                                     PIN_MODE_OUTPUT(GPIOG_FLASH_CS) |      \
                                     PIN_MODE_OUTPUT(GPIOG_POINTING_CS) |   \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOG_FMC_A10) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A11) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A12) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_BA0) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_BA1) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN6) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN7) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_SDCLK) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_NCE) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN10) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN11) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN12) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FLASH_CS) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOG_POINTING_CS) |\
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_OSPEEDR           (PIN_OSPEED_HIGH(GPIOG_FMC_A10) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A11) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A12) |       \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN3) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_BA0) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_BA1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN6) |        \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN7) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_SDCLK) |     \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_NCE) |       \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN10) |        \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN11) |        \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN12) |        \
                                     PIN_OSPEED_HIGH(GPIOG_FLASH_CS) |      \
                                     PIN_OSPEED_HIGH(GPIOG_POINTING_CS) |   \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_PUPDR             (PIN_PUPDR_FLOATING(GPIOG_FMC_A10) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A11) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A12) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN3) |         \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_BA0) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_BA1) |    \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN6) |     \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN7) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_SDCLK) |  \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_NCE) |    \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN10) |     \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN11) |     \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN12) |     \
                                     PIN_PUPDR_FLOATING(GPIOG_FLASH_CS) |   \
                                     PIN_PUPDR_FLOATING(GPIOG_POINTING_CS) |\
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_ODR               (PIN_ODR_HIGH(GPIOG_FMC_A10) |          \
                                     PIN_ODR_HIGH(GPIOG_FMC_A11) |          \
                                     PIN_ODR_HIGH(GPIOG_FMC_A12) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOG_FMC_BA0) |          \
                                     PIN_ODR_HIGH(GPIOG_FMC_BA1) |          \
                                     PIN_ODR_HIGH(GPIOG_PIN6) |           \
                                     PIN_ODR_HIGH(GPIOG_PIN7) |          \
                                     PIN_ODR_HIGH(GPIOG_FMC_SDCLK) |        \
                                     PIN_ODR_HIGH(GPIOG_FMC_NCE) |          \
                                     PIN_ODR_HIGH(GPIOG_PIN10) |           \
                                     PIN_ODR_HIGH(GPIOG_PIN11) |           \
                                     PIN_ODR_HIGH(GPIOG_PIN12) |           \
                                     PIN_ODR_HIGH(GPIOG_FLASH_CS) |         \
                                     PIN_ODR_HIGH(GPIOG_POINTING_CS) |      \
                                     PIN_ODR_HIGH(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_AFRL              (PIN_AFIO_AF(GPIOG_FMC_A10, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_FMC_A11, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_FMC_A12, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_FMC_BA0, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_FMC_BA1, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN7, 0U))
#define VAL_GPIOG_AFRH              (PIN_AFIO_AF(GPIOG_FMC_SDCLK, 12U) |    \
                                     PIN_AFIO_AF(GPIOG_FMC_NCE, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_FLASH_CS, 0U) |      \
                                     PIN_AFIO_AF(GPIOG_POINTING_CS, 0U) |   \
                                     PIN_AFIO_AF(GPIOG_FMC_SDNCAS, 12U))

/*
 * GPIOH setup:
 *
 * PH0  - OSC_IN                    (input floating).
 * PH1  - OSC_OUT                   (input floating).
 * PH2  - PIN2                      (input pullup).
 * PH3  - PIN3                      (input pullup).
 * PH4  - MATRIX_ROW3               (input pullup).
 * PH5  - MATRIX_ROW4               (input pullup).
 * PH6  - FMC_SDNE1                 (input pullup).
 * PH7  - FMC_SDCKE1                (input pullup).
 * PH8  - PIN8                      (input pullup).
 * PH9  - PIN9                      (input pullup).
 * PH10 - PIN10                     (input pullup).
 * PH11 - PIN11                     (input pullup).
 * PH12 - PIN12                     (input pullup).
 * PH13 - PIN13                     (input pullup).
 * PH14 - PIN14                     (input pullup).
 * PH15 - PIN15                     (input pullup).
 */
#define VAL_GPIOH_MODER             (PIN_MODE_INPUT(GPIOH_OSC_IN) |         \
                                     PIN_MODE_INPUT(GPIOH_OSC_OUT) |        \
                                     PIN_MODE_INPUT(GPIOH_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOH_MATRIX_ROW3) |    \
                                     PIN_MODE_INPUT(GPIOH_MATRIX_ROW4) |    \
                                     PIN_MODE_ALTERNATE(GPIOH_FMC_SDNE1) |      \
                                     PIN_MODE_ALTERNATE(GPIOH_FMC_SDCKE1) |     \
                                     PIN_MODE_INPUT(GPIOH_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN15))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_OSC_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_OSC_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_MATRIX_ROW3) |\
                                     PIN_OTYPE_PUSHPULL(GPIOH_MATRIX_ROW4) |\
                                     PIN_OTYPE_PUSHPULL(GPIOH_FMC_SDNE1) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOH_FMC_SDCKE1) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN15))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_HIGH(GPIOH_OSC_IN) |        \
                                     PIN_OSPEED_HIGH(GPIOH_OSC_OUT) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_MATRIX_ROW3) |\
                                     PIN_OSPEED_VERYLOW(GPIOH_MATRIX_ROW4) |\
                                     PIN_OSPEED_HIGH(GPIOH_FMC_SDNE1) |  \
                                     PIN_OSPEED_HIGH(GPIOH_FMC_SDCKE1) | \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN14) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN15))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_FLOATING(GPIOH_OSC_IN) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_OSC_OUT) |    \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_MATRIX_ROW3) |  \
                                     PIN_PUPDR_PULLUP(GPIOH_MATRIX_ROW4) |  \
                                     PIN_PUPDR_PULLUP(GPIOH_FMC_SDNE1) |    \
                                     PIN_PUPDR_PULLUP(GPIOH_FMC_SDCKE1) |   \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN15))
#define VAL_GPIOH_ODR               (PIN_ODR_HIGH(GPIOH_OSC_IN) |           \
                                     PIN_ODR_HIGH(GPIOH_OSC_OUT) |          \
                                     PIN_ODR_HIGH(GPIOH_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOH_MATRIX_ROW3) |      \
                                     PIN_ODR_HIGH(GPIOH_MATRIX_ROW4) |      \
                                     PIN_ODR_HIGH(GPIOH_FMC_SDNE1) |        \
                                     PIN_ODR_HIGH(GPIOH_FMC_SDCKE1) |       \
                                     PIN_ODR_HIGH(GPIOH_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN15))
#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_OSC_IN, 0U) |        \
                                     PIN_AFIO_AF(GPIOH_OSC_OUT, 0U) |       \
                                     PIN_AFIO_AF(GPIOH_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_MATRIX_ROW3, 0U) |   \
                                     PIN_AFIO_AF(GPIOH_MATRIX_ROW4, 0U) |   \
                                     PIN_AFIO_AF(GPIOH_FMC_SDNE1, 12U) |     \
                                     PIN_AFIO_AF(GPIOH_FMC_SDCKE1, 12U))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN15, 0U))

/*
 * GPIOI setup:
 *
 * PI0  - PIN0                      (input pullup).
 * PI1  - PIN1                      (input pullup).
 * PI2  - PIN2                      (input pullup).
 * PI3  - PIN3                      (input pullup).
 * PI4  - PIN4                      (input pullup).
 * PI5  - PIN5                      (input pullup).
 * PI6  - PIN6                      (input pullup).
 * PI7  - PIN7                      (input pullup).
 * PI8  - PIN8                      (input pullup).
 * PI9  - PIN9                      (input pullup).
 * PI10 - PIN10                     (input pullup).
 * PI11 - PIN11                     (input pullup).
 * PI12 - PIN12                     (input pullup).
 * PI13 - PIN13                     (input pullup).
 * PI14 - PIN14                     (input pullup).
 * PI15 - PIN15                     (input pullup).
 */
#define VAL_GPIOI_MODER             (PIN_MODE_INPUT(GPIOI_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN15))
#define VAL_GPIOI_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOI_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN15))
#define VAL_GPIOI_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOI_PIN0) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN6) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN14) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN15))
#define VAL_GPIOI_PUPDR             (PIN_PUPDR_PULLUP(GPIOI_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN15))
#define VAL_GPIOI_ODR               (PIN_ODR_HIGH(GPIOI_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_AFRL              (PIN_AFIO_AF(GPIOI_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN7, 0U))
#define VAL_GPIOI_AFRH              (PIN_AFIO_AF(GPIOI_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN15, 0U))

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
