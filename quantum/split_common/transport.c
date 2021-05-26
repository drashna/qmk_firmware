#include <string.h>
#include <stddef.h>

#include "config.h"
#include "matrix.h"
#include "quantum.h"
#include "split_sync.h"

#define ROWS_PER_HAND (MATRIX_ROWS / 2)
#define SYNC_TIMER_OFFSET 2

#ifdef RGBLIGHT_ENABLE
#    include "rgblight.h"
#endif

#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif

#ifdef ENCODER_ENABLE
#    include "encoder.h"
static pin_t encoders_pad[] = ENCODERS_PAD_A;
#    define NUMBER_OF_ENCODERS (sizeof(encoders_pad) / sizeof(pin_t))
#endif

#if defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_SPLIT)
#    include "led_matrix.h"
#endif
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)
#    include "rgb_matrix.h"
#endif

#ifdef SPLIT_HOST_SYNC_ENABLE
void set_split_host_indicators(uint8_t host_leds);
#endif

#if defined(USE_I2C)

#    include "i2c_master.h"
#    include "i2c_slave.h"

typedef struct _I2C_slave_buffer_t {
#    ifndef DISABLE_SYNC_TIMER
    uint32_t sync_timer;
#    endif
#    ifdef SPLIT_TRANSPORT_MIRROR
    matrix_row_t mmatrix[ROWS_PER_HAND];
#    endif
    matrix_row_t smatrix[ROWS_PER_HAND];
#    ifdef SPLIT_MODS_ENABLE
    uint8_t real_mods;
    uint8_t weak_mods;
#        ifndef NO_ACTION_ONESHOT
    uint8_t oneshot_mods;
#        endif
#    endif
#    ifdef BACKLIGHT_ENABLE
    uint8_t backlight_level;
#    endif
#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    rgblight_syncinfo_t rgblight_sync;
#    endif
#    ifdef ENCODER_ENABLE
    uint8_t encoder_state[NUMBER_OF_ENCODERS];
#    endif
#    ifdef WPM_ENABLE
    uint8_t current_wpm;
#    endif
#    if defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_SPLIT)
    led_eeconfig_t led_matrix;
    bool           led_suspend_state;
#    endif
#    if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)
    rgb_config_t rgb_matrix;
    bool         rgb_suspend_state;
#    endif
#    ifdef SPLIT_HOST_SYNC_ENABLE
    uint8_t host_indicators;
#    endif
} I2C_slave_buffer_t;

_Static_assert(sizeof(I2C_slave_buffer_t) <= I2C_SLAVE_QMK_REG_COUNT, "I2C_slave_buffer_t too large for I2C_SLAVE_QMK_REG_COUNT");

static I2C_slave_buffer_t *const i2c_buffer = (I2C_slave_buffer_t *)i2c_slave_reg;

#    define I2C_SYNC_TIME_START offsetof(I2C_slave_buffer_t, sync_timer)
#    define I2C_KEYMAP_MASTER_START offsetof(I2C_slave_buffer_t, mmatrix)
#    define I2C_KEYMAP_SLAVE_START offsetof(I2C_slave_buffer_t, smatrix)
#    define I2C_REAL_MODS_START offsetof(I2C_slave_buffer_t, real_mods)
#    define I2C_WEAK_MODS_START offsetof(I2C_slave_buffer_t, weak_mods)
#    define I2C_ONESHOT_MODS_START offsetof(I2C_slave_buffer_t, oneshot_mods)
#    define I2C_BACKLIGHT_START offsetof(I2C_slave_buffer_t, backlight_level)
#    define I2C_RGB_START offsetof(I2C_slave_buffer_t, rgblight_sync)
#    define I2C_ENCODER_START offsetof(I2C_slave_buffer_t, encoder_state)
#    define I2C_WPM_START offsetof(I2C_slave_buffer_t, current_wpm)
#    define I2C_LED_MATRIX_START offsetof(I2C_slave_buffer_t, led_matrix)
#    define I2C_LED_SUSPEND_START offsetof(I2C_slave_buffer_t, led_suspend_state)
#    define I2C_RGB_MATRIX_START offsetof(I2C_slave_buffer_t, rgb_matrix)
#    define I2C_RGB_SUSPEND_START offsetof(I2C_slave_buffer_t, rgb_suspend_state)
#    define I2C_HOST_INDICATORS_START offsetof(I2C_slave_buffer_t, host_indicators)

