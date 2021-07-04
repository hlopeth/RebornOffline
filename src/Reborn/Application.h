#pragma once
#include "Window.h"
#include "Renderer.h"
#include "System.h"

namespace Reborn {
	class Application
	{
	public:
		Application(WindowConfiguration windowConfig);
		void Run();
		void Close();
		virtual ~Application();
		void onApplicationClose(const IEvent& evt);

	protected:
		std::unique_ptr<Window> window;
		std::unique_ptr<Renderer> renderer;
	private: 
		void PoolEvents();
		bool shouldClose = false; 
		t_EventHandler closeHandler;
	};
}