//
// Created by mrzardari on 3/1/24.
//

#include "Application.h"
#include "Ship.h"

void Application::run() {
    sdl.initialize();
    sdl.createWindow();

    Ship playerShip = *new Ship(sdl.getRenderer());
    bool run = true;
    int count = 0;
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
                            std::cout << "Right pressed " << count++ <<std::endl;
                            playerShip.moveRight();
                            break;
                        case SDLK_LEFT:
                            std::cout << "Left pressed " << count++ <<std::endl;
                            playerShip.moveLeft();
                            break;
                    }
            }
        }

        sdl.clear();
        sdl.renderShip(&playerShip);
        sdl.display();
    }
    sdl.cleanup();
    SDL_Quit();
}
