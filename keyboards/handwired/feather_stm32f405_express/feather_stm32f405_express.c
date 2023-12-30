#include "quantum.h"

void keyboard_post_init_kb(void) {
    setPinOutput(C1);
    writePinLow(C1);
    keyboard_post_init_user();
}
