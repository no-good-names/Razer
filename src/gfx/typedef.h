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
#define WARNING(message) __attribute__((warning(message)))
#define RGB(r, g, b) (uint32_t) ((255 << 24) | (r << 16) | (g << 8) | b)

#define swap(a, b) \
		{ \
			__typeof__(a) temp = a; \
			a = b; \
			b = temp; \
		}

#define RED (uint32_t) 0xFFFF0000
#define GREEN (uint32_t) 0xFF00FF00
#define BLUE (uint32_t) 0xFF0000FF
#define YELLOW (uint32_t) 0xFFFFFF00
#define PURPLE (uint32_t) 0xFFFF00FF
#define CYAN (uint32_t) 0xFF00FFFF
#define WHITE (uint32_t) 0xFFFFFFFF
#define BLACK (uint32_t) 0xFF000000

#define MAX_OBJECT_VERTICES 1000

#if defined(_MSC_VER)
#define INLINE __forceinline
#else
#define INLINE static inline __attribute((always_inline))
#endif


#endif //TYPEDEF_H
