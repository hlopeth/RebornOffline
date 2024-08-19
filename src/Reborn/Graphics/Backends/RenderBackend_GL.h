#pragma once
#include "RenderBackend.h"
#include "RenderBackendTypes.h"
#include "Graphics/VertexLayout.h"
#include "Graphics/TextureDescriptor.h"
#include "Math/Matrix.h"
#include "Math/Vector.h"
#include "array"

namespace Reborn {
	class RenderBackend_GL : public RenderBackend {
	public:
		RenderBackend_GL(SDL_GLContext& context);
		~RenderBackend_GL();
		virtual void processComandBuffer();
		virtual const RenderContext_Handler getContext();

		std::array<GLuint, MAX_VERTEX_BUFFERS> gl_vertexBuffers;
		std::array<GLuint, MAX_INDEX_BUFFERS> gl_indexBuffers;
		std::array<GLuint, MAX_VERTEX_ARRAY_OBJECTS> gl_vertexArrayObjects;
		std::array<GLuint, MAX_TEXTURES> gl_Textures;
		std::array<GLuint, MAX_RENDERBUFFERS> gl_Renderbuffers;
		std::array<GLuint, MAX_FRAMEBUFFERS> gl_Framebuffers;
		std::array<GLuint, MAX_SHADERPROGRAMS> gl_ShaderPrograms;
	private:
		void init();
		void createVertexBuffer(Handler handler, std::size_t sizeInBytes, void* data);
		void createIndexBuffer(Handler handler, std::size_t sizeInBytes, void* data);
		void createVertexArrayObject(
			Handler vaoHandler,
			Handler vboHandler,
			Handler eboHandler,
			uint16_t numAttributes,
			const std::vector<VertexLayout::VertexAttribute>& attributes
		);
		void createTexture(Handler handler, const TextureDescriptor& descriptor);
		void createShaderProgram(
			Handler handler,
			const std::string& vertexSource,
			const std::string& fragmentSource
		);
		void deleteShaderProgram(Handler handler);
		void allocateRenderbuffer(Handler handler, RenderbufferDescriptor descriptor);
		SDL_GLContext context;

	};
}