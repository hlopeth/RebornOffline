#pragma once
#include <ECS/EntitySystem.h>
#include <Components/Transform3DComponent.h>
#include <Components/RenderComponent.h>
#include <Graphics/Renderer.h>
#include <Math/Matrix.h>
#include <Math/MathUtils.h>

namespace Reborn {
	template<std::size_t _ComponentCount, std::size_t _SystemCount>
	class RenderSystem : public EntitySystem<_ComponentCount, _SystemCount> {
	public:
		RenderSystem() {
			setRequirements<Transform3DComponent, RenderComponent>();
		}

		virtual void onManagedEntityAdded([[maybe_unused]] Entity cameraControllerEntity) override {
		};
		virtual void onManagedEntityRemoved([[maybe_unused]] Entity cameraControllerEntity) override {
		};

		void process(Renderer& renderer) {
			
			//Matrix4 proj = perspectiveMatrix(-100, 100, 10, -10, 10, -10);
			//Matrix4 proj = perspectiveFOVMatrix(toRadians(60), 1, -3, 3);
			//Matrix4 proj = orthoMatrix(-100, 100, 10, -10, 10, -10);
			const Matrix4& proj = renderer.getCamera().getViewProjection();

			auto& entityManager = Application::get()->entityManager();
			for (Entity cameraControllerEntity : getManagedEntities()) {
				auto [transform3DComponent, renderComponent] = entityManager.getComponents<Transform3DComponent, RenderComponent>(cameraControllerEntity);
				const Matrix4 transform = transfromMatrix(transform3DComponent.position, transform3DComponent.scale, transform3DComponent.rotation);
				renderer.useProgram(*renderComponent.program);
				Matrix4 mvp = proj * transform;
				renderer.setUniform(*renderComponent.program, "uTransform", mvp, true);
				renderer.drawVAO(renderComponent.vao, 36);
			}
		};
	private:
	};
}