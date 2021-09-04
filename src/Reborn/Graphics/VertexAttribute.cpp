#include <Core.h>
#include "VertexAttribute.h"

using namespace Reborn;

VertexAttribute::VertexAttribute(
	GLuint _index,
	size_t _size,
	GLenum _type,
	bool _normalized,
	size_t _stride,
	int _offset
) {
	index = _index;
	size = _size;
	stride = _stride;
	normalized = _normalized;
	type = _type;
	offset = _offset;
}

VertexAttribute Reborn::positionVertexAttribute(
	bool normalized,
	size_t stride,
	int offset
) {
	return VertexAttribute(
		GL_POSITION_INDEX,
		3,
		GL_FLOAT,
		normalized,
		stride,
		offset
	);
}

VertexAttribute Reborn::normalVertexAttribute(
	bool normalized,
	size_t stride,
	int offset
) {
	return VertexAttribute(
		GL_NORMAL_INDEX,
		3,
		GL_FLOAT,
		normalized,
		stride,
		offset
	);
}

VertexAttribute Reborn::uv1VertexAttribute(
	bool normalized,
	size_t stride,
	int offset
) {
	return VertexAttribute(
		GL_UV1_INDEX,
		2,
		GL_FLOAT,
		normalized,
		stride,
		offset
	);
}