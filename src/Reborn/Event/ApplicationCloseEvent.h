#pragma once
#include "IEvent.h"

namespace Reborn {
	class ApplicationCloseEvent : public IEvent
	{
	public:
		const EventType GetType() const override {
			return TYPE();
		};
		const char* GetName() const override {
			return "ApplicationCloseEvent";
		};
		static EventType TYPE() { 
			return 0x77cf338a;
		};
	};
}