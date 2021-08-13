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
	class MouseMotionEvent : public IEvent
	{
	public:
		MouseMotionEvent(int32_t _x, int32_t _y, int32_t _xRel, int32_t _yRel) :
			x(_x),
			y(_y),
			xRel(_xRel),
			yRel(_yRel)
		{}
		const EventType GetType() const override {
			return TYPE();
		};
		const char* GetName() const override {
			return "MouseMotionEvent";
		};
		static EventType TYPE() {
			return 0x5a642c83;
		};

		int32_t x;
		int32_t y;
		int32_t xRel;
		int32_t yRel;
	};
}
