//
// Created by mrzardari on 3/1/24.
//

#include "Application.h"
#include <iostream>

void Application::run() {
    sdl.initialize();
    sdl.window = SDL_CreateWindow("Space Invaders" , 200 , 200 , 800 , 600 , SDL_WINDOW_RESIZABLE);
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
    }
}
