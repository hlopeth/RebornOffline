#pragma once
#include <SDL_opengl.h>

namespace Reborn {
	struct VertexBufferObject {
	public:
		VertexBufferObject(std::shared_ptr<float[]> _vertices, size_t _size) {
			vertices = _vertices;
			size = _size;
		};
		std::shared_ptr<float[]> vertices = nullptr;
		size_t size = 0;
		GLuint id = -1;
	};
}