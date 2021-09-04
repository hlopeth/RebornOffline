#pragma once
#include <SDL_opengl.h>
#include "VertexBufferObject.h"
#include "VertexAttribute.h"

namespace Reborn {
	struct VertexArrayObject {
		VertexArrayObject(
			const VertexBufferObject& _vbo,
			const ElementBufferObject& _ebo,
			std::vector<VertexAttribute>& _layout
		): 
			vbo(_vbo), 
			ebo(_ebo),
			layout(_layout) 
		{}
		VertexBufferObject vbo;
		ElementBufferObject ebo;
		std::vector<VertexAttribute> layout;
		GLuint id = -1;
	};

}