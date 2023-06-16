#include "quantum.h"

void keyboard_pre_init_kb(void) {
    setPinOutput(A15);
    writePinLow(A15);

    keyboard_pre_init_user();
}
