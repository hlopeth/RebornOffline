#pragma once
#include "SDL_video.h"
#include <memory>

namespace Reborn {
	struct WindowConfiguration {
		char title[64];
		int x;
		int y;
		int width;
		int height;
		bool fullscreen = false;
		bool resizable = false;
	};

	class Window {
	public:
		Window(SDL_Window* sdlWindow);
		void Update();
		~Window();
		static std::shared_ptr<Window> CreateSDLWindow(WindowConfiguration configuration);
	private:
		SDL_Window* _id = nullptr;
	};
}