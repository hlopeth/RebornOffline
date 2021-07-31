#pragma once
#include "Event/EventDispatcher.h"
#include "ECS/EntityManager.h"
#include "Resources/ResourceManager.h"

namespace Reborn {
	class System {
	public:
		static System& get();
		int Init();
		void Shutdown();
		
		EventDispatcher& eventDispatcher();
		ResourceManager& resourceManager();
		static const uint8_t maxEntitySystems = 10;
		static const uint16_t maxComponents = 100;
		EntityManager<maxComponents, maxEntitySystems>& entityManager();
	private:
		System();
		static System* systemInstance;

		EventDispatcher _eventDispatcher;
		ResourceManager _resourceManager;
		EntityManager<maxComponents, maxEntitySystems> _entityManager;
	};
}