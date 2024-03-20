//
// Created by mrzardari on 3/1/24.
//

#include "Application.h"
#include <iostream>

void Application::run() {
    sdl.initialize();
    sdl.createWindow();

    SDL_Texture* texture = sdl.loadTexture("../assets/ship.png");

    bool run = true;
    while(run){
        SDL_Event ev;
        while(SDL_PollEvent(&ev)){
            switch(ev.type){
                case SDL_QUIT:
                    run = false;
                    break;
            }
        }
        sdl.clear();
        sdl.renderTexture(texture);
        sdl.display();
    }
    sdl.cleanup();
    SDL_Quit();
}
