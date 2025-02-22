cmake_minimum_required(VERSION 3.30)
project(Razer C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 QUIET)

if(SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIRS})
else()
    message(STATUS "SDL2 wasn't found, please install")
endif()

set(LIBS ${LIBS} ${SDL2_LIBRARIES} m)

# LONGGG
add_executable(Razer
        src/main.c
        src/gfx/typedef.h
        src/gfx/primitives.c
        src/gfx/primitives.h
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
        src/gfx/objects.c
        src/gfx/objects.h
        src/gfx/gfx.h
        src/gfx/camera.c
        src/gfx/camera.h
        src/gfx/scene.c
        src/gfx/scene.h
        src/gfx/window.h
        src/gfx/window.c
        src/gfx/math/mat3.c
        src/gfx/math/mat3.h
)

target_link_libraries(Razer ${LIBS})
