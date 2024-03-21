//
// Created by mrzardari on 3/1/24.
//

#include "SDLManager.h"

SDLManager::SDLManager() = default;

void SDLManager::initialize() {
    if(SDL_Init(SDL_INIT_VIDEO) > 0 )
        std::cout << "Initialization Error for SDL" << SDL_GetError() << std::endl;
    if(!IMG_Init(IMG_INIT_PNG))
        std::cout << "Initialization Error for SDL IMAGE" << SDL_GetError() << std::endl;
}

void SDLManager::createWindow() {
    this->window = SDL_CreateWindow("Space Invaders" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , SCREEN_WIDTH , SCREEN_HEIGHT , SDL_WINDOW_RESIZABLE);
    this->renderer = SDL_CreateRenderer(this->window , -1 ,  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(this->renderer , 0 , 0 , 0 ,255);
}

SDL_Texture* SDLManager::loadTexture(const char *filePath) {
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(this->renderer , filePath);
    if(texture == NULL){
        std::cout << "Error Loading Texture Error: " << SDL_GetError() << std::endl;
    }

    return texture;
}

void SDLManager::renderTexture(SDL_Texture *tex) {
    SDL_Rect dest;
    dest.x = SCREEN_WIDTH - (SCREEN_WIDTH/2);
    dest.y = SCREEN_HEIGHT - 50;
    dest.w = 50;
    dest.h = 50;

    SDL_RenderCopy(this->renderer , tex , nullptr , &dest);
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

SDL_Renderer *SDLManager::getRenderer() {
    return this->renderer;
}

void SDLManager::renderShip(Ship *ship) {
    SDL_Rect dest;
    dest.x = ship->pos.x;
    dest.y = ship->pos.y;
    dest.w = 50;
    dest.h = 50;
    SDL_RenderCopy(this->renderer , ship->getTexture() , NULL , &dest);
}