#    define TIMEOUT 100

#    ifndef SLAVE_I2C_ADDRESS
#        define SLAVE_I2C_ADDRESS 0x32
#    endif

#    ifdef SERIAL_USE_MULTI_TRANSACTION
struct extra_transaction {
    enum split_transaction_id id;
    uint16_t                  offset;
    uint8_t                   initiator2target_buffer_size;
    void *                    initiator2target_buffer;
    uint8_t                   target2initiator_buffer_size;
    void *                    target2initiator_buffer;
} extra_transactions[(SPLIT_NUM_TRANSACTIONS_KB) + (SPLIT_NUM_TRANSACTIONS_USER)] = {0};

static uint16_t next_transaction_offset = sizeof(I2C_slave_buffer_t);

void split_sync_register_transaction(enum split_transaction_id id, uint8_t initiator2target_buffer_size, void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    int max_idx = (SPLIT_NUM_TRANSACTIONS_KB) + (SPLIT_NUM_TRANSACTIONS_USER);
    for (int i = 0; i < max_idx; ++i) {
        struct extra_transaction *trans = &extra_transactions[i];
        if (trans->offset == 0) {
            trans->id                           = id;
            trans->offset                       = next_transaction_offset;
            trans->initiator2target_buffer_size = initiator2target_buffer_size;
            trans->initiator2target_buffer      = initiator2target_buffer;
            trans->target2initiator_buffer_size = target2initiator_buffer_size;
            trans->target2initiator_buffer      = target2initiator_buffer;

            next_transaction_offset += initiator2target_buffer_size + target2initiator_buffer_size;
            break;
        }
    }
}

bool split_sync_execute_transaction(enum split_transaction_id id) {
    int max_idx = (SPLIT_NUM_TRANSACTIONS_KB) + (SPLIT_NUM_TRANSACTIONS_USER);
    for (int i = 0; i < max_idx; ++i) {
        struct extra_transaction *trans = &extra_transactions[i];
        if (trans->id == id) {
            if (trans->initiator2target_buffer_size) {
                uint16_t initiator2target_offset = trans->offset;
                i2c_writeReg(SLAVE_I2C_ADDRESS, initiator2target_offset, trans->initiator2target_buffer, trans->initiator2target_buffer_size, TIMEOUT);
            }
            if (trans->target2initiator_buffer_size) {
                uint16_t target2initiator_offset = trans->offset + trans->initiator2target_buffer_size;
                i2c_readReg(SLAVE_I2C_ADDRESS, target2initiator_offset, trans->target2initiator_buffer, trans->target2initiator_buffer_size, TIMEOUT);
            }
            return true;
        }
    }
    return false;
}

static void split_sync_execute_slave(void) {
    int max_idx = (SPLIT_NUM_TRANSACTIONS_KB) + (SPLIT_NUM_TRANSACTIONS_USER);
    for (int i = 0; i < max_idx; ++i) {
        struct extra_transaction *trans = &extra_transactions[i];
        if (trans->offset != 0) {
            if (trans->initiator2target_buffer_size) {
                uint16_t initiator2target_offset = trans->offset;
                memcpy(trans->initiator2target_buffer, (void *)&i2c_slave_reg[initiator2target_offset], trans->initiator2target_buffer_size);
            }
            if (trans->target2initiator_buffer_size) {
                uint16_t target2initiator_offset = trans->offset + trans->initiator2target_buffer_size;
                memcpy((void *)&i2c_slave_reg[target2initiator_offset], trans->target2initiator_buffer, trans->target2initiator_buffer_size);
            }
        }
    }
}
#    endif  // SERIAL_USE_MULTI_TRANSACTION

// Get rows from other half over i2c
bool transport_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    i2c_readReg(SLAVE_I2C_ADDRESS, I2C_KEYMAP_SLAVE_START, (void *)slave_matrix, sizeof(i2c_buffer->smatrix), TIMEOUT);
#    ifdef SPLIT_TRANSPORT_MIRROR
    i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_KEYMAP_MASTER_START, (void *)master_matrix, sizeof(i2c_buffer->mmatrix), TIMEOUT);
