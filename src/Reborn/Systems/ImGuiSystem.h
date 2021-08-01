#pragma once
#include <ECS/EntitySystem.h>
#include <Components/ImGuiComponent.h>
#include <Components/Transform3DComponent.h>
#include "Core/System.h"

#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>

namespace Reborn {
	template<std::size_t _ComponentCount, std::size_t _SystemCount>
	class ImGuiSystem : public EntitySystem<_ComponentCount, _SystemCount> {
	public:
		ImGuiSystem() {
			setRequirements<ImGuiComponent>();
		}

		virtual void onManagedEntityAdded([[maybe_unused]] Entity entity) override {
		};
		virtual void onManagedEntityRemoved([[maybe_unused]] Entity entity) override {
		};

		void process(SDL_Window &window) {
			ImGui_ImplSDL2_NewFrame(&window);
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			auto& entityManager = System::get().entityManager();
			for (Entity entity : getManagedEntities()) {
				auto imGuiComponent = entityManager.getComponent<ImGuiComponent>(entity);
				imGuiComponent.onDraw(entity, imGuiComponent);
			}

			ImGui::Render();
		}
	};
}