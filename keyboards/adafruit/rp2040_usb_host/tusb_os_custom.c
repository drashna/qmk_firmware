// Copyright 2023 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ch.h"
#include "tusb_os_custom.h"

void osal_task_delay(uint32_t msec) {
    chThdSleepMilliseconds(msec);
}

bool osal_mutex_lock(osal_mutex_t mutex_hdl, uint32_t msec) {
    // Because this function is called from both of thread and ISR contexts,
    // the only way to control coherency is system lock
    chSysLock();
    return true;
}

bool osal_mutex_unlock(osal_mutex_t mutex_hdl) {
    chSysUnlock();
    return true;
}

osal_mutex_t osal_mutex_create(osal_mutex_def_t *mdef) {
    return mdef;
}

/* TU_ATTR_ALWAYS_INLINE static inline bool osal_mutex_delete(osal_mutex_t mutex_hdl) { */
bool osal_mutex_delete(osal_mutex_t mutex_hdl) {
  (void) mutex_hdl;
  return true; // nothing to do
}

#include <stdarg.h>

static char     debug_buffer[(1 << 12)];
static uint32_t write_index = 0;
static uint32_t read_index  = 0;

int tusb_debug_printf(const char *format, ...) {
    va_list va;
    va_start(va, format);

    int ret = 0;
    if (write_index >= read_index) {
        if (read_index == 0) {
            ret = vsnprintf(&debug_buffer[write_index], sizeof(debug_buffer) - write_index - 1, format, va);
        } else {
            ret = vsnprintf(&debug_buffer[write_index], sizeof(debug_buffer) - write_index, format, va);
        }
        write_index = (write_index + ret) & (sizeof(debug_buffer) - 1);
    }

    int32_t maxlen = read_index - write_index - 1;
    if (maxlen > 0) {
        int ret2    = vsnprintf(&debug_buffer[write_index], maxlen, format, va);
        write_index = (write_index + ret2) & (sizeof(debug_buffer) - 1);
        ret += ret2;
    }

    va_end(va);

    return ret;
}

void tusb_print_debug_buffer(void) {
    while (read_index != write_index) {
        printf("%c", debug_buffer[read_index]);
        read_index = (read_index + 1) & (sizeof(debug_buffer) - 1);
    }
}
