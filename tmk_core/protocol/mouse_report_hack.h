HID_RI_USAGE_PAGE(8, 0x01),            // Generic Desktop
HID_RI_USAGE(8, 0x02),                 // Mouse
HID_RI_COLLECTION(8, 0x01),            // Application
#    ifdef MOUSE_SHARED_EP
    HID_RI_REPORT_ID(8, REPORT_ID_MOUSE),
#    endif
    HID_RI_USAGE(8, 0x01),             // Pointer
    HID_RI_COLLECTION(8, 0x00),        // Physical
        // Buttons (8 bits)
        HID_RI_USAGE_PAGE(8, 0x09),    // Button
        HID_RI_USAGE_MINIMUM(8, 0x01), // Button 1
        HID_RI_USAGE_MAXIMUM(8, 0x08), // Button 8
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(8, 0x01),
        HID_RI_REPORT_COUNT(8, 0x08),
        HID_RI_REPORT_SIZE(8, 0x01),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

#    ifdef MOUSE_EXTENDED_REPORT
        // Boot protocol XY ignored in Report protocol
        HID_RI_REPORT_COUNT(8, 0x02),
        HID_RI_REPORT_SIZE(8, 0x08),
        HID_RI_INPUT(8, HID_IOF_CONSTANT),
#    endif
        // X/Y position (2 or 4 bytes)
        HID_RI_USAGE_PAGE(8, 0x01),    // Generic Desktop
        HID_RI_USAGE(8, 0x30),         // X
        HID_RI_USAGE(8, 0x31),         // Y
#    ifndef MOUSE_EXTENDED_REPORT
        HID_RI_LOGICAL_MINIMUM(8, -127),
        HID_RI_LOGICAL_MAXIMUM(8, 127),
        HID_RI_REPORT_COUNT(8, 0x02),
        HID_RI_REPORT_SIZE(8, 0x08),
#    else
        HID_RI_LOGICAL_MINIMUM(16, -32767),
        HID_RI_LOGICAL_MAXIMUM(16,  32767),
        HID_RI_REPORT_COUNT(8, 0x02),
        HID_RI_REPORT_SIZE(8, 0x10),
#    endif
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),

        #    ifdef POINTING_DEVICE_HIRES_SCROLL_ENABLE
            HID_RI_COLLECTION(8, 0x02),
            // Feature report and padding (1 byte)
            HID_RI_USAGE(8, 0x48),     // Resolution Multiplier
            HID_RI_REPORT_COUNT(8, 0x01),
            HID_RI_REPORT_SIZE(8, 0x02),
            HID_RI_LOGICAL_MINIMUM(8, 0x00),
            HID_RI_LOGICAL_MAXIMUM(8, 0x01),
            HID_RI_PHYSICAL_MINIMUM(8, 1),
            HID_RI_PHYSICAL_MAXIMUM(8, POINTING_DEVICE_HIRES_SCROLL_MULTIPLIER),
            HID_RI_UNIT_EXPONENT(8, POINTING_DEVICE_HIRES_SCROLL_EXPONENT),
            HID_RI_FEATURE(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
            HID_RI_PHYSICAL_MINIMUM(8, 0x00),
            HID_RI_PHYSICAL_MAXIMUM(8, 0x00),
            HID_RI_REPORT_SIZE(8, 0x06),
            HID_RI_FEATURE(8, HID_IOF_CONSTANT),
#    endif

        // Vertical wheel (1 or 2 bytes)
        HID_RI_USAGE(8, 0x38),     // Wheel
#    ifndef WHEEL_EXTENDED_REPORT
        HID_RI_LOGICAL_MINIMUM(8, -127),
        HID_RI_LOGICAL_MAXIMUM(8, 127),
        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_REPORT_SIZE(8, 0x08),
#    else
        HID_RI_LOGICAL_MINIMUM(16, -32767),
        HID_RI_LOGICAL_MAXIMUM(16,  32767),
        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_REPORT_SIZE(8, 0x10),
#    endif
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),
        // Horizontal wheel (1 or 2 bytes)
        HID_RI_USAGE_PAGE(8, 0x0C),// Consumer
        HID_RI_USAGE(16, 0x0238),  // AC Pan
#    ifndef WHEEL_EXTENDED_REPORT
        HID_RI_LOGICAL_MINIMUM(8, -127),
        HID_RI_LOGICAL_MAXIMUM(8, 127),
        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_REPORT_SIZE(8, 0x08),
#    else
        HID_RI_LOGICAL_MINIMUM(16, -32767),
        HID_RI_LOGICAL_MAXIMUM(16,  32767),
        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_REPORT_SIZE(8, 0x10),
#    endif
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),

#    ifdef POINTING_DEVICE_HIRES_SCROLL_ENABLE
        HID_RI_END_COLLECTION(0),
#    endif
    HID_RI_END_COLLECTION(0),
HID_RI_END_COLLECTION(0),
