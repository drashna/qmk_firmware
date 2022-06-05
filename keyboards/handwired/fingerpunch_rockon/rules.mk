
# Bootloader selection
BOOTLOADER = tinyuf2

WS2812_DRIVER = bitbang

AUDIO_DRIVER = pwm_hardware

DEBOUNCE_TYPE = asym_eager_defer_pk
KEYBOARD_SHARED_EP = yes    # Free up some extra endpoints - needed if console+mouse+extra
