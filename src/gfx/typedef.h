//
// Created by cp176 on 1/24/2025.
//

#ifndef TYPEDEF_H
#define TYPEDEF_H

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 1200
#endif
#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 900
#endif

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 1200
#endif

#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 900
#endif

// Auto aspect ratio
#define VIEWPORT_WIDTH 1.0f
#define VIEWPORT_HEIGHT (VIEWPORT_WIDTH * (float) SCREEN_HEIGHT / SCREEN_WIDTH)

#define ASSERT(condition, message) if (!(condition)) { fprintf(stderr, "Assertion failed: %s\n", message); return 1; }
#define DEPRECATED(message) __attribute__((deprecated(message)))
#define RGB(r, g, b) (uint32_t) ((255 << 24) | (r << 16) | (g << 8) | b)
#define ABS(_x) ( (_x) < 0 ? -(_x) : (_x) )
#define MAX(_x, _y) ( (_x) > _y ? (_x)-1 : (_x) )

#define swap(a, b) \
		{ \
			__typeof__(a) temp = a; \
			a = b; \
			b = temp; \
		}


#define RED (uint32_t) 0xFFFF0000
#define GREEN (uint32_t) 0xFF00FF00
#define BLUE (uint32_t) 0xFF0000FF

#ifdef RENDER_WIREFRAME
#define RENDER_WIREFRAME 1
#else
#define RENDER_WIREFRAME 0
#endif

#endif //TYPEDEF_H
