#pragma once
#include <SDL_opengl.h>
#include "Core/Window.h"
#include "VertexArrayObject.h"
#include "GLSLProgram.h"
#include "Framebuffer.h"
#include "Renderbuffer.h"
#include "GLTexture.h"
#include <Math/Matrix.h>
#include <Math/Vector.h>
#include "Mesh.h"
#include "Camera.h"
#include "Backends/RenderBackend_GL.h"
#include "HandleAllocator.h"

namespace Reborn {
	class Renderer {
	public:
		Renderer(Window& window, const Vector2& sceneFraimbufferSize = Vector2(500, 500));
		void beginFrame();
		void endFrame();
		void drawVAO(const VertexArrayObject& vao, GLuint offset = 0);
		void drawMesh(const Mesh& mesh);
		RenderBackend& getRenderBackend();
		Camera& getCamera();
		const Camera& getCamera() const;

		void setUniform(const GLSLProgram& program, const GLchar* name, const int& value);
		void setUniform(const GLSLProgram& program, const GLchar* name, const float& value);
		void setUniform(const GLSLProgram& program, const GLchar* name, const Vector2& value);
		void setUniform(const GLSLProgram& program, const GLchar* name, const Vector3& value);
		void setUniform(const GLSLProgram& program, const GLchar* name, const Vector4& value);
		void setUniform(const GLSLProgram& program, const GLchar* name, const Matrix2& value, bool transpose = true);
		void setUniform(const GLSLProgram& program, const GLchar* name, const Matrix3& value, bool transpose = true);
		void setUniform(const GLSLProgram& program, const GLchar* name, const Matrix4& value, bool transpose = true);

		void create(GLSLProgram& program);
		void create(BufferObject& buf);
		void create(Framebuffer& fbo);
		void create(Renderbuffer& rbo);
		//!!! don't do data copy at the moment. expects data ptr to be valid !!!
		Handler createVertexBuffer(void* data, std::size_t sizeInBytes);
		Handler createIndexBuffer(void* data, std::size_t sizeInBytes);
		//creates VertexAttayObject and it's VertexBufferObject
		void create(VertexArrayObject& vao);
		void create(GLTexture& texture);
		void upload(BufferObject& buf, GLenum usage = GL_STATIC_DRAW);
		void upload(GLTexture& texture, void* data, GLuint mipLevel = 0);
		void upload(Renderbuffer& rbo);
		void updateTextureParameters(GLTexture& texture);
		void setFramebufferTexture(Framebuffer& fbo, GLTexture& texture, GLenum attachment);
		void setFramebufferRenderbuffer(Framebuffer& fbo, Renderbuffer& rbo, GLenum attachment);
		void bind(const BufferObject& buf);
		void bind(const VertexArrayObject& vao);
		void bind(const Framebuffer& fbo);
		void bindMainFramebuffer();
		void bind(GLTexture& texture);
		void bind(Renderbuffer& rbo);
		bool isFramebufferComplete(Framebuffer& fbo);
		void destroy(Framebuffer& fbo);
		void destroy(GLSLProgram& program);
		void destroy(VertexArrayObject& vao);
		void useProgram(const GLSLProgram& program);
		const GLTexture& getSceneTexture();

		void setClearColor(const Vector3& color);

		const Vector2& getSceneFraimbufferSize();
		void setSceneFramebufferSize(const Vector2& newSize);

		~Renderer();

		Vector3 lightColor = Vector3(1.0);
		float lightStr = 1.0;
		Vector3 ambientColor = Vector3(1.0);
		Vector3 outlineColor = Vector3(1.0);
	private:
		bool create(FramebufferAttachment& fboAttachment);
		void attach(Framebuffer& fbo, FramebufferAttachment& fboAttachment);
		bool initImGui(SDL_Window* window);
		SDL_GLContext _context;
		Window& _window;
		Vector2 sceneFraimbufferSize;
		Framebuffer sceneFraimbuffer;
		Framebuffer postprocessFramebuffer;
		Camera _camera;
		VertexArrayObject screenQuadVAO;
		GLSLProgram postprocessPropgram;
		RenderBackend* renderBackend;
	};
}