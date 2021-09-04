#pragma once
#include <SDL_opengl.h>

namespace Reborn {
	struct BufferObject {
		BufferObject(void* _data, size_t _size, GLenum _type) :
			data(_data),
			byteSize(_size),
			type(_type)
		{};
		void* data = nullptr;
		size_t byteSize = 0;
		GLenum type = 0;
		GLuint id = -1;
	};

	struct VertexBufferObject: BufferObject {
		VertexBufferObject(float* _vertices, size_t _size):
			BufferObject(_vertices, _size * sizeof(float), GL_ARRAY_BUFFER),
			size(_size)
		{};
		size_t size = 0;
	};

	struct ElementBufferObject: BufferObject {
		ElementBufferObject(GLuint* _indices, size_t _size):
			BufferObject(_indices, _size * sizeof(GLuint), GL_ELEMENT_ARRAY_BUFFER),
			size(_size)
		{};
		size_t size = 0;
	};
}