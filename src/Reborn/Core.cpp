#include "Core.h"
#include <SDL.h>
#include <iostream>

int Reborn::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "error while sdl init. \n" << SDL_GetError() << std::endl;
        return 1;
    }
    return 0;
}