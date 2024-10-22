// Copyright 2024 Sergey Vlasov (@sigprof)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE 8

#undef STM32_USB_USE_OTG1
#define STM32_USB_USE_OTG1 FALSE

#undef STM32_USB_USE_OTG2
#define STM32_USB_USE_OTG2 TRUE

#undef STM32_USE_USB_OTG2_HS
#define STM32_USE_USB_OTG2_HS TRUE
