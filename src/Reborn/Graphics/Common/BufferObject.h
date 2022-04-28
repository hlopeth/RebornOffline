#pragma once
#include "GraphicsResource.h"
#include "Types.h"

namespace Reborn 
{
	class BufferObject: public GrahicsResource
	{
	public:
		BufferObject(void* _data, size_t _size, BufferType _type, APIType apiType) :
			GrahicsResource(apiType),
			data(_data),
			byteSize(_size),
			type(_type)
		{};

		void* data = nullptr;
		size_t byteSize = 0;
		BufferType type = BufferType::UNDEFINED;
	};
}