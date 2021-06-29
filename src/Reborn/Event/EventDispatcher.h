#pragma once
#include "IEvent.h"

namespace Reborn {
	typedef std::function<void(const IEvent&)> t_EventHandler;

	class EventDispatcher {
	public:
		EventDispatcher();

		void subscribe(EventType eventType, t_EventHandler* handler);
		void unsubscribe(EventType eventType, t_EventHandler* handler);
		void triggerEvent(IEvent& evt);

	private:
		void invokeEvent(IEvent& evt);

		typedef std::vector<t_EventHandler*> EventHandlersVect;
		std::unordered_map<EventType, EventHandlersVect> eventHandlers;
	};
}