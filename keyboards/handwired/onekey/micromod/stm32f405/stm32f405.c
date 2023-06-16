#include "quantum.h"

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(A15);
    gpio_write_pin_low(A15);

    keyboard_pre_init_user();
}
