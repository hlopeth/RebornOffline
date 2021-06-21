#pragma once
#include <memory>

namespace Reborn {
	class System {
	public:
		static System& get();
		int Init();
		void Shutdown();
	private:
		System();
		static System* systemInstance;
	};
}