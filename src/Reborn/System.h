#pragma once
#include <memory>
#include "Event/EventDispatcher.h"
#include "ECS/EntityManager.h"

namespace Reborn {
	class System {
	public:
		static System& get();
		int Init();
		void Shutdown();
		
		EventDispatcher& eventDispatcher();
		static const uint8_t maxEntitySystems = 10;
		static const uint16_t maxComponents = 100;
		EntityManager<maxComponents, maxEntitySystems>& entityManager();
	private:
		System();
		static System* systemInstance;

		EventDispatcher _eventDispatcher;
		EntityManager<maxComponents, maxEntitySystems> _entityManager;
	};
}