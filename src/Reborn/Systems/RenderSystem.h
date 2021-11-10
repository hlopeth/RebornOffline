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
		};
		virtual void onManagedEntityRemoved([[maybe_unused]] Entity entity) override {
		};

		void process(Renderer& renderer) {			
			const Matrix4& proj = renderer.getCamera().getViewProjection();

			auto& entityManager = Application::get()->entityManager();
			for (Entity entity : getManagedEntities()) {
				auto& transform3DComponent = entityManager.getComponent<Transform3DComponent>(entity);
				auto& renderComponent = entityManager.getComponent<RenderComponent>(entity);
				//auto [transform3DComponent, renderComponent] = entityManager.getComponents<Transform3DComponent, RenderComponent>(cameraControllerEntity);
				const Matrix4& model = transform3DComponent.getModelMatrix();
				renderer.useProgram(*renderComponent.program);
				Matrix4 mvp = proj * model;
				renderer.setUniform(*renderComponent.program, "uTransform", mvp, true);
				renderer.setUniform(*renderComponent.program, "uModel", model, true);
				renderer.setUniform(*renderComponent.program, "uLightColor", renderer.lightColor * renderer.lightStr);
				renderer.setUniform(*renderComponent.program, "uAmbientColor", renderer.ambientColor);
				renderer.setUniform(*renderComponent.program, "uOutlined", 1.f);

				renderer.drawVAO(renderComponent.vao);
			}
		};
	private:
	};
}