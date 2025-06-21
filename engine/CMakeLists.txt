cmake_minimum_required(VERSION 3.30)
project(Razer-Engine C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)

add_subdirectory(lib/sdl3 EXCLUDE_FROM_ALL)
add_subdirectory(lib/cglm EXCLUDE_FROM_ALL)
set(LIBS SDL3::SDL3 cglm)

if (UNIX AND NOT APPLE)
    list(APPEND LIBS m)
endif ()

add_library(Razer-Engine STATIC
        src/backend.c
        src/primitives.c
        src/misc/misc.c
        include/Razer/misc/misc.h
)

target_link_libraries(Razer-Engine PUBLIC ${LIBS})

target_include_directories(Razer-Engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(Razer-Engine PUBLIC -DSDL_MAIN_HANDLED)

if (WIN32)
    target_compile_definitions(Razer-Engine PRIVATE -DRazer_Engine)
endif ()
