#pragma once
#include "ComponentTypes.h"
#include "ECS/Component.h"
#include <Graphics/VertexArrayObject.h>
#include <Graphics/GLSLProgram.h>

namespace Reborn {
	class RenderComponent : public Component<RenderComponent, ComponentTypes::Render>
	{
	public:
		RenderComponent() = delete;
		RenderComponent(const VertexArrayObject& _vao, const GLSLProgram& _program):
			vao(_vao),
			program(_program)
		{

		}
		VertexArrayObject vao;
		GLSLProgram program;
	};
}