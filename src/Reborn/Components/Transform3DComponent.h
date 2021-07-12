#pragma once
#include "ComponentTypes.h"
#include <ECS/Component.h>
#include "Math/Vector.h"

namespace Reborn {
	class Transform3DComponent : public Component<Transform3DComponent, ComponentTypes::Transform3D>
	{
	public:
		Transform3DComponent() : position(0.f), scale(1.f), rotation(0.f) {}
		Transform3DComponent(
			const Vector3& _position,
			const Vector3& _scale,
			const Vector3& _rotation
		): position(_position), scale(_scale), rotation(_rotation) {}
		Vector3 position;
		Vector3 scale;
		Vector3 rotation;
	};
}