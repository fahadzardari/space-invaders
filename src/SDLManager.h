//
// Created by mrzardari on 3/1/24.
//

#ifndef SPACE_INVADERS_SDLMANAGER_H
#define SPACE_INVADERS_SDLMANAGER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900


class SDLManager {
public:
    SDLManager();
    void initialize();
    void createWindow();
    void clear();
    void display();
    void cleanup();
    SDL_Window *window;
    SDL_Renderer *renderer;
private:
};


#endif //SPACE_INVADERS_SDLMANAGER_H
