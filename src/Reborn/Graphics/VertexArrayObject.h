#pragma once
#include <SDL_opengl.h>
#include "VertexBufferObject.h"

namespace Reborn {
	struct VertexAttribute
	{
		VertexAttribute(size_t _size, size_t _stride, bool _normalized, GLenum _type) {
			size = _size;
			stride = _stride;
			normalized = _normalized;
			type = _type;
		}
		size_t size;
		size_t stride;
		bool normalized;
		GLenum type;
	};

	struct VertexArrayObject {
		VertexArrayObject(const VertexBufferObject& _vbo, std::vector<VertexAttribute>& _layout): vbo(_vbo), layout(_layout) {}
		VertexBufferObject vbo;
		std::vector<VertexAttribute> layout;
		GLuint id;
	};

}