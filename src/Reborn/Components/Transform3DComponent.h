#pragma once
#include "ComponentTypes.h"
#include <ECS/Component.h>
#include <ECS/Entity.h>
#include <Graphics/Transform.h>

namespace Reborn {
	class Transform3DComponent : public Component<Transform3DComponent, ComponentTypes::Transform3D>
	{
	public:
		Transform3DComponent() {};
		Transform3DComponent(
			const Transform& _transform
		) : transform(_transform) {};
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
		const Transform& getTransform() const;
		void setTransform(const Transform& tr);
		Entity getParent() const;
		bool setParent(Entity parent);
		const std::vector<Entity>& getChilds() const;
		Matrix4 world;
	private:
		void addChild(Entity child);
		void deatachChild(Entity child);
		void deatachParent();
		bool hasTransform3d(Entity entity);
		Entity parent = NoEntity;
		std::vector<Entity> childs;
		Transform transform = Transform();
	};
}