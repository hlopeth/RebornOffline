#include "Core.h"
#include "Window.h"

#include <imgui.h>

Reborn::Window::Window(SDL_Window* sdlWindow)
{
	_sdlWindow = sdlWindow;
}

SDL_GLContext Reborn::Window::createGLContext()
{
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	SDL_GLContext context = SDL_GL_CreateContext(_sdlWindow);
	if (!context) {
		LOG_ERROR << "Failed to create context. \n" << SDL_GetError();
		context = nullptr;
	}
	return context;
}

SDL_Window& Reborn::Window::getSDLWindow()
{
	return *_sdlWindow;
}

const int Reborn::Window::width() const
{
	int width;
	int height;
	SDL_GetWindowSize(_sdlWindow, &width, &height);
	return width;
}

const int Reborn::Window::height() const
{
	int width;
	int height;
	SDL_GetWindowSize(_sdlWindow, &width, &height);
	return height;
}

void Reborn::Window::Update()
{
	//SDL_UpdateWindowSurface(_sdlWindow);
}

Reborn::Window::~Window()
{
	SDL_DestroyWindow(_sdlWindow);
}

Reborn::Window* Reborn::Window::CreateSDLWindow(WindowConfiguration config)
{

	Uint16 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
	if(config.resizable)
		flags |= SDL_WINDOW_RESIZABLE;
	if(config.fullscreen)
		flags |= SDL_WINDOW_FULLSCREEN;

	SDL_Window* sdlWindow = SDL_CreateWindow(config.title, config.x, config.y, config.width, config.height, flags);
	if (sdlWindow == nullptr) {
		LOG_ERROR << "Failed to create SDL window. \n" << SDL_GetError();
	}
	return new Window(sdlWindow);
}