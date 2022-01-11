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
			program(&_program)
		{
			VAOs.push_back(_mesh.getVAO());
		}
		RenderComponent(const Mesh** meshes, size_t numMeshes, const GLSLProgram& _program) :
			program(&_program)
		{
			VAOs.reserve(numMeshes);
			for (int i = 0; i < numMeshes; i++)
			{
				VAOs.push_back(meshes[i]->getVAO());
			}
		}
		std::vector<VertexArrayObject> VAOs;
		const GLSLProgram* program;
		bool outline = false;
	};
}