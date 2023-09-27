#pragma once

#include <Common.h>

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} GXColor;
static_assert(sizeof(GXColor) == 0x4);

#define GXCOLOR_RED \
    (GXColor) { 0xFF, 0x00, 0x00, 0xFF }
#define GXCOLOR_GREEN \
    (GXColor) { 0x00, 0xFF, 0x00, 0xFF }
#define GXCOLOR_BLUE \
    (GXColor) { 0x00, 0x00, 0xFF, 0xFF }
#define GXCOLOR_PINK \
    (GXColor) { 0xFF, 0x00, 0xFF, 0xFF }
#define GXCOLOR_WHITE \
    (GXColor) { 0xFF, 0xFF, 0xFF, 0xFF }
#define GXCOLOR_BLACK \
    (GXColor) { 0x00, 0x00, 0x00, 0xFF }
