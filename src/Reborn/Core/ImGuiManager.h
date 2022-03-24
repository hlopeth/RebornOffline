#pragma once
#include <SDL_events.h>

namespace Reborn {
	class Renderer;
	class Window;

	class ImGuiManager {
	public:
		ImGuiManager() = default;

		void init(Renderer& renderer, Window& window);
		void render(Renderer& renderer);
		void processEvent(SDL_Event& evt);
		void destroy(Renderer& renderer);
	private:
		bool initialized = false;
	};
}