#include "EventDispatcher.h"
#include <algorithm>
#include "Log.h"

Reborn::EventDispatcher::EventDispatcher()
{
}

void Reborn::EventDispatcher::subscribe(EventType eventType, t_EventHandler* handler)
{
	auto& handlers = eventHandlers[eventType];
	auto it = std::find(handlers.begin(), handlers.end(), handler);
	if (it != handlers.end()) {
		LOG_WARN << "EventDispatcher.subscribe. handler was already subscribed. EventType " << eventType;
		return;
	}

	eventHandlers[eventType].push_back(handler);
}

void Reborn::EventDispatcher::unsubscribe(EventType eventType, t_EventHandler* handler)
{
	auto& handlers = eventHandlers[eventType];
	auto it = std::find(handlers.begin(), handlers.end(), handler);
	if (it == handlers.end()) {
		LOG_WARN << "EventDispatcher.unsubscribe. handler wasn't subscribed. EventType " << eventType;
		return;
	}

	handlers.erase(it);
}

void Reborn::EventDispatcher::triggerEvent(IEvent& evt)
{
	invokeEvent(evt);
}

void Reborn::EventDispatcher::invokeEvent(IEvent& evt)
{
	auto& handlers = eventHandlers[evt.GetType()];

	for (auto handler : handlers) {
		(*handler)(evt);
	}
}

