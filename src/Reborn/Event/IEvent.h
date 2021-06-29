#pragma once

namespace Reborn {
	typedef unsigned long EventType;

	class IEvent
	{
	public:
		virtual const EventType GetType() const = 0;
		virtual const char* GetName() const = 0;
	};
}