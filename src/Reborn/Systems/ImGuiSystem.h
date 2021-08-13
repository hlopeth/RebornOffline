#pragma once
#include <ECS/EntitySystem.h>
#include <Components/ImGuiComponent.h>
#include <Components/Transform3DComponent.h>

#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>

namespace Reborn {
	template<std::size_t _ComponentCount, std::size_t _SystemCount>
	class ImGuiSystem : public EntitySystem<_ComponentCount, _SystemCount> {
	public:
		ImGuiSystem() {
			setRequirements<ImGuiComponent>();
		}

		virtual void onManagedEntityAdded([[maybe_unused]] Entity cameraControllerEntity) override {
		};
		virtual void onManagedEntityRemoved([[maybe_unused]] Entity cameraControllerEntity) override {
		};

		void process(SDL_Window &window) {
			ImGui_ImplSDL2_NewFrame(&window);
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			auto& entityManager = Application::get()->entityManager();
			for (Entity cameraControllerEntity : getManagedEntities()) {
				auto imGuiComponent = entityManager.getComponent<ImGuiComponent>(cameraControllerEntity);
				if (imGuiComponent.enable) {
					imGuiComponent.onDraw(cameraControllerEntity, imGuiComponent);
				}
			}

			ImGui::Render();
		}
	};
}