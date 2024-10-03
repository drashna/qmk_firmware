// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef STM32_ADC_USE_ADC1
#define STM32_ADC_USE_ADC1 TRUE

#undef STM32_PWM_USE_TIM4
#define STM32_PWM_USE_TIM4 TRUE

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE

#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE

#undef STM32_LSE_ENABLED
#define STM32_LSE_ENABLED TRUE

#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE 4
#undef STM32_PLLN_VALUE
#define STM32_PLLN_VALUE 168
#undef STM32_PLLP_VALUE
#define STM32_PLLP_VALUE 2
#undef STM32_PLLQ_VALUE
#define STM32_PLLQ_VALUE 7

#undef STM32_RTCSEL
#define STM32_RTCSEL STM32_RTCSEL_LSE

#undef STM32_MCO1SEL
#define STM32_MCO1SEL                       STM32_MCO1SEL_HSE

#undef STM32_HSI_ENABLED
#define STM32_HSI_ENABLED                   FALSE
#undef STM32_LSI_ENABLED
#define STM32_LSI_ENABLED                   FALSE
