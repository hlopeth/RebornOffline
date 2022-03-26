#pragma once
#include "Platform.h"

namespace Reborn {
	struct BufferObject {
		BufferObject(void* _data, size_t _size, EnumValue _type) :
			data(_data),
			byteSize(_size),
			type(_type)
		{};
		void* data = nullptr;
		size_t byteSize = 0;
		EnumValue type = 0;
		UIntValue id = -1;
	};

	struct VertexBufferObject: BufferObject {
		VertexBufferObject(float* _vertices, size_t _size):
			BufferObject(_vertices, _size * sizeof(float), REBORN_ARRAY_BUFFER),
			size(_size)
		{};
		size_t size = 0;
	};

	struct ElementBufferObject: BufferObject {
		ElementBufferObject(UIntValue* _indices, size_t _size):
			BufferObject(_indices, _size * sizeof(UIntValue), REBORN_ELEMENT_ARRAY_BUFFER),
			size(_size)
		{};
		size_t size = 0;
	};
}