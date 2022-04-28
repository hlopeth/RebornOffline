#pragma once
#include <Platform.h>
#include <Graphics/Common/Renderer.h>
#include "GLShaderProgram.h"
#include "GLTextureHandler.h"
#include "GLFramebuffer.h"

struct ImDrawData;

namespace Reborn
{
	class GLRenderer: public Renderer
	{
	public:
		GLRenderer(Window& window, const Vector2& sceneFraimbufferSize = Vector2(500, 500));
		void beginFrame();
		void endFrame(ImGuiManager& imguiManager);
		void drawVAO(const VertexArrayObject& vao, UIntValue offset = 0);
		const RenderingContext& getContext();

		void setUniform(const GLShaderProgram& program, const CharValue* name, const float& value);
		void setUniform(const GLShaderProgram& program, const CharValue* name, const int& value);
		void setUniform(const GLShaderProgram& program, const CharValue* name, const Vector2& value);
		void setUniform(const GLShaderProgram& program, const CharValue* name, const Vector3& value);
		void setUniform(const GLShaderProgram& program, const CharValue* name, const Vector4& value);
		void setUniform(const GLShaderProgram& program, const CharValue* name, const Matrix2& value, bool transpose = true);
		void setUniform(const GLShaderProgram& program, const CharValue* name, const Matrix3& value, bool transpose = true);
		void setUniform(const GLShaderProgram& program, const CharValue* name, const Matrix4& value, bool transpose = true);

		GLShaderProgram create(const std::string& vertexSource, const std::string fragmentSource);
		void create(VertexArrayObject& vao);
		void create(GLTextureHandler& texture);
		void upload(BufferObject& buf, EnumValue usage = REBORN_STATIC_DRAW);
		void upload(GLTextureHandler& texture, void* data, UIntValue mipLevel = 0);
		void upload(GLRenderbuffer& rbo);
		void updateTextureParameters(GLTextureHandler& texture);
		void setFramebufferTexture(GLFramebuffer& fbo, GLTextureHandler& texture, EnumValue attachment);
		void setFramebufferRenderbuffer(GLFramebuffer& fbo, GLRenderbuffer& rbo, EnumValue attachment);
		void bind(const BufferObject& buf);
		void bind(const VertexArrayObject& vao);
		void bind(const GLFramebuffer& fbo);
		void bindMainFramebuffer();
		void bind(GLTextureHandler& texture);
		void bind(GLRenderbuffer& rbo);
		bool isFramebufferComplete(GLFramebuffer& fbo);
		void destroy(GLFramebuffer& fbo);
		void destroy(ShaderProgram& program);
		void destroy(VertexArrayObject& vao);
		void useProgram(const ShaderProgram& program);
		const GLTextureHandler& getSceneTexture();
	private:
		bool create(GLFramebufferAttachment& fboAttachment);
		void attach(GLFramebuffer& fbo, GLFramebufferAttachment& fboAttachment);
		RenderingContext context;
		VertexArrayObject screenQuadVAO;
		ShaderProgram postprocessPropgram;
		GLFramebuffer sceneFraimbuffer;
		GLFramebuffer postprocessFramebuffer;
	};
}