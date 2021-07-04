#include "Core.h"
#include "System.h"
#include <SDL.h>
#include "Systems/TestSystem.h"
#include "Components/TestComponent.h"

Reborn::System* Reborn::System::systemInstance = nullptr;

Reborn::EntityManager<Reborn::System::maxComponents, Reborn::System::maxEntitySystems>& Reborn::System::entityManager()
{
    return _entityManager;
}

Reborn::System::System() {

}

Reborn::System& Reborn::System::get()
{
    if (systemInstance == nullptr) {
        systemInstance = new System();
    }
    return *systemInstance;
}

int Reborn::System::Init() {
    Uint32 sdlInitFlags = SDL_INIT_VIDEO;
    if (SDL_Init(sdlInitFlags) != 0) {
        LOG_ERROR << "Error while sdl init. \n" << SDL_GetError();
        return 1;
    }

    auto testSystem = _entityManager.createSystem<TestSystem<System::maxComponents, System::maxEntitySystems>>();
    _entityManager.registerComponent<TestComponent>();
    return 0;
}

void Reborn::System::Shutdown()
{
    SDL_Quit();
    delete systemInstance;
    systemInstance = nullptr;
}

Reborn::EventDispatcher& Reborn::System::eventDispatcher()
{
    return _eventDispatcher;
}
