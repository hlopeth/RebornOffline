#pragma once
#include "ComponentTypes.h"
#include "ECS/Component.h"
#include <Graphics/Mesh.h>
#include <Graphics/Material.h>

namespace Reborn {
	class RenderComponent : public Component<RenderComponent, ComponentTypes::Render>
	{
	public:
		RenderComponent() = delete;
		RenderComponent(const Mesh& _mesh, Material& _material):
			material(&_material)
		{
			VAOs.push_back(_mesh.getVAO());
		}
		RenderComponent(const Mesh** meshes, size_t numMeshes, Material& _material) :
			material(&_material)
		{
			VAOs.reserve(numMeshes);
			for (int i = 0; i < numMeshes; i++)	{
				VAOs.push_back(meshes[i]->getVAO());
			}
		}
		std::vector<VertexArrayObject> VAOs;
		Material* material;
		bool outline = false;
	};
}