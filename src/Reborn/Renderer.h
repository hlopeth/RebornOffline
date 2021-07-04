#pragma once
#include <SDL_video.h>
#include <SDL_opengl.h>
#include "Window.h"

namespace Reborn {
	class Renderer {
	public:
		Renderer(SDL_GLContext context);
		void draw(Window& window);
		const SDL_GLContext& getContext();
		~Renderer();
	private:
		SDL_GLContext _context;
	};
}