/* Copyright 2021 QMK
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include_next <mcuconf.h>

#if HAL_USE_ADC==TRUE
#undef STM32_ADC_USE_ADC1
#define STM32_ADC_USE_ADC1 TRUE
#endif

#if HAL_USE_I2C==TRUE
#undef STM32_I2C_USE_I2C2
#define STM32_I2C_USE_I2C2 TRUE
#endif

#if HAL_USE_SPI==TRUE
#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE
#endif

#ifdef WS2812_PWM
#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3 TRUE
#endif

#ifdef AUDIO_DRIVER_PWM
#undef STM32_PWM_USE_TIM8
#define STM32_PWM_USE_TIM8 TRUE
#endif

#ifdef AUDIO_DRIVER_DAC
#undef STM32_DAC_USE_DAC1_CH1
#define STM32_DAC_USE_DAC1_CH1 TRUE
#undef STM32_DAC_USE_DAC1_CH2
#define STM32_DAC_USE_DAC1_CH2 TRUE

#undef STM32_GPT_USE_TIM6
#define STM32_GPT_USE_TIM6 TRUE
#endif
