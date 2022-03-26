#pragma once
#include "VertexBufferObject.h"
#include "VertexAttribute.h"

namespace Reborn {
	struct VertexArrayObject {
		VertexArrayObject() = default;
		VertexArrayObject(
			const VertexBufferObject& _vbo,
			const ElementBufferObject& _ebo,
			std::vector<VertexAttribute>& _layout
		): 
			vbo(_vbo), 
			ebo(_ebo),
			layout(_layout) 
		{}
		VertexBufferObject vbo = VertexBufferObject(nullptr, 0);
		ElementBufferObject ebo = ElementBufferObject(nullptr, 0);
		std::vector<VertexAttribute> layout;
		UIntValue id = -1;
	};

}