#include "engine.h"
#include <SDL.h>
#include <iostream>

int createWindow(const char* name) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "error while sdl init. \n" << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow(name, 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if(win == nullptr) {
        std::cout << "error while sdl window creation. \n" << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Delay(10000);

    SDL_DestroyWindow(win);
    SDL_Quit();

    // SDL_Renderer* renderer = SDL_CreateRenderer(
    //     win,
    //     -1,
    //     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC 
    // );

    // if(renderer == nullptr) {
    //     return 1;
    // }

    return 0;
}