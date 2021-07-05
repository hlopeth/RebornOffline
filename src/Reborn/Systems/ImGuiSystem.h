#pragma once
#include <ECS/EntitySystem.h>
#include <Components/ImGuiComponent.h>
#include <Components/Transform3DComponent.h>
#include <System.h>

#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>

namespace Reborn {
	template<std::size_t _ComponentCount, std::size_t _SystemCount>
	class ImGuiSystem : public EntitySystem<_ComponentCount, _SystemCount> {
	public:
		ImGuiSystem() {
			setRequirements<Transform3DComponent, ImGuiComponent>();
		}

		virtual void onManagedEntityAdded([[maybe_unused]] Entity entity) override {
		};
		virtual void onManagedEntityRemoved([[maybe_unused]] Entity entity) override {
		};

		void process() {
			ImGui_ImplSDL2_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			auto& entityManager = System::get().entityManager();
			for (Entity entity : getManagedEntities()) {
				auto [ transform3DComponent, imGuiComponent ] = entityManager.getComponents<Transform3DComponent, ImGuiComponent>(entity);
				imGuiComponent.onDraw(entity, imGuiComponent);
			}

			ImGui::Render();
		}
	};
}