#include "quantum.h"

void keyboard_post_init_kb(void) {
    gpio_set_pin_output(C1);
    gpio_write_pin_low(C1);
    keyboard_post_init_user();
}
