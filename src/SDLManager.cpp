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

void SDLManager::createWindow() {
    this->window = SDL_CreateWindow("Space Invaders" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , SCREEN_WIDTH , SCREEN_HEIGHT , SDL_WINDOW_RESIZABLE);
    this->renderer = SDL_CreateRenderer(this->window , -1 , 0);
    SDL_SetRenderDrawColor(this->renderer , 0 , 0 , 0 ,255);
}

void SDLManager::clear() {
    SDL_RenderClear(this->renderer);
}

void SDLManager::display() {
    SDL_RenderPresent(this->renderer);
}

void SDLManager::cleanup() {
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
}