#    endif

    // write backlight info
#    ifdef BACKLIGHT_ENABLE
    uint8_t level = is_backlight_enabled() ? get_backlight_level() : 0;
    if (level != i2c_buffer->backlight_level) {
        if (i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_BACKLIGHT_START, (void *)&level, sizeof(level), TIMEOUT) >= 0) {
            i2c_buffer->backlight_level = level;
        }
    }
#    endif

#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    if (rgblight_get_change_flags()) {
        rgblight_syncinfo_t rgblight_sync;
        rgblight_get_syncinfo(&rgblight_sync);
        if (i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_RGB_START, (void *)&rgblight_sync, sizeof(rgblight_sync), TIMEOUT) >= 0) {
            rgblight_clear_change_flags();
        }
    }
#    endif

#    ifdef ENCODER_ENABLE
    i2c_readReg(SLAVE_I2C_ADDRESS, I2C_ENCODER_START, (void *)i2c_buffer->encoder_state, sizeof(i2c_buffer->encoder_state), TIMEOUT);
    encoder_update_raw(i2c_buffer->encoder_state);
#    endif

#    ifdef WPM_ENABLE
    uint8_t current_wpm = get_current_wpm();
    if (current_wpm != i2c_buffer->current_wpm) {
        if (i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_WPM_START, (void *)&current_wpm, sizeof(current_wpm), TIMEOUT) >= 0) {
            i2c_buffer->current_wpm = current_wpm;
        }
    }
#    endif

#    ifdef SPLIT_HOST_SYNC_ENABLE
    uint8_t host_indicators = host_keyboard_leds();
    set_split_host_indicators(host_indicators);
    if (i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_HOST_LED_START, (void *)&host_indicators, sizeof(host_indicators), TIMEOUT) >= 0) {
        i2c_buffer->host_indicators = host_indicators;
    }
#    endif

#    ifdef SPLIT_MODS_ENABLE
    uint8_t real_mods = get_mods();
    if (real_mods != i2c_buffer->real_mods) {
        if (i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_REAL_MODS_START, (void *)&real_mods, sizeof(real_mods), TIMEOUT) >= 0) {
            i2c_buffer->real_mods = real_mods;
        }
    }

    uint8_t weak_mods = get_weak_mods();
    if (weak_mods != i2c_buffer->weak_mods) {
        if (i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_WEAK_MODS_START, (void *)&weak_mods, sizeof(weak_mods), TIMEOUT) >= 0) {
            i2c_buffer->weak_mods = weak_mods;
        }
    }

#        ifndef NO_ACTION_ONESHOT
    uint8_t oneshot_mods = get_oneshot_mods();
    if (oneshot_mods != i2c_buffer->oneshot_mods) {
        if (i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_ONESHOT_MODS_START, (void *)&oneshot_mods, sizeof(oneshot_mods), TIMEOUT) >= 0) {
            i2c_buffer->oneshot_mods = oneshot_mods;
        }
    }
#        endif
#    endif

#    if defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_SPLIT)
    i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_LED_MATRIX_START, (void *)led_matrix_eeconfig, sizeof(i2c_buffer->led_matrix), TIMEOUT);
    bool suspend_state = led_matrix_get_suspend_state();
    i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_LED_SUSPEND_START, (void *)suspend_state, sizeof(i2c_buffer->led_suspend_state), TIMEOUT);
#    endif
#    if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)
    i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_RGB_MATRIX_START, (void *)rgb_matrix_config, sizeof(i2c_buffer->rgb_matrix), TIMEOUT);
    bool suspend_state = rgb_matrix_get_suspend_state();
    i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_RGB_SUSPEND_START, (void *)suspend_state, sizeof(i2c_buffer->rgb_suspend_state), TIMEOUT);
#    endif

#    ifndef DISABLE_SYNC_TIMER
    i2c_buffer->sync_timer = sync_timer_read32() + SYNC_TIMER_OFFSET;
    i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_SYNC_TIME_START, (void *)&i2c_buffer->sync_timer, sizeof(i2c_buffer->sync_timer), TIMEOUT);
