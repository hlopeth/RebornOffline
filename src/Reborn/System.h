#pragma once
#include <memory>
#include "Event/EventDispatcher.h"

#define SET_MEMBER_EVENT_HANDLER(ClassType, EventType, Callback) System::get().eventDispatcher().setEventHandler<ClassType, EventType>(EventType::TYPE(), this, &ClassType::Callback)
#define SET_EVENT_HANDLER(EventType, Callback) System::get().eventDispatcher().setEventHandler<EventType>(EventType::TYPE(), Callback)

namespace Reborn {
	class System {
	public:
		static System& get();
		int Init();
		void Shutdown();
		EventDispatcher& eventDispatcher();
	private:
		System();
		static System* systemInstance;

		EventDispatcher _eventDispatcher;
	};
}