#pragma once
#include "Core.h"
#include "Renderer.h"

Reborn::Renderer::Renderer(SDL_GLContext context):
	_context(context)
{
	glClearColor(1.0, 0.0, 0.0, 1.0);
}

void Reborn::Renderer::draw(Window& window)
{
	glViewport(0, 0, window.width(), window.height());
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(&(window.getSDLWindow()));
}

const SDL_GLContext& Reborn::Renderer::getContext()
{
	return _context;
}

Reborn::Renderer::~Renderer()
{
	SDL_GL_DeleteContext(_context);
}
