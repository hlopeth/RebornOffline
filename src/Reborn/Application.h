#pragma once
#include "Window.h"

namespace Reborn {
	class Application
	{
	public:
		Application(WindowConfiguration windowConfig);
		void Run();
		void Close();
		virtual ~Application();

	protected:
		std::shared_ptr<Window> window;
	private: 
		void PoolEvents();
		bool shouldClose = false;
	};
}