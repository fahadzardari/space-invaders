//
// Created by mrzardari on 3/1/24.
//

#include "SDLManager.h"

SDLManager::SDLManager() = default;

void SDLManager::initialize() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0 ){
        std::cout << "Initialization Error for SDL " << SDL_GetError() << std::endl;
    }else {
        std::cout << "SDL INITIALIZED ";
    }
}


