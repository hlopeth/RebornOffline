#pragma once
#include "ComponentTypes.h"
#include <ECS/Component.h>
#include <Graphics/Transform.h>

namespace Reborn {
	class Transform3DComponent : public Component<Transform3DComponent, ComponentTypes::Transform3D>
	{
	public:
		Transform3DComponent() {};
		Transform3DComponent(
			const Vector3& position,
			const Vector3& scale,
			const Vector3& rotation
		) : transform(position, scale, rotation) {};

		const Vector3& getPosition() const;
		const Vector3& getScale() const;
		const Vector3& getRotation() const;
		void setPosition(Vector3 newPosition);
		void setScale(Vector3 newScale);
		void setRotation(Vector3 newRotation);
		const Matrix4& getModelMatrix() const;
		Transform3DComponent* parent = nullptr;
	private:
		Transform transform = Transform();
	};
}