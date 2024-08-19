#pragma once
#include <SDL_opengl.h>
#include "Core/Window.h"
#include "GLSLProgram.h"
#include "GLTexture.h"
#include <Math/Matrix.h>
#include <Math/Vector.h>
#include "Mesh.h"
#include "Camera.h"
#include "HandleAllocator.h"
#include "VertexLayout.h"
#include "TextureDescriptor.h"
#include "Backends/RenderBackendTypes.h"
#include "Backends/RenderBackend.h"


#if REBORN_RENDER_BACKEND_OPENGL
#include "Backends/RenderBackend_GL.h"
#else 
static_assert(0, "no render backend???");
#endif

namespace Reborn {

	class Renderer {
	public:
		Renderer(Window& window, const Vector2& sceneFraimbufferSize = Vector2(500, 500));
		void beginFrame();
		void endFrame();
		RenderBackend& getRenderBackend();
		Camera& getCamera();
		const Camera& getCamera() const;

		//!!! don't do data copy at the moment. expects data ptr to be valid !!!
		Handler createVertexBuffer(void* data, std::size_t sizeInBytes);
		Handler createIndexBuffer(void* data, std::size_t sizeInBytes);
		Handler createVertexArray(const Handler& vbo, const Handler& ebo, const VertexLayout& layout);
		Handler createTexture(const TextureDescriptor& descriptor);
		Handler createRenderBuffer(const RenderbufferDescriptor& descriptor);
		Handler createFrameBuffer();
		Handler createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
		void deleteSharerProgram(Handler handler);
		void allocateTexture(Handler handler, const TextureDescriptor& descriptor, uint16_t mipLevel, void* data = nullptr);
		void allocateRenderbuffer(Handler handler, const RenderbufferDescriptor& descriptor);
		void attachTextureToFramebuffer(Handler framebufferHandler, Handler textureHandler, const TextureDescriptor& textureDescriptor, const FramebufferAttachmentType& attachment);
		void attachRenderbufferToFramebuffer(Handler framebufferHandler, Handler renderbufferHandler, const FramebufferAttachmentType& attachment);
		void setFramebufferDrawbuffers(Handler framebufferHandler, uint8_t numAttachments, FramebufferAttachmentType attachments[3]);
		void bindFramebuffer(Handler framebuffer = InvalidHandle);
		void bindTexture(Handler texture, const TextureDescriptor& descriptor);
		void bindShaderProgram(Handler shaderProgramHandler);
		void setUniform(Handler shaderProgramHandler, const std::string& name, const int& value);
		void setUniform(Handler shaderProgramHandler, const std::string& name, const float& value);
		void setUniform(Handler shaderProgramHandler, const std::string& name, const Vector2& value);
		void setUniform(Handler shaderProgramHandler, const std::string& name, const Vector3& value);
		void setUniform(Handler shaderProgramHandler, const std::string& name, const Vector4& value);
		void setUniform(Handler shaderProgramHandler, const std::string& name, const Matrix2& value, bool transpose = true);
		void setUniform(Handler shaderProgramHandler, const std::string& name, const Matrix3& value, bool transpose = true);
		void setUniform(Handler shaderProgramHandler, const std::string& name, const Matrix4& value, bool transpose = true);
		void activateTexture(int attachmentIndex);
		void renderVAO(Handler vaoHandler, uint32_t size, uint32_t offset = 0);
		void setViewport(uint16_t x, uint16_t y, uint16_t with, uint16_t height);
		void clear(FramebufferAttachmentType bufferToClear, bool color, bool depth, Vector4 clearColor);
		void create(GLTexture& texture);
		void upload(GLTexture& texture, void* data, GLuint mipLevel = 0);
		void updateTextureParameters(GLTexture& texture);
		void bind(GLTexture& texture);
		void destroy(GLSLProgram& program);
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
		bool initImGui(SDL_Window* window);
		Window& _window;
		Vector2 sceneFraimbufferSize;
		Camera _camera;
		RenderBackend* renderBackend;
		Reborn::Handler framebufferHandler = Reborn::InvalidHandle;
		Reborn::TextureDescriptor colorAttachmentDescriptor;
		Reborn::Handler colorAttachmentHandler = Reborn::InvalidHandle;
		Reborn::TextureDescriptor outlinedGeomTextureDescriptor;
		Reborn::Handler outlinedGeomAttachmentHandler = Reborn::InvalidHandle;
		Reborn::RenderbufferDescriptor depthStensilDescriptor;
		Reborn::Handler depthStensilHandler = Reborn::InvalidHandle;

		Reborn::Handler postprocessFramebufferHandler = Reborn::InvalidHandle;
		Reborn::TextureDescriptor postprocessTextureDescriptor;
		Reborn::Handler postprocessTextureHandler = Reborn::InvalidHandle;

		Reborn::Handler postprocessProgrammHandler = Reborn::InvalidHandle;

		Reborn::Handler screenQuadVAOHandler = Reborn::InvalidHandle;

		Vector4 clearColor = { 0, 0, 0, 1 };
	};
}