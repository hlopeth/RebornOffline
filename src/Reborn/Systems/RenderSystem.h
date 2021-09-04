#pragma once
#include <ECS/EntitySystem.h>
#include <Components/Transform3DComponent.h>
#include <Components/RenderComponent.h>
#include <Graphics/Renderer.h>
#include <Math/Matrix.h>
#include <Math/MathUtils.h>
#include <Utils.h>

namespace Reborn {
	class RenderSystem : public EntitySystem {
	public:
		RenderSystem() {
			setRequirements<Transform3DComponent, RenderComponent>();
		}

		virtual void onManagedEntityAdded([[maybe_unused]] Entity entity) override {
			auto& entityManager = Application::get()->entityManager();
			auto& renderComponent = entityManager.getComponent<RenderComponent>(entity);
			Mesh* meshRef = &renderComponent.mesh;

			auto search = meshToVAO.find(meshRef);
			if (search == meshToVAO.end()) {
				meshToVAO.insert({ meshRef, RefCounter<VertexArrayObject>(meshRef->getVAO()) });
				vaoToCreate.push_back(&meshToVAO.at(meshRef).data);
			} else {
				search->second.addRef();
			}
		};
		virtual void onManagedEntityRemoved([[maybe_unused]] Entity entity) override {
			auto& entityManager = Application::get()->entityManager();
			auto& renderComponent = entityManager.getComponent<RenderComponent>(entity);
			Mesh* meshRef = &renderComponent.mesh;

			auto search = meshToVAO.find(meshRef);
			if (search == meshToVAO.end()) {
				LOG_WARN << "RenderSystem::onManagedEntityRemoved: VertexArrayObject was deleted before RenderComponent";
			} else {
				RefCounter<VertexArrayObject>& refCounter = search->second;
				refCounter.removeRef();

				if (!refCounter.hasRefs()) {
					std::remove(vaoToCreate.begin(), vaoToCreate.end(), &refCounter.data);
					meshToVAO.erase(search);
					Application::get()->renderer().destroy(refCounter.data);
				}
			}
		};

		void process(Renderer& renderer) {

			for (auto i = 0; i < vaoToCreate.size(); i++) {
				renderer.create(*vaoToCreate[i]);
			}
			vaoToCreate.clear();

			for (auto i = 0; i < vaoToDestroy.size(); i++) {
				renderer.destroy(vaoToDestroy[i]);
			}
			vaoToDestroy.clear();
			
			const Matrix4& proj = renderer.getCamera().getViewProjection();

			auto& entityManager = Application::get()->entityManager();
			for (Entity entity : getManagedEntities()) {
				auto& transform3DComponent = entityManager.getComponent<Transform3DComponent>(entity);
				auto& renderComponent = entityManager.getComponent<RenderComponent>(entity);
				//auto [transform3DComponent, renderComponent] = entityManager.getComponents<Transform3DComponent, RenderComponent>(cameraControllerEntity);
				const Matrix4 transform = transfromMatrix(transform3DComponent.position, transform3DComponent.scale, transform3DComponent.rotation);
				renderer.useProgram(*renderComponent.program);
				Matrix4 mvp = proj * transform;
				renderer.setUniform(*renderComponent.program, "uTransform", mvp, true);
				renderer.setUniform(*renderComponent.program, "uNormalTransform", transform.inverse(), false);
				renderer.setUniform(*renderComponent.program, "uLightColor", renderer.lightColor * renderer.lightStr);
				renderer.setUniform(*renderComponent.program, "uAmbientColor", renderer.ambientColor);
				renderer.drawVAO(meshToVAO.at(&renderComponent.mesh).data, renderComponent.mesh.vertexCount());
			}
		};
	private:
		std::unordered_map<Mesh*, RefCounter<VertexArrayObject>> meshToVAO;
		std::vector<VertexArrayObject*> vaoToCreate;
		std::vector<VertexArrayObject> vaoToDestroy;
	};
}