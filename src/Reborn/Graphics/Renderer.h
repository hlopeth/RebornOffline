#pragma once
#include <SDL_opengl.h>
#include "Core/Window.h"

namespace Reborn {
	class Renderer {
	public:
		Renderer(Window& window);
		void draw();
		const SDL_GLContext& getContext();
		~Renderer();
	private:
		bool initImGui(SDL_Window* window);
		SDL_GLContext _context;
		Window& _window;
	};
}