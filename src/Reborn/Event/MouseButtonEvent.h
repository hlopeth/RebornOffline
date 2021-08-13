#pragma once
#include "IEvent.h"
#include "KeyCodes.h"

namespace Reborn {
	class MouseButtonPressedEvent : public IEvent
	{
	public:
		MouseButtonPressedEvent(MouseButtonCode _button) :
			button(_button)
		{}
		const EventType GetType() const override {
			return TYPE();
		};
		const char* GetName() const override {
			return "MouseButtonPressedEvent";
		};
		static EventType TYPE() {
			return 0xf4f051bc;
		};

		MouseButtonCode button;
	};

	class MouseButtonReleasedEvent : public IEvent
	{
	public:
		MouseButtonReleasedEvent(MouseButtonCode _button) :
			button(_button)
		{}
		const EventType GetType() const override {
			return TYPE();
		};
		const char* GetName() const override {
			return "MouseButtonPressedEvent";
		};
		static EventType TYPE() {
			return 0x9806ebf0;
		};

		MouseButtonCode button;
	};
}
