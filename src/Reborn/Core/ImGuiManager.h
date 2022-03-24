#pragma once
#include <SDL_events.h>

namespace Reborn {
	class Renderer;
	class Window;

	class ImGuiManager {
	public:
		ImGuiManager() = default;

		void init(Renderer* renderer, Window* window);
		//return false when imGui system not initialized and no imgui should be drawn
		bool newFrame();
		void render();
		void processEvent(SDL_Event& evt);
		void destroy();
		bool initialized();
	private:
		bool _initialized = false;
		Renderer* _renderer = nullptr;
		Window* _window = nullptr;
	};
}