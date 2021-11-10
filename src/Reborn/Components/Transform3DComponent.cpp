#include "Core.h"
#include "Transform3DComponent.h"
#include <Math/MathUtils.h>

using Reborn::Vector3;
using Reborn::Matrix4;

const Vector3& Reborn::Transform3DComponent::getPosition() const
{
	return transform.getPosition();
}

const Vector3& Reborn::Transform3DComponent::getScale() const
{
	return transform.getScale();
}

const Vector3& Reborn::Transform3DComponent::getRotation() const
{
	return transform.getRotation();
}

const Matrix4& Reborn::Transform3DComponent::getModelMatrix() const
{
	if (parent != nullptr) {
		return transform.getModelMatrix(parent->transform);
	}
	else {
		return transform.getModelMatrix();
	}
}

void Reborn::Transform3DComponent::setPosition(Vector3 newPosition)
{
	transform.setPosition(newPosition);
}

void Reborn::Transform3DComponent::setScale(Vector3 newScale)
{
	transform.setScale(newScale);
}

void Reborn::Transform3DComponent::setRotation(Vector3 newRotation)
{
	transform.setRotation(newRotation);
}
