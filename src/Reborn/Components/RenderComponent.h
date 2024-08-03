#pragma once
#include "ComponentTypes.h"
#include "ECS/Component.h"
#include <Graphics/Mesh.h>
#include <Graphics/Material.h>

namespace Reborn {
	class RenderComponent : public Component<RenderComponent, ComponentTypes::Render>
	{
	public:
		struct RenderData {
			RenderData(Handler _VAO, uint32_t _indexCount, uint32_t _offset, Material* const _material) :
				VAO(_VAO),
				indexCount(_indexCount),
				offset(_offset),
				material(_material)
			{};

			Handler VAO;
			uint32_t indexCount;
			uint32_t offset;
			Material* const material;
		};


		RenderComponent() = delete;
		RenderComponent(const Mesh* mesh, Material& material)
		{
			assert(mesh != nullptr, "mesh is null");
			meshes.push_back(mesh);
			materials.push_back(material);
		}
		RenderComponent(const Mesh** inMeshes, size_t numMeshes, const Material** materials, size_t numMaterials)
		{
			meshes.reserve(numMeshes);
			for (int i = 0; i < numMeshes; i++)	{
				assert(inMeshes[i] != nullptr, "mesh is null");
				meshes.push_back(inMeshes[i]);
			}
			this->materials.reserve(numMaterials);
			for (int i = 0; i < numMaterials; i++) {
				this->materials.push_back(*materials[i]);
			}
		}

		void buildRenderData(Renderer& renderer) {
			if (shouldBuildRenderData) {
				renderDatas.reserve(meshes.size());
				for (uint16_t i = 0; i < meshes.size(); i++) {
					const Mesh& mesh = *meshes[i];
					const VertexLayout vertexLayout = mesh.getVertexLayout();
					void* vertexBuffer;
					size_t vertexBufferSize;
					void* indexBuffer;
					size_t indexBufferSize;
					mesh.getVertexBuffer(vertexBuffer, vertexBufferSize);
					mesh.getIndexBuffer(indexBuffer, indexBufferSize);
					Handler VBO = renderer.createVertexBuffer(vertexBuffer, vertexBufferSize);
					Handler EBO = renderer.createIndexBuffer(indexBuffer, indexBufferSize);
					Handler VAO = renderer.createVertexArray(VBO, EBO, mesh.getVertexLayout());
					RenderData renderData(VAO, mesh.indexCount(), 0, &materials[i]);
					renderDatas.push_back(renderData);
				}

				shouldBuildRenderData = false;
			}
		}

		const std::vector<RenderData>& getRenderDatas() {
			return renderDatas;
		}

		std::vector<Material> materials;
		bool outline = false;
	private:
		std::vector<const Mesh*> meshes;
		std::vector<RenderData> renderDatas;
		bool shouldBuildRenderData = true;
	};
}