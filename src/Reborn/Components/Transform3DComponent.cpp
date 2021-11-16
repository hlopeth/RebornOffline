#include "Core.h"
#include "Transform3DComponent.h"
#include <Math/MathUtils.h>
#include <Core/Application.h>
#include <cassert>

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
	return transform.getModelMatrix();
}

const Reborn::Transform& Reborn::Transform3DComponent::getTransform() const
{
	return transform;
}

void Reborn::Transform3DComponent::setTransform(const Transform& tr)
{
	transform = tr;
}

Reborn::Entity Reborn::Transform3DComponent::getParent() const
{
	return parent;
}

bool Reborn::Transform3DComponent::setParent(Entity newParent)
{
	if (newParent == this->parent) {
		return true;
	}
	if (newParent == NoEntity) {
		deatachParent();
		return true;
	}
	
	if (!hasTransform3d(newParent)) {
		return false;
	}
	if (this->parent != NoEntity) {
		deatachParent();
	}
	this->parent = newParent;
	Entity owner = Application::get()->entityManager().getOwner<Reborn::Transform3DComponent>(*this);
	Application::get()->entityManager().getComponent<Reborn::Transform3DComponent>(newParent).addChild(owner);
	return true;
}

const std::vector<Reborn::Entity>& Reborn::Transform3DComponent::getChilds() const
{
	return childs;
}

void Reborn::Transform3DComponent::deatachChild(Entity child)
{
	auto it = std::find(childs.begin(), childs.end(), child);
	if (it != childs.end()) {
		childs.erase(it);
	}
}

void Reborn::Transform3DComponent::addChild(Entity newChild)
{
	auto it = std::find(childs.begin(), childs.end(), newChild);
	if (it == childs.end()) {
		childs.push_back(newChild);
	}
}

bool Reborn::Transform3DComponent::hasTransform3d(Entity entity)
{
	return Application::get()->entityManager().hasComponent<Reborn::Transform3DComponent>(entity);
}

void Reborn::Transform3DComponent::deatachParent()
{
	if (this->parent == NoEntity) {
		return;
	}
	Entity owner = Application::get()->entityManager().getOwner<Reborn::Transform3DComponent>(*this);
	Application::get()->entityManager().getComponent<Reborn::Transform3DComponent>(parent).deatachChild(owner);
	parent = NoEntity;
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
