#pragma once
#include "Types.h"

namespace Reborn 
{
	const uint16_t REBORN_POSITION_INDEX = 0;
	const uint16_t REBORN_NORMAL_INDEX = 1;
	const uint16_t REBORN_UV1_INDEX = 2;

	struct VertexAttribute
	{
		VertexAttribute(
			uint32_t _index,
			size_t _size,
			VertexType _type,
			bool _normalized,
			size_t _stride,
			int _offset
		);

		uint32_t index;
		size_t size;
		size_t stride;
		bool normalized;
		VertexType type;
		int offset;
	};

	VertexAttribute positionVertexAttribute(
		bool normalized,
		size_t stride,
		int offset
	);

	VertexAttribute normalVertexAttribute(
		bool normalized,
		size_t stride,
		int offset
	);

	VertexAttribute uv1VertexAttribute(
		bool normalized,
		size_t stride,
		int offset
	);
}