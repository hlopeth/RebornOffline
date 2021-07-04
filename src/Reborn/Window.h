#pragma once
#include "SDL_video.h"

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
		SDL_GLContext createGLContext();
		SDL_Window& getSDLWindow();
		const int width() const;
		const int height() const;
		void Update();
		~Window();
		static Window* CreateSDLWindow(WindowConfiguration configuration);
	private:
		SDL_Window* _sdlWindow = nullptr;
	};
}