#include <Core.h>
#include "Camera.h"

#include <Math/MathUtils.h>

Reborn::Camera::Camera():
	fov(0),
	_near(0),
	_far(0),
	aspect(0),
	position(0,0,0)
{
	matricesDirty = true;
}

Reborn::Camera::Camera(radian in_fov, float in_near, float in_far, float in_aspect):
	fov(in_fov),
	_near(in_near),
	_far(in_far),
	aspect(in_aspect),
	position(0,0,0)
{
	rebuildMatrices();
	matricesDirty = false;
}

const Reborn::Matrix4& Reborn::Camera::getProjection() const
{
	if (matricesDirty) {
		Camera* camera = const_cast<Camera*>(this);
		camera->rebuildMatrices();
		camera->matricesDirty = false;
	}
	return proj;
}

const Reborn::Matrix4& Reborn::Camera::getViewProjection() const
{
	if (matricesDirty) {
		Camera* camera = const_cast<Camera*>(this);
		camera->rebuildMatrices();
		camera->matricesDirty = false;
	}
	return viewProj;
}

const Reborn::Matrix4& Reborn::Camera::getView() const
{
	if (matricesDirty) {
		Camera* camera = const_cast<Camera*>(this);
		camera->rebuildMatrices();
		camera->matricesDirty = false;
	}
	return view;
}

void Reborn::Camera::setAspect(float newAspect)
{
	aspect = newAspect;
	matricesDirty = true;
}

void Reborn::Camera::setNear(float newNear)
{
	_near = newNear;
	matricesDirty = true;
}

void Reborn::Camera::setFar(float newFar)
{
	_far = newFar;
	matricesDirty = true;
}

void Reborn::Camera::setFOV(radian newFOV)
{
	fov = newFOV;
}

float Reborn::Camera::getAspect() const
{
	return aspect;
}

float Reborn::Camera::getNear() const
{
	return _near;
}

float Reborn::Camera::getFar() const
{
	return _far;
}

Reborn::radian Reborn::Camera::getFOV() const
{
	return fov;
}

void Reborn::Camera::rebuildMatrices()
{
	proj = Reborn::perspectiveFOVMatrix(fov, aspect, _near, _far);
	view = Reborn::lookAt(position, cursor, Vector3(0, 1, 0)).translate(-position);
	viewProj = proj * view;
}

void Reborn::Camera::setPosition(const Vector3 newPosition)
{
	position = newPosition;
	matricesDirty = true;
}

Reborn::Vector3 Reborn::Camera::getPosition() const
{
	return position;
}

void Reborn::Camera::setCursor(const Vector3 newCursor)
{
	cursor = newCursor;
	matricesDirty = true;
}

Reborn::Vector3 Reborn::Camera::getCursor() const
{
	return cursor;
}