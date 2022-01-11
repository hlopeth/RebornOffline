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
		RenderSystem(EntityManager& _entityManager): entityManager(_entityManager) {
			setRequirements<Transform3DComponent, RenderComponent>();
		}

		virtual void onManagedEntityAdded([[maybe_unused]] Entity entity) override {
		};
		virtual void onManagedEntityRemoved([[maybe_unused]] Entity entity) override {
		};

		void process(Renderer& renderer) {			
			const Matrix4& proj = renderer.getCamera().getViewProjection();

			for (Entity entity : getManagedEntities()) {
				auto& transform3DComponent = entityManager.getComponent<Transform3DComponent>(entity);
				auto& renderComponent = entityManager.getComponent<RenderComponent>(entity);
				//auto [transform3DComponent, renderComponent] = entityManager.getComponents<Transform3DComponent, RenderComponent>(cameraControllerEntity);
				//const Matrix4& model = transform3DComponent.getModelMatrix();
				const Matrix4 world = transform3DComponent.world;
				Matrix4 mvp = proj * world;
				renderComponent.material->setParameter("uTransform", mvp);
				renderComponent.material->setParameter("uModel", world);
				renderComponent.material->setParameter("uLightColor", renderer.lightColor * renderer.lightStr);
				renderComponent.material->setParameter("uAmbientColor", renderer.ambientColor);
				renderComponent.material->setParameter("uOutlined", 1.f);
				renderComponent.material->setup(renderer);

				for (int i = 0; i < renderComponent.VAOs.size(); i++) {
					renderer.drawVAO(renderComponent.VAOs[i]);
				}
			}
		};
	private:
		EntityManager& entityManager;
	};
}