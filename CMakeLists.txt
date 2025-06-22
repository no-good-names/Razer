cmake_minimum_required(VERSION 3.30)
project(Razer C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(engine EXCLUDE_FROM_ALL)
set(LIBS Razer-Engine)

add_executable(Razer test/main.c)

target_link_libraries(Razer PRIVATE ${LIBS})
