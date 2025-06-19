cmake_minimum_required(VERSION 3.30)
project(Razer C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(lib/sdl3 EXCLUDE_FROM_ALL)
add_subdirectory(lib/cglm EXCLUDE_FROM_ALL)
set(LIBS SDL3::SDL3 cglm m)

add_executable(Razer src/main.c
        src/gfx/backend.c
        src/gfx/backend.h
        src/gfx/primitives.c
        src/gfx/primitives.h
        src/misc/misc.c
        src/misc/misc.h
)

target_link_libraries(Razer ${LIBS})

