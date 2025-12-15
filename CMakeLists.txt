cmake_minimum_required(VERSION 3.27)
project(space_invaders)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL2 (modern CMake)
find_package(SDL2 CONFIG REQUIRED)

# SDL_image + SDL_ttf via pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2TTF REQUIRED SDL2_ttf)

add_executable(space_invaders
        main.cpp
        src/Application.cpp
        src/SDLManager.cpp
        src/Ship.cpp
        src/Vector2f.cpp
        src/Projectile.cpp
        src/enemies/Enemy.cpp
        src/enemies/Invader.cpp
        src/enemies/EnemyFactory.cpp
        src/obstacle/Obstacle.cpp
        src/obstacle/Block.cpp
)

target_include_directories(space_invaders PRIVATE
        ${SDL2IMAGE_INCLUDE_DIRS}
        ${SDL2TTF_INCLUDE_DIRS}
)

target_link_directories(space_invaders PRIVATE
        ${SDL2IMAGE_LIBRARY_DIRS}
        ${SDL2TTF_LIBRARY_DIRS}
)

target_link_libraries(space_invaders PRIVATE
        SDL2::SDL2
        ${SDL2IMAGE_LIBRARIES}
        ${SDL2TTF_LIBRARIES}
)
