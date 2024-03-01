//
// Created by mrzardari on 3/1/24.
//

#ifndef SPACE_INVADERS_SDLMANAGER_H
#define SPACE_INVADERS_SDLMANAGER_H
#include <SDL2/SDL.h>
#include <iostream>


class SDLManager {
public:
    SDLManager();
    void initialize();
    SDL_Window *window;
private:
};


#endif //SPACE_INVADERS_SDLMANAGER_H
