cmake_minimum_required(VERSION 3.27)
project(space_invaders)

set(CMAKE_CXX_STANDARD 20)
find_package(SDL2 REQUIRED SDL2)

find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)


add_executable(space_invaders main.cpp
        src/Application.cpp
        src/Application.h
        src/SDLManager.cpp
        src/SDLManager.h
        src/Invader.cpp
        src/Invader.h
        src/Ship.cpp
        src/Ship.h
        src/Vector2f.cpp
        src/Vector2f.h
        src/Constants.h
        src/Projectile.cpp
        src/Projectile.h
)
target_include_directories(space_invaders PRIVATE ${SDL2IMAGE_INCLUDE_DIRS})
target_link_libraries(space_invaders PRIVATE ${SDL2IMAGE_LIBRARIES})
target_link_libraries(space_invaders
        PRIVATE SDL2::SDL2
)
