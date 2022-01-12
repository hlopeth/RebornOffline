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
		RenderComponent(const Mesh& mesh, Material& material)
		{
			VAOs.push_back(mesh.getVAO());
			materials.push_back(material);
		}
		RenderComponent(const Mesh** meshes, size_t numMeshes, const Material** materials, size_t numMaterials)
		{
			VAOs.reserve(numMeshes);
			for (int i = 0; i < numMeshes; i++)	{
				VAOs.push_back(meshes[i]->getVAO());
			}
			this->materials.reserve(numMaterials);
			for (int i = 0; i < numMaterials; i++) {
				this->materials.push_back(*materials[i]);
			}
		}
		std::vector<VertexArrayObject> VAOs;
		std::vector<Material> materials;
		bool outline = false;
	};
}