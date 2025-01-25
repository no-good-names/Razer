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

add_executable(Razer
        src/main.c
        src/gfx/typedef.h
        src/gfx/prim.c
        src/gfx/prim.h
        src/gfx/math/maths.c
        src/gfx/math/maths.h
        src/gfx/objects.c
        src/gfx/objects.h
        src/gfx/gfx.h
)

target_link_libraries(Razer ${LIBS})
