#pragma once
#include <SDL_opengl.h>
#include "Core/Window.h"
#include "VertexBufferObject.h"

namespace Reborn {
	class Renderer {
	public:
		Renderer(Window& window);
		void draw();
		const SDL_GLContext& getContext();
		void generate(VBO& vbo);
		void upload(VBO& vbo, GLenum usage = GL_STATIC_DRAW);
		void bind(VBO& vbo);
		~Renderer();
	private:
		bool initImGui(SDL_Window* window);
		SDL_GLContext _context;
		Window& _window;
	};
}