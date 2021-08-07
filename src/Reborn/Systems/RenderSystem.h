#pragma once
#include <ECS/EntitySystem.h>
#include <Components/Transform3DComponent.h>
#include <Components/RenderComponent.h>
#include <Graphics/Renderer.h>
#include <Math/Matrix.h>

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
			auto& entityManager = Application::get()->entityManager();
			for (Entity entity : getManagedEntities()) {
				auto [transform3DComponent, renderComponent] = entityManager.getComponents<Transform3DComponent, RenderComponent>(entity);
				const Matrix4 transform = calculateTransform(transform3DComponent);
				renderer.useProgram(*renderComponent.program);
				LOG_DEBUG << transform;
				renderer.setUniform(*renderComponent.program, "uTransform", transform);
				renderer.drawVAO(renderComponent.vao, 3);
			}
		};
	private:
		Matrix4 calculateTransform(const Transform3DComponent& transformComponent) {
			Matrix4 transform = Matrix4::one();
			transform
				.rotateX(transformComponent.rotation.x)
				.rotateY(transformComponent.rotation.y)
				.rotateZ(transformComponent.rotation.z)
				.scale(transformComponent.scale)
				.translate(transformComponent.position);
			return transform;
		}
	};
}