#    endif

    return true;
}

void transport_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
#    ifndef DISABLE_SYNC_TIMER
    sync_timer_update(i2c_buffer->sync_timer);
#    endif
    // Copy matrix to I2C buffer
    memcpy((void *)i2c_buffer->smatrix, (void *)slave_matrix, sizeof(i2c_buffer->smatrix));
#    ifdef SPLIT_TRANSPORT_MIRROR
    memcpy((void *)master_matrix, (void *)i2c_buffer->mmatrix, sizeof(i2c_buffer->mmatrix));
#    endif

// Read Backlight Info
#    ifdef BACKLIGHT_ENABLE
    backlight_set(i2c_buffer->backlight_level);
#    endif

#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    // Update the RGB with the new data
    if (i2c_buffer->rgblight_sync.status.change_flags != 0) {
        rgblight_update_sync(&i2c_buffer->rgblight_sync, false);
        i2c_buffer->rgblight_sync.status.change_flags = 0;
    }
#    endif

#    ifdef ENCODER_ENABLE
    encoder_state_raw(i2c_buffer->encoder_state);
#    endif

#    ifdef WPM_ENABLE
    set_current_wpm(i2c_buffer->current_wpm);
#    endif

#    ifdef SPLIT_HOST_SYNC_ENABLE
    set_split_host_indicators(i2c_buffer->host_indicators);
#    endif

#    ifdef SPLIT_MODS_ENABLE
    set_mods(i2c_buffer->real_mods);
    set_weak_mods(i2c_buffer->weak_mods);
#        ifndef NO_ACTION_ONESHOT
    set_oneshot_mods(i2c_buffer->oneshot_mods);
#        endif
#    endif

#    if defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_SPLIT)
    memcpy((void *)i2c_buffer->led_matrix, (void *)led_matrix_eeconfig, sizeof(i2c_buffer->led_matrix));
    led_matrix_set_suspend_state(i2c_buffer->led_suspend_state);
#    endif
#    if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)
    memcpy((void *)i2c_buffer->rgb_matrix, (void *)rgb_matrix_config, sizeof(i2c_buffer->rgb_matrix));
    rgb_matrix_set_suspend_state(i2c_buffer->rgb_suspend_state);
#    endif

#    ifdef SERIAL_USE_MULTI_TRANSACTION
    split_sync_execute_slave();
#    endif  // SERIAL_USE_MULTI_TRANSACTION
}

void transport_master_init(void) { i2c_init(); }

void transport_slave_init(void) { i2c_slave_init(SLAVE_I2C_ADDRESS); }

#else  // USE_SERIAL

#    include "serial.h"

typedef struct _Serial_s2m_buffer_t {
    // TODO: if MATRIX_COLS > 8 change to uint8_t packed_matrix[] for pack/unpack
    matrix_row_t smatrix[ROWS_PER_HAND];

#    ifdef ENCODER_ENABLE
    uint8_t encoder_state[NUMBER_OF_ENCODERS];
#    endif

} Serial_s2m_buffer_t;

typedef struct _Serial_m2s_buffer_t {
#    ifdef SPLIT_MODS_ENABLE
    uint8_t real_mods;
    uint8_t weak_mods;
#        ifndef NO_ACTION_ONESHOT
    uint8_t oneshot_mods;
#        endif
#    endif
#    ifndef DISABLE_SYNC_TIMER
    uint32_t sync_timer;
#    endif
#    ifdef SPLIT_TRANSPORT_MIRROR
    matrix_row_t mmatrix[ROWS_PER_HAND];
#    endif
#    ifdef BACKLIGHT_ENABLE
    uint8_t backlight_level;
#    endif
#    ifdef WPM_ENABLE
    uint8_t current_wpm;
#    endif
#    if defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_SPLIT)
    led_eeconfig_t led_matrix;
    bool           led_suspend_state;
#    endif
#    if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)
    rgb_config_t rgb_matrix;
    bool         rgb_suspend_state;
#    endif
    uint8_t      host_indicators;
} Serial_m2s_buffer_t;

