#pragma once
#include <SDL_opengl.h>
#include "Core/Window.h"
#include "VertexArrayObject.h"
#include "GLSLProgram.h"
#include "Math/Vector.h"

namespace Reborn {
	class Renderer {
	public:
		Renderer(Window& window);
		void beginFrame();
		void endFrame();
		void drawVAO(VertexArrayObject& vao, GLuint vertices, GLuint offset = 0);
		const SDL_GLContext& getContext();
		void create(GLSLProgram& program);
		void create(VertexBufferObject& vbo);
		//creates VertexAttayObject and it's VertexBufferObject
		void create(VertexArrayObject& vao);
		void upload(VertexBufferObject& vbo, GLenum usage = GL_STATIC_DRAW);
		void createLayout(VertexArrayObject vao);
		void bind(VertexBufferObject& vbo);
		void bind(VertexArrayObject& vao);
		void useProgram(const GLSLProgram& program);

		void setClearColor(const Vector3& color);

		~Renderer();
	private:
		bool initImGui(SDL_Window* window);
		SDL_GLContext _context;
		Window& _window;
	};
}