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

		virtual void onManagedEntityAdded([[maybe_unused]] Entity entity) override {
		};
		virtual void onManagedEntityRemoved([[maybe_unused]] Entity entity) override {
		};

		void process(Renderer& renderer) {
			//Matrix4 proj = perspectiveMatrix(-100, 100, 10, -10, 10, -10).transpose();
			Matrix4 proj = perspectiveFOVMatrix(60, 1, -3, 3).transpose();
			//Matrix4 proj = orthoMatrix(-10, 10, 10, -10, 10, -10).transpose();

			auto& entityManager = Application::get()->entityManager();
			for (Entity entity : getManagedEntities()) {
				auto [transform3DComponent, renderComponent] = entityManager.getComponents<Transform3DComponent, RenderComponent>(entity);
				const Matrix4 transform = transfromMatrix(transform3DComponent.position, transform3DComponent.scale, transform3DComponent.rotation);
				renderer.useProgram(*renderComponent.program);
				//LOG_DEBUG << transform;
				Matrix4 mvp = proj * transform;
				renderer.setUniform(*renderComponent.program, "uTransform",  mvp);
				renderer.drawVAO(renderComponent.vao, 36);
			}
		};
	private:
		Matrix4 calculateTransform(const Transform3DComponent& transformComponent) {
			Matrix4 transform = rotation(transformComponent.rotation)
				.scale(transformComponent.scale)
				.translate(transformComponent.position);
			return transform;
		}
	};
}