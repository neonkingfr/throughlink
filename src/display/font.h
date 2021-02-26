#pragma once

constexpr uint8_t font[] = {
    /* 0x20 */ 0x00, 0x00, 0x00, 0x00, 0x00,
    /* 0x21 */ 0x00, 0x00, 0x5f, 0x00, 0x00,
    /* 0x22 */ 0x00, 0x07, 0x00, 0x07, 0x00,
    /* 0x23 */ 0x14, 0x7f, 0x14, 0x7f, 0x14,
    /* 0x24 */ 0x24, 0x2a, 0x7f, 0x2a, 0x12,
    /* 0x25 */ 0x23, 0x13, 0x08, 0x64, 0x62,
    /* 0x26 */ 0x36, 0x49, 0x55, 0x22, 0x50,
    /* 0x27 */ 0x00, 0x05, 0x03, 0x00, 0x00,
    /* 0x28 */ 0x00, 0x1c, 0x22, 0x41, 0x00,
    /* 0x29 */ 0x00, 0x41, 0x22, 0x1c, 0x00,
    /* 0x2a */ 0x08, 0x2a, 0x1c, 0x2a, 0x08,
    /* 0x2b */ 0x08, 0x08, 0x3e, 0x08, 0x08,
    /* 0x2c */ 0x00, 0x50, 0x30, 0x00, 0x00,
    /* 0x2d */ 0x08, 0x08, 0x08, 0x08, 0x08,
    /* 0x2e */ 0x00, 0x60, 0x60, 0x00, 0x00,
    /* 0x2f */ 0x20, 0x10, 0x08, 0x04, 0x02,
    /* 0x30 */ 0x3e, 0x51, 0x49, 0x45, 0x3e,
    /* 0x31 */ 0x00, 0x42, 0x7f, 0x40, 0x00,
    /* 0x32 */ 0x42, 0x61, 0x51, 0x49, 0x46,
    /* 0x33 */ 0x21, 0x41, 0x45, 0x4b, 0x31,
    /* 0x34 */ 0x18, 0x14, 0x12, 0x7f, 0x10,
    /* 0x35 */ 0x27, 0x45, 0x45, 0x45, 0x39,
    /* 0x36 */ 0x3c, 0x4a, 0x49, 0x49, 0x30,
    /* 0x37 */ 0x01, 0x71, 0x09, 0x05, 0x03,
    /* 0x38 */ 0x36, 0x49, 0x49, 0x49, 0x36,
    /* 0x39 */ 0x06, 0x49, 0x49, 0x29, 0x1e,
    /* 0x3a */ 0x00, 0x36, 0x36, 0x00, 0x00,
    /* 0x3b */ 0x00, 0x56, 0x36, 0x00, 0x00,
    /* 0x3c */ 0x00, 0x08, 0x14, 0x22, 0x41,
    /* 0x3d */ 0x14, 0x14, 0x14, 0x14, 0x14,
    /* 0x3e */ 0x41, 0x22, 0x14, 0x08, 0x00,
    /* 0x3f */ 0x02, 0x01, 0x51, 0x09, 0x06,
    /* 0x40 */ 0x32, 0x49, 0x79, 0x41, 0x3e,
    /* 0x41 */ 0x7e, 0x11, 0x11, 0x11, 0x7e,
    /* 0x42 */ 0x7f, 0x49, 0x49, 0x49, 0x36,
    /* 0x43 */ 0x3e, 0x41, 0x41, 0x41, 0x22,
    /* 0x44 */ 0x7f, 0x41, 0x41, 0x22, 0x1c,
    /* 0x45 */ 0x7f, 0x49, 0x49, 0x49, 0x41,
    /* 0x46 */ 0x7f, 0x09, 0x09, 0x01, 0x01,
    /* 0x47 */ 0x3e, 0x41, 0x41, 0x51, 0x32,
    /* 0x48 */ 0x7f, 0x08, 0x08, 0x08, 0x7f,
    /* 0x49 */ 0x00, 0x41, 0x7f, 0x41, 0x00,
    /* 0x4a */ 0x20, 0x40, 0x41, 0x3f, 0x01,
    /* 0x4b */ 0x7f, 0x08, 0x14, 0x22, 0x41,
    /* 0x4c */ 0x7f, 0x40, 0x40, 0x40, 0x40,
    /* 0x4d */ 0x7f, 0x02, 0x04, 0x02, 0x7f,
    /* 0x4e */ 0x7f, 0x04, 0x08, 0x10, 0x7f,
    /* 0x4f */ 0x3e, 0x41, 0x41, 0x41, 0x3e,
    /* 0x50 */ 0x7f, 0x09, 0x09, 0x09, 0x06,
    /* 0x51 */ 0x3e, 0x41, 0x51, 0x21, 0x5e,
    /* 0x52 */ 0x7f, 0x09, 0x19, 0x29, 0x46,
    /* 0x53 */ 0x46, 0x49, 0x49, 0x49, 0x31,
    /* 0x54 */ 0x01, 0x01, 0x7f, 0x01, 0x01,
    /* 0x55 */ 0x3f, 0x40, 0x40, 0x40, 0x3f,
    /* 0x56 */ 0x1f, 0x20, 0x40, 0x20, 0x1f,
    /* 0x57 */ 0x7f, 0x20, 0x18, 0x20, 0x7f,
    /* 0x58 */ 0x63, 0x14, 0x08, 0x14, 0x63,
    /* 0x59 */ 0x03, 0x04, 0x78, 0x04, 0x03,
    /* 0x5a */ 0x61, 0x51, 0x49, 0x45, 0x43,
    /* 0x5b */ 0x00, 0x00, 0x7f, 0x41, 0x41,
    /* 0x5c */ 0x02, 0x04, 0x08, 0x10, 0x20,
    /* 0x5d */ 0x41, 0x41, 0x7f, 0x00, 0x00,
    /* 0x5e */ 0x04, 0x02, 0x01, 0x02, 0x04,
    /* 0x5f */ 0x40, 0x40, 0x40, 0x40, 0x40,
    /* 0x60 */ 0x00, 0x01, 0x02, 0x04, 0x00,
    /* 0x61 */ 0x20, 0x54, 0x54, 0x54, 0x78,
    /* 0x62 */ 0x7f, 0x48, 0x44, 0x44, 0x38,
    /* 0x63 */ 0x38, 0x44, 0x44, 0x44, 0x20,
    /* 0x64 */ 0x38, 0x44, 0x44, 0x48, 0x7f,
    /* 0x65 */ 0x38, 0x54, 0x54, 0x54, 0x18,
    /* 0x66 */ 0x08, 0x7e, 0x09, 0x01, 0x02,
    /* 0x67 */ 0x08, 0x14, 0x54, 0x54, 0x3c,
    /* 0x68 */ 0x7f, 0x08, 0x04, 0x04, 0x78,
    /* 0x69 */ 0x00, 0x44, 0x7d, 0x40, 0x00,
    /* 0x6a */ 0x20, 0x40, 0x44, 0x3d, 0x00,
    /* 0x6b */ 0x00, 0x7f, 0x10, 0x28, 0x44,
    /* 0x6c */ 0x00, 0x41, 0x7f, 0x40, 0x00,
    /* 0x6d */ 0x7c, 0x04, 0x18, 0x04, 0x78,
    /* 0x6e */ 0x7c, 0x08, 0x04, 0x04, 0x78,
    /* 0x6f */ 0x38, 0x44, 0x44, 0x44, 0x38,
    /* 0x70 */ 0x7c, 0x14, 0x14, 0x14, 0x08,
    /* 0x71 */ 0x08, 0x14, 0x14, 0x18, 0x7c,
    /* 0x72 */ 0x7c, 0x08, 0x04, 0x04, 0x08,
    /* 0x73 */ 0x48, 0x54, 0x54, 0x54, 0x20,
    /* 0x74 */ 0x04, 0x3f, 0x44, 0x40, 0x20,
    /* 0x75 */ 0x3c, 0x40, 0x40, 0x20, 0x7c,
    /* 0x76 */ 0x1c, 0x20, 0x40, 0x20, 0x1c,
    /* 0x77 */ 0x3c, 0x40, 0x30, 0x40, 0x3c,
    /* 0x78 */ 0x44, 0x28, 0x10, 0x28, 0x44,
    /* 0x79 */ 0x0c, 0x50, 0x50, 0x50, 0x3c,
    /* 0x7a */ 0x44, 0x64, 0x54, 0x4c, 0x44,
    /* 0x7b */ 0x00, 0x08, 0x36, 0x41, 0x00,
    /* 0x7c */ 0x00, 0x00, 0x7f, 0x00, 0x00,
    /* 0x7d */ 0x00, 0x41, 0x36, 0x08, 0x00,
    /* 0x7e */ 0x08, 0x08, 0x2a, 0x1c, 0x08,
};
