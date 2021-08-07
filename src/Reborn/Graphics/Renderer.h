#pragma once
#include <SDL_opengl.h>
#include "Core/Window.h"
#include "VertexArrayObject.h"
#include "GLSLProgram.h"
#include "Framebuffer.h"
#include "Renderbuffer.h"
#include "GLTexture.h"
#include "Math/Vector.h"

namespace Reborn {
	class Renderer {
	public:
		Renderer(Window& window, const Vector2& sceneFraimbufferSize = Vector2(500, 500));
		void beginFrame();
		void endFrame();
		void drawVAO(VertexArrayObject& vao, GLuint vertices, GLuint offset = 0);
		const SDL_GLContext& getContext();
		void create(GLSLProgram& program);
		void create(VertexBufferObject& vbo);
		void create(Framebuffer& fbo);
		void create(Renderbuffer& rbo);
		//creates VertexAttayObject and it's VertexBufferObject
		void create(VertexArrayObject& vao);
		void create(GLTexture& texture);
		void upload(VertexBufferObject& vbo, GLenum usage = GL_STATIC_DRAW);
		void upload(GLTexture& texture, void* data, GLuint mipLevel = 0);
		void upload(Renderbuffer& rbo);
		void createLayout(VertexArrayObject vao);
		void updateTextureParameters(GLTexture& texture);
		void setFramebufferTexture(Framebuffer& fbo, GLTexture& texture, GLenum attachment);
		void setFramebufferRenderbuffer(Framebuffer& fbo, Renderbuffer& rbo, GLenum attachment);
		void bind(VertexBufferObject& vbo);
		void bind(VertexArrayObject& vao);
		void bind(Framebuffer& fbo);
		void bindMainFramebuffer();
		void bind(GLTexture& texture);
		void bind(Renderbuffer& rbo);
		bool isFramebufferComplete(Framebuffer& fbo);
		void destroy(Framebuffer& fbo);
		void destroy(GLSLProgram& program);
		void useProgram(const GLSLProgram& program);
		const GLTexture& getSceneTexture();

		void setClearColor(const Vector3& color);

		const Vector2& getSceneFraimbufferSize();
		void setSceneFramebufferSize(const Vector2& newSize);

		~Renderer();
	private:
		bool initImGui(SDL_Window* window);
		SDL_GLContext _context;
		Window& _window;
		Vector2 sceneFraimbufferSize;
		Framebuffer sceneFraimbuffer;
		GLTexture colorAttachmentTexture;
		Renderbuffer depthStencilRenderbuffer;
	};
}