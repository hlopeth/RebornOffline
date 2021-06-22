#include "System.h"
#include <SDL.h>
#include "Log.h"

Reborn::System* Reborn::System::systemInstance = nullptr;

Reborn::System& Reborn::System::get()
{
    return *systemInstance;
}

int Reborn::System::Init() {
    Uint32 sdlInitFlags = SDL_INIT_VIDEO;
    if (SDL_Init(sdlInitFlags) != 0) {
        LOG_ERROR << "Error while sdl init. \n" << SDL_GetError();
        return 1;
    }
    return 0;
}

void Reborn::System::Shutdown()
{
    SDL_Quit();
    systemInstance = nullptr;
}