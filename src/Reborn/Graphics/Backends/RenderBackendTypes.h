#pragma once 
#include "SDL_video.h"
#include <SDL_opengl.h>

#define OPEN_GL_HANDLER OpenGL_Handler
#define NONE_HANDLER None_Handler

namespace Reborn {

	typedef uint32_t Handler;

	const size_t MAX_VERTEX_BUFFERS = 2048;
	const size_t MAX_INDEX_BUFFERS = 2048;
	const size_t MAX_VERTEX_ARRAY_OBJECTS = 2048;
	const size_t MAX_TEXTURES = 2048;
	const size_t MAX_RENDERBUFFERS = 64;
	const size_t MAX_FRAMEBUFFERS = 16;
	const size_t MAX_SHADERPROGRAMS = 1024;

	enum BackendType {
		OPEN_GL,
		NONE
	};

	union RenderContext_Handler	{
		SDL_GLContext OPEN_GL_HANDLER;
		char NONE_HANDLER;
	};

	union BufferObject_Handler {
		GLuint OPEN_GL_HANDLER;
		char NONE_HANDLER;
	};

	enum class FramebufferAttachmentType {
		colorAttachment0 = GL_COLOR_ATTACHMENT0,
		colorAttachment1 = GL_COLOR_ATTACHMENT1,
		colorAttachment2 = GL_COLOR_ATTACHMENT2,
		depthStensilAttachment = GL_DEPTH_STENCIL_ATTACHMENT,
		emptyAttachment = 0
	};

	enum struct UniformValueType {
		INT,
		FLOAT,
		VECTOR2F,
		VECTOR3F,
		VECTOR4F,
		MATRIX2F,
		MATRIX3F,
		MATRIX4F,
		COUNT
	};
}