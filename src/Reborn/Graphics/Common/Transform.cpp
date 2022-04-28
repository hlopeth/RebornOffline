#include "Core.h"
#include "Transform.h"
#include <Math/MathUtils.h>

using Reborn::Vector3;
using Reborn::Matrix4;

Reborn::Transform::Transform(
	const Vector3& _position,
	const Vector3& _scale,
	const Vector3& _rotation
) :
	position(_position),
	scale(_scale),
	rotation(_rotation)
{
}

const Vector3& Reborn::Transform::getPosition() const
{
	return position;
}

const Vector3& Reborn::Transform::getScale() const
{
	return scale;
}

const Vector3& Reborn::Transform::getRotation() const
{
	return rotation;
}

const Matrix4& Reborn::Transform::getModelMatrix() const
{
	if (modelMatrixIsDirty) {
		Reborn::Transform* transform = const_cast<Transform*>(this);
		transform->model = transfromMatrix(transform->position, transform->scale, transform->rotation);
		transform->modelMatrixIsDirty = false;
	}
	return model;
}

const Matrix4& Reborn::Transform::getModelMatrix(const Matrix4& parentModel) const
{
	Reborn::Transform* transform = const_cast<Transform*>(this);
	getModelMatrix();
	transform->model = parentModel * transform->model;
	transform->modelMatrixIsDirty = true;
	return model;
}

void Reborn::Transform::setPosition(Vector3 newPosition)
{
	position = newPosition;
	modelMatrixIsDirty = true;
}

void Reborn::Transform::setScale(Vector3 newScale)
{
	scale = newScale;
	modelMatrixIsDirty = true;
}

void Reborn::Transform::setRotation(Vector3 newRotation)
{
	rotation = newRotation;
	modelMatrixIsDirty = true;
}
