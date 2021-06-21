#include "Application.h"
#include <SDL.h>
#include <iostream>

SDL_Event event;

Reborn::Application::Application(WindowConfiguration windowConfig):
	window(Window::CreateWindow(windowConfig))
{
	if (!window) {
		shouldClose = true;
	}
}

void Reborn::Application::Run()
{
	if (!window) {
		return;
	}

	while (!shouldClose)
	{
		PoolEvents();		
		window->Update();
	}

}

void Reborn::Application::Close()
{
	shouldClose = true;
}

Reborn::Application::~Application()
{
}

void Reborn::Application::PoolEvents()
{
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			shouldClose = true;
			break;
		default:
			break;
		}
	}
}