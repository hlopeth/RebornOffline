#pragma once
#include "ComponentTypes.h"
#include <ECS/Component.h>

namespace Reborn {
	class Transform3DComponent : public Component<Transform3DComponent, ComponentTypes::Transform3D>
	{
	public:
		Transform3DComponent() : x(0.f), y(0.f), z(0.f) {}
		Transform3DComponent(float _x, float _y, float _z): x(_x), y(_y), z(_z) {}
		float x;
		float y;
		float z;
	};
}