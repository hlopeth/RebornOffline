#pragma once
#include "Graphics/Renderer.h"
#include <SDL_opengl.h>

namespace Reborn {
	class OpenGLRenderer : public Renderer {
	public:
		OpenGLRenderer(const Vector2& sceneFraimbufferSize = Vector2(500, 500));
		virtual void init(Window& window) override;
		virtual void beginFrame() override;
		virtual void endFrame() override;
		virtual void create(GLSLProgram& program) override;
		virtual void create(BufferObject& buf) override;

		virtual void setUniform(const GLSLProgram& program, const GLchar* name, const int& value) override;
		virtual void setUniform(const GLSLProgram& program, const GLchar* name, const float& value) override;
		virtual void setUniform(const GLSLProgram& program, const GLchar* name, const Vector2& value) override;
		virtual void setUniform(const GLSLProgram& program, const GLchar* name, const Vector3& value) override;
		virtual void setUniform(const GLSLProgram& program, const GLchar* name, const Vector4& value) override;
		virtual void setUniform(const GLSLProgram& program, const GLchar* name, const Matrix2& value, bool transpose = true) override;
		virtual void setUniform(const GLSLProgram& program, const GLchar* name, const Matrix3& value, bool transpose = true) override;
		virtual void setUniform(const GLSLProgram& program, const GLchar* name, const Matrix4& value, bool transpose = true) override;

		const SDL_GLContext& getContext();
	private:
		bool initImGui(SDL_Window* window);

		SDL_GLContext _context;
	};
}