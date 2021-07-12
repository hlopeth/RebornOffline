#pragma once
#include <SDL_opengl.h>
#include "Core/Window.h"
#include "VertexArrayObject.h"
#include "GLSLProgram.h"

namespace Reborn {
	class Renderer {
	public:
		Renderer(Window& window);
		void draw();
		const SDL_GLContext& getContext();
		void create(GLSLProgram& program);
		void create(VertexBufferObject& vbo);
		//creates VertexAttayObject and it's VertexBufferObject
		void create(VertexAttayObject& vao);
		void upload(VertexBufferObject& vbo, GLenum usage = GL_STATIC_DRAW);
		void createLayout(VertexAttayObject vao);
		void bind(VertexBufferObject& vbo);
		void bind(VertexAttayObject& vao);
		void useProgram(const GLSLProgram& program);
		~Renderer();
	private:
		bool initImGui(SDL_Window* window);
		SDL_GLContext _context;
		Window& _window;
	};
}