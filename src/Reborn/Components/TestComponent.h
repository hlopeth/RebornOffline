#pragma once
#include "ComponentTypes.h"
#include "ECS/Component.h"

namespace Reborn
{
	class TestComponent : public Component<TestComponent, ComponentTypes::Test>
	{
		float x;
		float y;
	};
}