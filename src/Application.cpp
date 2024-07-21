//
// Created by mrzardari on 3/1/24.
//

#include "Application.h"
#include "Ship.h"
#include "Projectile.h"
#include <chrono>

void Application::run() {
    sdl.enemies_x=80;
    sdl.enemies_x_end=720;
    sdl.enemies_y= 240;
    sdl.initialize();
    sdl.createWindow();
    sdl.createShip();
    sdl.createEnemies();
    sdl.enemiesDirection = true;
    sdl.playersLives = 3;
    bool run = true;
    int count = 0;
    bool rightKeyPressed = false;
    bool leftKeyPressed = false;
    auto lastFired = std::chrono::steady_clock::now();
    while (run) {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
                case SDL_QUIT:
                    run = false;
                    break;
                case SDL_KEYDOWN:
                    switch (ev.key.keysym.sym) {
                        case SDLK_RIGHT:
                            std::cout << "Right key pressed" << std::endl;
                            rightKeyPressed = true;
                            break;
                        case SDLK_LEFT:
                            std::cout << "Left key pressed" << std::endl;
                            leftKeyPressed = true;
                            break;
                        case SDLK_f:
                            std::cout << "Fire (f) pressed " << count++ << std::endl;
                            auto currentTime = std::chrono::steady_clock::now();
                            const std::chrono::duration<double> elapsed_seconds{currentTime - lastFired};
                            const std::chrono::duration<double> duration{0.25};
                            if (elapsed_seconds > duration) {
                                sdl.createProjectile();
                                lastFired = currentTime;
                            }
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (ev.key.keysym.sym) {
                        case SDLK_RIGHT:
                            std::cout << "Right key released" << std::endl;
                            rightKeyPressed = false;
                            break;
                        case SDLK_LEFT:
                            std::cout << "Left key released" << std::endl;
                            leftKeyPressed = false;
                            break;
                    }
                    break;
            }
        }
        if (rightKeyPressed) {
            std::cout << "Moving ship right" << std::endl;
            sdl.playerShip.moveRight();
        }
        if (leftKeyPressed) {
            std::cout << "Moving ship left" << std::endl;
            sdl.playerShip.moveLeft();
        }
        sdl.clear();
        sdl.render();
        sdl.display();
    }
    sdl.cleanup();
    SDL_Quit();
}
