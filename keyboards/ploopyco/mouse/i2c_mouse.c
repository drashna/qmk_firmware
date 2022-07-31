#include "i2c_mouse.h"
#include "usb_util.h"
#include "wait.h"
#include "timer.h"
#include "host.h"

#ifndef SLAVE_I2C_TIMEOUT
#    define SLAVE_I2C_TIMEOUT 100
#endif // SLAVE_I2C_TIMEOUT

#ifndef SLAVE_I2C_ADDRESS
#    define SLAVE_I2C_ADDRESS 0x3F
#endif

#ifndef SPLIT_USB_TIMEOUT
#    define SPLIT_USB_TIMEOUT 2000
#endif

#ifndef SPLIT_USB_TIMEOUT_POLL
#    define SPLIT_USB_TIMEOUT_POLL 10
#endif

// Max number of consecutive failed communications (one per scan cycle) before the communication is seen as disconnected.
// Set to 0 to disable the disconnection check altogether.
#ifndef SPLIT_MAX_CONNECTION_ERRORS
#    define SPLIT_MAX_CONNECTION_ERRORS 10
#endif // SPLIT_MAX_CONNECTION_ERRORS

// How long (in milliseconds) to block all connection attempts after the communication has been flagged as disconnected.
// One communication attempt will be allowed everytime this amount of time has passed since the last attempt. If that attempt succeeds, the communication is seen as working again.
// Set to 0 to disable communication throttling while disconnected
#ifndef SPLIT_CONNECTION_CHECK_TIMEOUT
#    define SPLIT_CONNECTION_CHECK_TIMEOUT 500
#endif // SPLIT_CONNECTION_CHECK_TIMEOUT

_Static_assert((SPLIT_USB_TIMEOUT / SPLIT_USB_TIMEOUT_POLL) <= UINT16_MAX, "Please lower SPLIT_USB_TIMEOUT and/or increase SPLIT_USB_TIMEOUT_POLL.");
static bool usbIsActive(void) {
    for (uint16_t i = 0; i < (SPLIT_USB_TIMEOUT / SPLIT_USB_TIMEOUT_POLL); i++) {
        // This will return true if a USB connection has been established
        if (usb_connected_state()) {
            return true;
        }
        wait_ms(SPLIT_USB_TIMEOUT_POLL);
    }
    return false;
}

bool is_keyboard_master(void) {
    static enum { UNKNOWN, MASTER, SLAVE } usbstate = UNKNOWN;

    // only check once, as this is called often
    if (usbstate == UNKNOWN) {
        usbstate = usbIsActive() ? MASTER : SLAVE;

        // Avoid NO_USB_STARTUP_CHECK - Disable USB as the previous checks seem to enable it somehow
        if (usbstate == SLAVE) {
            usb_disconnect();
        }
    }

    return (usbstate == MASTER);
}

void i2c_mouse_init(void) {
    host_set_driver(0);
    i2c_slave_init(SLAVE_I2C_ADDRESS);
}
