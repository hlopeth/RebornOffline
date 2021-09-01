#pragma once
#include <SDL_opengl.h>
#include "VertexBufferObject.h"

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
		) {
			index = _index;
			size = _size;
			stride = _stride;
			normalized = _normalized;
			type = _type;
			offset = _offset;
		}
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

	VertexAttribute normalVertexAttribute(
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

	VertexAttribute uv1VertexAttribute(
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

	struct VertexArrayObject {
		VertexArrayObject(const VertexBufferObject& _vbo, std::vector<VertexAttribute>& _layout): vbo(_vbo), layout(_layout) {}
		VertexBufferObject vbo;
		std::vector<VertexAttribute> layout;
		GLuint id;
	};

}