cmake_minimum_required(VERSION 3.27)
project(space_invaders)

set(CMAKE_CXX_STANDARD 20)
find_package(SDL2 REQUIRED SDL2)


find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)


add_executable(space_invaders main.cpp
        src/Application.cpp
        src/Application.h
        src/SDLManager.cpp
        src/SDLManager.h
        src/Ship.cpp
        src/Ship.h
        src/Vector2f.cpp
        src/Vector2f.h
        src/Constants.h
        src/Projectile.cpp
        src/Projectile.h
        src/enemies/Enemy.h
        src/enemies/Enemy.cpp
        src/enemies/Invader.cpp
        src/enemies/Invader.h
        src/enemies/EnemyFactory.cpp
        src/enemies/EnemyFactory.h
)
# Include directories
target_include_directories(space_invaders PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

# Link libraries
target_link_libraries(space_invaders PRIVATE ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
