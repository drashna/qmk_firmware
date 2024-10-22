// Copyright 2024 Sergey Vlasov (@sigprof)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <board.h>

#undef STM32_HSECLK
#define STM32_HSECLK 8000000

#define BOARD_OTG2_USES_ULPI
