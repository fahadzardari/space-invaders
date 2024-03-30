//
// Created by mrzardari on 3/1/24.
//

#include "Application.h"
#include "Ship.h"
#include "Projectile.h"

void Application::run() {
    sdl.initialize();
    sdl.createWindow();
    sdl.createShip();
    bool run = true;
    int count = 0;
    bool rightKeyPressed = false;
    bool leftKeyPressed = false;
    while(run){
        SDL_Event ev;
        while(SDL_PollEvent(&ev)){
            switch(ev.type){
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
                            std::cout << "Fire (f) pressed " << count++ <<std::endl;
                            sdl.createProjectile();
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
