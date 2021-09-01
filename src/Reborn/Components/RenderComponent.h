#pragma once
#include "ComponentTypes.h"
#include "ECS/Component.h"
#include <Graphics/Mesh.h>
#include <Graphics/GLSLProgram.h>

namespace Reborn {
	class RenderComponent : public Component<RenderComponent, ComponentTypes::Render>
	{
	public:
		RenderComponent() = delete;
		RenderComponent(const Mesh& _mesh, const GLSLProgram& _program):
			mesh(_mesh), //TODO copy!!!
			program(&_program)
		{

		}
		Mesh mesh;
		const GLSLProgram* program;
	};
}