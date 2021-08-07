#pragma once
#include <SDL_opengl.h>

namespace Reborn {
	class GLSLProgram {
	public:
		GLSLProgram() = default;
		GLSLProgram(const std::string& _vertexSource, const std::string& _fragmentSource) {
			vertexSource = _vertexSource;
			fragmentSource = _fragmentSource;
		};
		std::string vertexSource;
		std::string fragmentSource;
		GLuint id = -1;
	};
}