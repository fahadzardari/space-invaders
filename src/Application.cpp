//
// Created by mrzardari on 3/1/24.
//

#include "Application.h"
#include "Ship.h"

void Application::run() {
    sdl.initialize();
    sdl.createWindow();

    Ship p1 = *new Ship(sdl.getRenderer());
    bool run = true;
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    int count = 0;
    while(run){
        SDL_Event ev;
        while(SDL_PollEvent(&ev)){
            switch(ev.type){
                case SDL_QUIT:
                    run = false;
                    break;
                case SDL_KEYDOWN:
                    if(ev.key.keysym.sym == SDLK_UP){
                            std::cout << "Up pressed " << count++ <<std::endl;
                    }
            }
        }

        sdl.clear();
        sdl.renderTexture(p1.getTexture());
        sdl.display();
    }
    sdl.cleanup();
    SDL_Quit();
}
