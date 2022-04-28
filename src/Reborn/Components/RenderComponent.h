#pragma once
#include <Platform.h>
#include "ComponentTypes.h"
#include "ECS/Component.h"
#include <Graphics/Common/Mesh.h>
#include <Graphics/Common/Material.h>

#ifdef REBORN_OPENGL
#include <Graphics/Platform/OpenGL/GLVertexArrayObject.h>
#endif // REBORN_OPENGL


namespace Reborn {
	class RenderComponent : public Component<RenderComponent, ComponentTypes::Render>
	{
	public:
		RenderComponent() = delete;
		RenderComponent(const Mesh& mesh, Material& material);
		RenderComponent(const Mesh** meshes, size_t numMeshes, const Material** materials, size_t numMaterials)
		{
			VAOs.reserve(numMeshes);
			for (int i = 0; i < numMeshes; i++)	{
				VAOs.push_back(createVAO(*meshes[i]));
			}
			this->materials.reserve(numMaterials);
			for (int i = 0; i < numMaterials; i++) {
				this->materials.push_back(*materials[i]);
			}
		}

#ifdef REBORN_OPENGL
		std::vector<GLVertexArrayObject> VAOs;
		GLVertexArrayObject createVAO(const Mesh&);
#endif // REBORN_OPENGL
		std::vector<Material> materials;
		bool outline = false;
	};
}