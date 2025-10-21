SRC += matrix.c c1_main.c c1_usbh.c tusb_os_custom.c
CUSTOM_MATRIX = lite
POINTING_DEVICE_DRIVER = custom

SRC += lib/Pico-PIO-USB/src/pio_usb.c
SRC += lib/Pico-PIO-USB/src/pio_usb_host.c
SRC += lib/Pico-PIO-USB/src/usb_crc.c
VPATH += keyboards/adafruit/rp2040_usb_host/lib/Pico-PIO-USB/src

SRC += lib/tinyusb/src/tusb.c
SRC += lib/tinyusb/src/common/tusb_fifo.c
SRC += lib/tinyusb/src/host/usbh.c
SRC += lib/tinyusb/src/host/hub.c
SRC += lib/tinyusb/src/class/hid/hid_host.c
SRC += lib/tinyusb/src/portable/raspberrypi/pio_usb/hcd_pio_usb.c
VPATH += keyboards/adafruit/rp2040_usb_host/lib/tinyusb/src

SRC += lib/pico-sdk/src/rp2_common/hardware_dma/dma.c
SRC += lib/pico-sdk/src/host/pico_stdlib/stdlib.c
VPATH += lib/pico-sdk/src/rp2_common/hardware_dma/include
VPATH += lib/pico-sdk/src/rp2_common/hardware_uart/include
VPATH += lib/pico-sdk/src/rp2_common/pico_stdio/include
VPATH += lib/pico-sdk/src/common/pico_stdlib/include
VPATH += lib/pico-sdk/src/common/pico_time/include
VPATH += lib/pico-sdk/src/common/pico_sync/include
VPATH += lib/pico-sdk/src/common/pico_util/include

SRC += parser/report_descriptor_parser.c parser/report_parser.c
VPATH += keyboards/adafruit/rp2040_usb_host/parser
