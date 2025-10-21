#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#ifdef __cplusplus
 extern "C" {
#endif

#define CFG_TUSB_OS               OPT_OS_CUSTOM
#define CFG_TUSB_MCU              OPT_MCU_RP2040

#define CFG_TUSB_DEBUG 0
#define CFG_TUSB_DEBUG_PRINTF tusb_debug_printf

// Disable device stack
#define CFG_TUD_ENABLED     0

// Enable host stack with pio-usb if Pico-PIO-USB library is available
#define CFG_TUH_ENABLED     1
#define CFG_TUH_RPI_PIO_USB 1

#ifndef CFG_TUSB_MEM_SECTION
#define CFG_TUSB_MEM_SECTION
#endif

#ifndef CFG_TUSB_MEM_ALIGN
#define CFG_TUSB_MEM_ALIGN          __attribute__ ((aligned(4)))
#endif

// HOST CONFIGURATION
//--------------------------------------------------------------------

#define CFG_TUH_ENUMERATION_BUFSIZE 256

#define CFG_TUH_HUB                 1
#define CFG_TUH_DEVICE_MAX          (CFG_TUH_HUB ? 4 : 1) 

#define CFG_TUH_HID                  8
#define CFG_TUH_HID_EPIN_BUFSIZE    64
#define CFG_TUH_HID_EPOUT_BUFSIZE   64

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_CONFIG_H_ */
