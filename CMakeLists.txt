cmake_minimum_required(VERSION 3.30)
project(razer_remake C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(lib/SDL2)
set(LIBS SDL2-static m)

add_executable(razer_remake
        src/main.c
        src/gfx/typedef.h
        src/gfx/primitives.c
        src/gfx/primitives.h
        src/gfx/window.c
        src/gfx/window.h
        src/gfx/math/maths.c
        src/gfx/math/maths.h
        src/gfx/math/vec2.c
        src/gfx/math/vec2.h
        src/gfx/math/vec3.c
        src/gfx/math/vec3.h
        src/gfx/math/vec4.c
        src/gfx/math/vec4.h
        src/gfx/math/ivec2.c
        src/gfx/math/ivec2.h
        src/gfx/math/ivec3.c
        src/gfx/math/ivec3.h
        src/gfx/math/ivec4.c
        src/gfx/math/ivec4.h
        src/gfx/math/mat3.c
        src/gfx/math/mat3.h
        src/gfx/math/mat4.c
        src/gfx/math/mat4.h
        src/gfx/typedef.h
)

target_compile_definitions(razer_remake PRIVATE SDL_MAIN_HANDLED)
target_link_libraries(razer_remake ${LIBS})
