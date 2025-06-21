//
// Created by carp on 6/18/25.
//

#ifndef MISC_H
#define MISC_H

#define iswap(a, b) \
    a = a^b; \
    b = a^b; \
    a = b^a; \

#include <stdint.h>

static uint32_t color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return ((uint32_t)a << 24) | ((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b;
}

#endif //MISC_H
