#pragma once
#include "Platform.h"

namespace Reborn {
	const UIntValue REBORN_POSITION_INDEX = 0;
	const UIntValue REBORN_NORMAL_INDEX = 1;
	const UIntValue REBORN_UV1_INDEX = 2;

	struct VertexAttribute
	{
		VertexAttribute(
			UIntValue _index,
			size_t _size,
			EnumValue _type,
			bool _normalized,
			size_t _stride,
			int _offset
		);
		UIntValue index;
		size_t size;
		size_t stride;
		bool normalized;
		EnumValue type;
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