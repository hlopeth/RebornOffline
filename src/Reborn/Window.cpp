#include "Core.h"
#include "Window.h"

Reborn::Window::Window(SDL_Window* sdlWindow)
{
	_id = sdlWindow;
}

void Reborn::Window::Update()
{
	SDL_UpdateWindowSurface(_id);
}

Reborn::Window::~Window()
{
	SDL_DestroyWindow(_id);
}

std::shared_ptr<Reborn::Window> Reborn::Window::CreateSDLWindow(WindowConfiguration config)
{
	Uint16 flags = SDL_WINDOW_SHOWN;
	if(config.resizable)
		flags |= SDL_WINDOW_RESIZABLE;
	if(config.fullscreen)
		flags |= SDL_WINDOW_FULLSCREEN;

	SDL_Window* sdlWindow = SDL_CreateWindow(config.title, config.x, config.y, config.width, config.height, flags);
	if (sdlWindow == nullptr) {
		LOG_ERROR << "Failed to create SDL window";
	}
	return std::make_shared<Window>(sdlWindow);
}