#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
// When MCUs on both sides drive their respective RGB LED chains,
// it is necessary to synchronize, so it is necessary to communicate RGB
// information. In that case, define RGBLIGHT_SPLIT with info on the number
// of LEDs on each half.
//
// Otherwise, if the master side MCU drives both sides RGB LED chains,
// there is no need to communicate.

typedef struct _Serial_rgblight_t {
    rgblight_syncinfo_t rgblight_sync;
} Serial_rgblight_t;

volatile Serial_rgblight_t serial_rgblight = {};
uint8_t volatile status_rgblight           = 0;
#    endif

volatile Serial_s2m_buffer_t serial_s2m_buffer = {};
volatile Serial_m2s_buffer_t serial_m2s_buffer = {};
uint8_t volatile status0                       = 0;

enum serial_transaction_id {
    GET_SLAVE_MATRIX = 0,
#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    PUT_RGBLIGHT,
#    endif

    // Totals
    NUM_SERIAL_TRANSACTIONS,
    NUM_TOTAL_TRANSACTIONS = NUM_SERIAL_TRANSACTIONS + NUM_SPLIT_TRANSACTIONS
};

SSTD_t transactions[NUM_TOTAL_TRANSACTIONS] = {
    [0 ...(NUM_TOTAL_TRANSACTIONS - 1)] = {NULL, 0, NULL, 0, NULL},
    [GET_SLAVE_MATRIX] =
        {
            (uint8_t *)&status0,
            sizeof(serial_m2s_buffer),
            (uint8_t *)&serial_m2s_buffer,
            sizeof(serial_s2m_buffer),
            (uint8_t *)&serial_s2m_buffer,
        },
#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    [PUT_RGBLIGHT] =
        {
            (uint8_t *)&status_rgblight, sizeof(serial_rgblight), (uint8_t *)&serial_rgblight, 0, NULL  // no slave to master transfer
        },
#    endif
};

#if defined(SERIAL_USE_MULTI_TRANSACTION) && ( defined(SPLIT_NUM_TRANSACTIONS_KB) || defined(SPLIT_NUM_TRANSACTIONS_USER))
void split_sync_register_transaction(enum split_transaction_id id, uint8_t initiator2target_buffer_size, void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    static uint8_t dummy;
    SSTD_t *       trans                = &transactions[NUM_SERIAL_TRANSACTIONS + id];
    trans->status                       = &dummy;
    trans->initiator2target_buffer_size = initiator2target_buffer_size;
    trans->initiator2target_buffer      = (uint8_t *)initiator2target_buffer;
    trans->target2initiator_buffer_size = target2initiator_buffer_size;
    trans->target2initiator_buffer      = (uint8_t *)target2initiator_buffer;
}

bool split_sync_execute_transaction(enum split_transaction_id id) { return soft_serial_transaction(NUM_SERIAL_TRANSACTIONS + id) == TRANSACTION_END; }
#    endif  // SERIAL_USE_MULTI_TRANSACTION

void transport_master_init(void) { soft_serial_initiator_init(transactions, TID_LIMIT(transactions)); }

void transport_slave_init(void) { soft_serial_target_init(transactions, TID_LIMIT(transactions)); }

#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)

// rgblight synchronization information communication.

void transport_rgblight_master(void) {
    if (rgblight_get_change_flags()) {
        rgblight_get_syncinfo((rgblight_syncinfo_t *)&serial_rgblight.rgblight_sync);
        if (soft_serial_transaction(PUT_RGBLIGHT) == TRANSACTION_END) {
            rgblight_clear_change_flags();
        }
    }
}

void transport_rgblight_slave(void) {
    if (status_rgblight == TRANSACTION_ACCEPTED) {
        rgblight_update_sync((rgblight_syncinfo_t *)&serial_rgblight.rgblight_sync, false);
        status_rgblight = TRANSACTION_END;
    }
}

#    else
#        define transport_rgblight_master()
#        define transport_rgblight_slave()
#    endif

bool transport_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
#    ifndef SERIAL_USE_MULTI_TRANSACTION
    if (soft_serial_transaction() != TRANSACTION_END) {
        return false;
    }
