#pragma once
#include <SDL_opengl.h>

namespace Reborn {
	const GLuint GL_POSITION_INDEX = 0;
	const GLuint GL_NORMAL_INDEX = 1;
	const GLuint GL_UV1_INDEX = 2;

	struct VertexAttribute
	{
		VertexAttribute(
			GLuint _index,
			size_t _size,
			GLenum _type,
			bool _normalized,
			size_t _stride,
			int _offset
		);
		GLuint index;
		size_t size;
		size_t stride;
		bool normalized;
		GLenum type;
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