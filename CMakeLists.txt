cmake_minimum_required(VERSION 3.27)
project(space_invaders)

set(CMAKE_CXX_STANDARD 20)
find_package(SDL2 REQUIRED SDL2)

add_executable(space_invaders main.cpp
        src/Application.cpp
        src/Application.h
)

target_link_libraries(space_invaders
        PRIVATE SDL2::SDL2
)
