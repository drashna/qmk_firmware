// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef RP_PWM_USE_PWM4
#define RP_PWM_USE_PWM4 TRUE

#undef RP_PWM_USE_PWM6
#define RP_PWM_USE_PWM6 TRUE

#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE

#define RP_IRQ_RTC_PRIORITY 3
