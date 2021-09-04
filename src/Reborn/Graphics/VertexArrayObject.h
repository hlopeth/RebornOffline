#pragma once
#include <SDL_opengl.h>
#include "VertexBufferObject.h"
#include "VertexAttribute.h"

namespace Reborn {
	struct VertexArrayObject {
		VertexArrayObject(const VertexBufferObject& _vbo, std::vector<VertexAttribute>& _layout): vbo(_vbo), layout(_layout) {}
		VertexBufferObject vbo;
		std::vector<VertexAttribute> layout;
		GLuint id = -1;
	};

}