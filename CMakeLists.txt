cmake_minimum_required(VERSION 3.8)
project(Snake)

set(CMAKE_C_STANDARD 99)

LINK_DIRECTORIES(/usr/local/lib)

set(SOURCE_FILES main.c)
add_executable(untitled15 ${SOURCE_FILES})

INCLUDE_DIRECTORIES(/usr/local/include/SDL2)
TARGET_LINK_LIBRARIES(untitled15 m SDL2 SDL2_gfx)
ADD_DEFINITIONS(-D_THREAD_SAFE)