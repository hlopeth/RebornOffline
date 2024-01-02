#pragma once
#include "Backends/RenderBackendTypes.h"

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


	enum BufferObject_Type {
		ARRAY_BUFFER,
		INDEX_BUFFER
	};

	struct BufferObject1 {
		BufferObject1(size_t _sizeInBytes, BufferObject_Type _type) :
			sizeInBytes(_sizeInBytes),
			type(_type)
		{};
		size_t sizeInBytes = 0;
		BufferObject_Type type;
		BufferObject_Handler id;
	};

	struct VertexBufferObject1 : BufferObject1 {
		VertexBufferObject1(size_t sizeInBytes) :
			BufferObject1(sizeInBytes, BufferObject_Type::ARRAY_BUFFER)
		{};
	};

	struct ElementBufferObject1 : BufferObject1 {
		ElementBufferObject1(size_t sizeInBytes) :
			BufferObject1(sizeInBytes, BufferObject_Type::INDEX_BUFFER)
		{};
	};

}