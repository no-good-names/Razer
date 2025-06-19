//
// Created by carp on 6/18/25.
//

#include "primitives.h"
#include "backend.h"

#include <cglm/cglm.h>

#include "../misc/misc.h"

void set_pixel(const int32_t x, const int32_t y, const uint32_t color) {
    // start at the middle of the screen
    // const int32_t tmp_x = x + get_screen_width()/2;
    // const int32_t tmp_y = (get_screen_height() / 2) - y - 1; // y flip
    // Check if x or y is out of bounds of the screen if so return
    if (x < 0 || x >= get_screen_width() || y < 0 || y >= get_screen_height()) {
        return;
    }

    pixels[(y * get_screen_width()) + x] = color;
}

void get_pixel(const int32_t x, const int32_t y, uint32_t *color) {
    // // start at the middle of the screen
    // const int32_t tmp_x = x + get_screen_width()/2;
    // const int32_t tmp_y = (get_screen_height() / 2) - y - 1; // y flip
    // Check if x or y is out of bounds of the screen if so return
    if (x < 0 || y >= get_screen_width() || y < 0 || y >= get_screen_height()) {
        return;
    }

    *color = pixels[(y * get_screen_width()) + x];
}

void draw_line(int ax, int ay, int bx, int by, uint32_t color) {
    bool steep = false;
    if (abs(ax - bx) < abs(ay - by)) {
        iswap(ax, ay);
        iswap(bx, by);
        steep = true;
    }
    if (ax > bx) {
        iswap(ax, bx);
        iswap(ay, by);
    }

    const int dx = bx - ax;
    const int dy = by - ay;
    const int derror2 = abs(dy) * 2;
    int error2 = 0;
    int y = ay;
    for (int x = ax; x <= bx; x++) {
        if (steep)
            set_pixel(y, x, color);
        else
            set_pixel(x, y, color);

        error2 += derror2;
        if (error2 > dx) {
            y += (by > ay) ? 1 : -1;
            error2 -= dx * 2;
        }
    }
}
