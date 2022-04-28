#pragma once
#include <Platform.h>
#include <Graphics/Common/BufferObject.h>

namespace Reborn
{
	class GLBufferObject : public BufferObject
	{
	public:
		GLBufferObject(
			void* _data, 
			size_t _size,
			BufferType _type
		) : BufferObject(_data, _size, _type, API_TYPE) {};
		UIntValue id = -1;
	};

	class GLVertexBufferObject : public GLBufferObject
	{
	public:
		GLVertexBufferObject(float* _vertices, size_t _size) :
			GLBufferObject(_vertices, _size * sizeof(float), BufferType::VERTEX_BUFFER),
			size(_size)
		{};
		size_t size = 0;
	};

	struct GLElementBufferObject : public GLBufferObject 
	{
	public:
		GLElementBufferObject(UIntValue* _indices, size_t _size) :
			GLBufferObject(_indices, _size * sizeof(UIntValue), BufferType::ELEMENT_BUFFER),
			size(_size)
		{};
		size_t size = 0;
	};
}