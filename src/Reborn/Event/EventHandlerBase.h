#pragma once
#include "Event.h"

namespace Reborn {
	class EventHandlerBase
	{
	public:
		virtual ~EventHandlerBase();
		void invoke(const IEvent& event);
		void call(const IEvent& event);
	private:
		virtual void intCall(const IEvent& event) = 0;
	};
}
