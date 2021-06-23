#pragma once
#include "Event/IEvent.h"

namespace Reborn {
	class IEventHandler {
		virtual void invoke(const IEvent& evt) = 0;
	};
}