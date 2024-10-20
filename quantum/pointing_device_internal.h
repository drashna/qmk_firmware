// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef POINTING_DEVICE_DEBUG
#    include "debug.h"
#    include "print.h"
#    define pd_dprintf(fmt, ...)                                     \
        do {                                                      \
            if (debug_config.pointing) xprintf(fmt, ##__VA_ARGS__); \
        } while (0)
#else
#    define pd_dprintf(...) \
        do {                \
        } while (0)
#endif
