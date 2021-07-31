#pragma once
#include <SDL_opengl.h>

namespace Reborn {
	struct Renderbuffer {
		GLsizei width;
		GLsizei height;
		GLenum internalFormat;
		GLuint id;
	};
}