#pragma once 
#include "ComponentTypes.h"
#include <ECS/Entity.h>
#include <ECS/Component.h>

namespace Reborn {
	class TickComponent;
	typedef std::function<void(Entity, TickComponent&, double, double)> t_tickHandler;

	class TickComponent : public Component<TickComponent, ComponentTypes::Tick>
	{
	public:
		//entity, this, time, delta
		TickComponent(t_tickHandler _onTick) :
			enable(true),
			onTick(_onTick)
		{}
		bool enable;

		t_tickHandler onTick;
	};
}