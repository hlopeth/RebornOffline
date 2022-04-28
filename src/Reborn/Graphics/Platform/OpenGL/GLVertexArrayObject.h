#pragma once
#include <Platform.h>
#include <Graphics/Common/VertexArrayObject.h>
#include <Graphics/Common/VertexAttribute.h>
#include "GLBufferObject.h"

namespace Reborn 
{
	class GLVertexArrayObject : public VertexArrayObject
	{
	public:
		GLVertexArrayObject(
			const GLVertexBufferObject& _vbo,
			const GLElementBufferObject& _ebo,
			std::vector<VertexAttribute>& _layout
		) :
			VertexArrayObject(API_TYPE),
			vbo(_vbo),
			ebo(_ebo),
			layout(_layout)
		{}
		GLVertexBufferObject vbo = GLVertexBufferObject(nullptr, 0);
		GLElementBufferObject ebo = GLElementBufferObject(nullptr, 0);
		std::vector<VertexAttribute> layout;
		UIntValue id = -1;
	};

}