#pragma once
#include <ECS/EntitySystem.h>
#include <Components/Transform3DComponent.h>
#include <Components/RenderComponent.h>
#include <Graphics/Renderer.h>

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
				renderer.useProgram(*renderComponent.program);
				renderer.drawVAO(renderComponent.vao, 3);
			}
		};
	};
}