#pragma once
#include "Window.h"
#include "Event/ApplicationCloseEvent.h"
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
		std::shared_ptr<Window> window;
	private: 
		void PoolEvents();
		bool shouldClose = false; 
		t_EventHandler closeHandler;
	};
}