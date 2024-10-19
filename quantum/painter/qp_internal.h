// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "qp.h"
#include "util.h" // PACKED/MIN/MAX

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helpers

#ifdef QUANTUM_PAINTER_DEBUG
#    include <debug.h>
#    include <print.h>
#    define qp_dprintf(fmt, ...)                                     \
        do {                                                      \
            if (debug_config.quantum_painter) xprintf(fmt, ##__VA_ARGS__); \
        } while (0)
#else
#    define qp_dprintf(...) \
        do {                \
        } while (0)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Specific internal definitions

#include <qp_internal_formats.h>
#include <qp_internal_driver.h>
