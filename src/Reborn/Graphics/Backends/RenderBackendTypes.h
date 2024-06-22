#pragma once 
#include "SDL_video.h"
#include <SDL_opengl.h>

#define OPEN_GL_HANDLER OpenGL_Handler
#define NONE_HANDLER None_Handler

namespace Reborn {

	typedef unsigned int Handler;

	const size_t MAX_VERTEX_BUFFERS = 2048;
	const size_t MAX_INDEX_BUFFERS = 2048;
	const size_t MAX_VERTEX_ARRAY_OBJECTS = 2048;
	const size_t MAX_TEXTURES = 2048;
	const size_t MAX_RENDERBUFFERS = 64;

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
}