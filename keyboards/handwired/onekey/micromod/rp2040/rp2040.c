#include "quantum.h"

void keyboard_pre_init_kb(void) {
    setPinOutput(GP25);
    writePinLow(GP25);

    keyboard_pre_init_user();
}
