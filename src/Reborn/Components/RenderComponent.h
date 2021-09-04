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
			mesh(&_mesh),
			program(&_program)
		{}
		const Mesh* mesh;
		const GLSLProgram* program;
	};
}