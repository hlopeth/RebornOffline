#include <Core.h>
#include "RenderComponent.h"

#ifdef REBORN_OPENGL
#endif

namespace Reborn
{
	RenderComponent::RenderComponent(const Mesh& mesh, Material& material)
	{
		VAOs.push_back(createVAO(mesh));
		materials.push_back(material);
	}

	RenderComponent::RenderComponent(const Mesh** meshes, size_t numMeshes, const Material** materials, size_t numMaterials)
	{
		VAOs.reserve(numMeshes);
		for (int i = 0; i < numMeshes; i++) {
			VAOs.push_back(createVAO(*meshes[i]));
		}
		this->materials.reserve(numMaterials);
		for (int i = 0; i < numMaterials; i++) {
			this->materials.push_back(*materials[i]);
		}
	}

#ifdef REBORN_OPENGL
	GLVertexArrayObject RenderComponent::createVAO(const Mesh& mesh)
	{
		int vertexSize = mesh.hasPositions()  * 3 + mesh.hasNormals() * 3 + mesh.hasUV1() * 2;
		GLVertexBufferObject vbo(mesh.vertexData(), mesh.vertexCount() * vertexSize);
		GLElementBufferObject ebo(mesh.indices(), mesh.indexCount());
		std::vector<VertexAttribute> attributes;
		
		if (mesh.hasPositions()) {
		    attributes.push_back(positionVertexAttribute(false, 0, mesh.positionsOffset()));
		}
		if (mesh.hasNormals()) {
		    attributes.push_back(normalVertexAttribute(false, 0, mesh.normalsOffset()));
		}
		if (mesh.hasUV1()) {
		    attributes.push_back(uv1VertexAttribute(false, 0, mesh.uv1Offset()));
		}    
		return GLVertexArrayObject(vbo, ebo, attributes);

	}
#endif // REBORN_OPENGL
}