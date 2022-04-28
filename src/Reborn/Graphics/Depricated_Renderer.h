#pragma once
#include "Platform.h"
#include "Core/Window.h"
#include "VertexArrayObject.h"
#include "Framebuffer.h"
#include "Renderbuffer.h"
#include <Math/Matrix.h>
#include <Math/Vector.h>
#include "Mesh.h"
#include "Camera.h"
#include <Core/ImGuiManager.h>
#include "ShaderProgram.h"
#include "TextureHandler.h"

struct ImDrawData;


namespace Reborn {
	class Renderer {
	public:
		Renderer(Window& window, const Vector2& sceneFraimbufferSize = Vector2(500, 500));
		void beginFrame();
		void endFrame(ImGuiManager& imguiManager);
		void drawVAO(const VertexArrayObject& vao, UIntValue offset = 0);
		void drawMesh(const Mesh& mesh);
		const RenderingContext& getContext();
		Camera& getCamera();
		const Camera& getCamera() const;

		void setUniform(const ShaderProgram& program, const CharValue* name, const float& value);
		void setUniform(const ShaderProgram& program, const CharValue* name, const int& value);
		void setUniform(const ShaderProgram& program, const CharValue* name, const Vector2& value);
		void setUniform(const ShaderProgram& program, const CharValue* name, const Vector3& value);
		void setUniform(const ShaderProgram& program, const CharValue* name, const Vector4& value);
		void setUniform(const ShaderProgram& program, const CharValue* name, const Matrix2& value, bool transpose = true);
		void setUniform(const ShaderProgram& program, const CharValue* name, const Matrix3& value, bool transpose = true);
		void setUniform(const ShaderProgram& program, const CharValue* name, const Matrix4& value, bool transpose = true);

		void create(ShaderProgram& program);
		void create(BufferObject& buf);
		void create(Framebuffer& fbo);
		void create(Renderbuffer& rbo);
		//creates VertexAttayObject and it's VertexBufferObject
		void create(VertexArrayObject& vao);
		void create(TextureHandler& texture);
		void upload(BufferObject& buf, EnumValue usage = REBORN_STATIC_DRAW);
		void upload(TextureHandler& texture, void* data, UIntValue mipLevel = 0);
		void upload(Renderbuffer& rbo);
		void updateTextureParameters(TextureHandler& texture);
		void setFramebufferTexture(Framebuffer& fbo, TextureHandler& texture, EnumValue attachment);
		void setFramebufferRenderbuffer(Framebuffer& fbo, Renderbuffer& rbo, EnumValue attachment);
		void bind(const BufferObject& buf);
		void bind(const VertexArrayObject& vao);
		void bind(const Framebuffer& fbo);
		void bindMainFramebuffer();
		void bind(TextureHandler& texture);
		void bind(Renderbuffer& rbo);
		bool isFramebufferComplete(Framebuffer& fbo);
		void destroy(Framebuffer& fbo);
		void destroy(ShaderProgram& program);
		void destroy(VertexArrayObject& vao);
		void useProgram(const ShaderProgram& program);
		const TextureHandler& getSceneTexture();

		void setClearColor(const Vector3& color);

		const Vector2& getSceneFraimbufferSize();
		void setSceneFramebufferSize(const Vector2& newSize);

		//imGui
		bool initImGui(SDL_Window* window);
		void newImGuiFrame();
		void drawImGui(ImDrawData* drawData);
		void destroyImGui();

		~Renderer();

		Vector3 lightColor = Vector3(1.0);
		float lightStr = 1.0;
		Vector3 ambientColor = Vector3(1.0);
		Vector3 outlineColor = Vector3(1.0);
	private:
		bool create(FramebufferAttachment& fboAttachment);
		void attach(Framebuffer& fbo, FramebufferAttachment& fboAttachment);
		RenderingContext _context;
		Window& _window;
		Vector2 sceneFraimbufferSize;
		Framebuffer sceneFraimbuffer;
		Framebuffer postprocessFramebuffer;
		Camera _camera;
		VertexArrayObject screenQuadVAO;
		ShaderProgram postprocessPropgram;

#ifdef REBORN_DIRECTX11
		ID3D11RenderTargetView* renderTargetView;
#endif // REBORN_DIRECTX11

	};
}