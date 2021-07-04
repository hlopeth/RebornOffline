#pragma once
#include "ECS/Component.h"

namespace Reborn
{
	class TestComponent : public Component<TestComponent, 0>
	{
		float x;
		float y;
	};
}