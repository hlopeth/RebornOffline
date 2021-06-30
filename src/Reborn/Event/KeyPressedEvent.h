#pragma once
#include "IEvent.h"
#include "KeyCodes.h"

namespace Reborn {
	class KeyPressedEvent: public IEvent
	{
	public:
		KeyPressedEvent(KeyCode _key):
			key(_key)
		{}
		const EventType GetType() const override {
			return TYPE();
		};
		const char* GetName() const override {
			return "KeyPressedEvent";
		};
		static EventType TYPE() {
			return 0xb1856b95;
		};

		KeyCode key;
	};
}