#    else
    transport_rgblight_master();
    if (soft_serial_transaction(GET_SLAVE_MATRIX) != TRANSACTION_END) {
        return false;
    }
#    endif

    // TODO:  if MATRIX_COLS > 8 change to unpack()
    for (int i = 0; i < ROWS_PER_HAND; ++i) {
        slave_matrix[i] = serial_s2m_buffer.smatrix[i];
#    ifdef SPLIT_TRANSPORT_MIRROR
        serial_m2s_buffer.mmatrix[i] = master_matrix[i];
#    endif
    }

#    ifdef BACKLIGHT_ENABLE
    // Write backlight level for slave to read
    serial_m2s_buffer.backlight_level = is_backlight_enabled() ? get_backlight_level() : 0;
#    endif

#    ifdef ENCODER_ENABLE
    encoder_update_raw((uint8_t *)serial_s2m_buffer.encoder_state);
#    endif

#    ifdef WPM_ENABLE
    // Write wpm to slave
    serial_m2s_buffer.current_wpm = get_current_wpm();
#    endif

#    ifdef SPLIT_MODS_ENABLE
    serial_m2s_buffer.real_mods = get_mods();
    serial_m2s_buffer.weak_mods = get_weak_mods();
#        ifndef NO_ACTION_ONESHOT
    serial_m2s_buffer.oneshot_mods = get_oneshot_mods();
#        endif
#    endif

#    if defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_SPLIT)
    serial_m2s_buffer.led_matrix        = led_matrix_eeconfig;
    serial_m2s_buffer.led_suspend_state = led_matrix_get_suspend_state();
#    endif
#    if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)
    serial_m2s_buffer.rgb_matrix        = rgb_matrix_config;
    serial_m2s_buffer.rgb_suspend_state = rgb_matrix_get_suspend_state();
#    endif

#    ifndef DISABLE_SYNC_TIMER
    serial_m2s_buffer.sync_timer = sync_timer_read32() + SYNC_TIMER_OFFSET;
#    endif

#    ifdef SPLIT_HOST_SYNC_ENABLE
    serial_m2s_buffer.host_indicators = host_keyboard_leds_raw();
    set_split_host_indicators(serial_m2s_buffer.host_indicators);
#    endif

    return true;
}

void transport_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    transport_rgblight_slave();
#    ifndef DISABLE_SYNC_TIMER
    sync_timer_update(serial_m2s_buffer.sync_timer);
#    endif

    // TODO: if MATRIX_COLS > 8 change to pack()
    for (int i = 0; i < ROWS_PER_HAND; ++i) {
        serial_s2m_buffer.smatrix[i] = slave_matrix[i];
#    ifdef SPLIT_TRANSPORT_MIRROR
        master_matrix[i] = serial_m2s_buffer.mmatrix[i];
#    endif
    }
#    ifdef BACKLIGHT_ENABLE
    backlight_set(serial_m2s_buffer.backlight_level);
#    endif

#    ifdef ENCODER_ENABLE
    encoder_state_raw((uint8_t *)serial_s2m_buffer.encoder_state);
#    endif

#    ifdef WPM_ENABLE
    set_current_wpm(serial_m2s_buffer.current_wpm);
#    endif

#    ifdef SPLIT_HOST_SYNC_ENABLE
    set_split_host_indicators(serial_m2s_buffer.host_indicators);
#    endif

#    ifdef SPLIT_MODS_ENABLE
    set_mods(serial_m2s_buffer.real_mods);
    set_weak_mods(serial_m2s_buffer.weak_mods);
#        ifndef NO_ACTION_ONESHOT
    set_oneshot_mods(serial_m2s_buffer.oneshot_mods);
#        endif
#    endif

#    if defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_SPLIT)
    led_matrix_eeconfig = serial_m2s_buffer.led_matrix;
    led_matrix_set_suspend_state(serial_m2s_buffer.led_suspend_state);
#    endif
#    if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)
    rgb_matrix_config = serial_m2s_buffer.rgb_matrix;
    rgb_matrix_set_suspend_state(serial_m2s_buffer.rgb_suspend_state);
#    endif
}

#endif
