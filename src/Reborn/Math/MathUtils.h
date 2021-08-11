#pragma once
#include "MathCore.h"
#include "Matrix.h"
#include "Vector.h"

namespace Reborn {
	degree toDegrees(radian r);
	radian toRadians(degree d);
	Matrix4 perspectiveMatrix(float n, float f, float r, float l, float t, float b);
	Matrix4 perspectiveFOVMatrix(float fovy, float aspect, float n, float f);
	Matrix4 perspectiveInfiniteDepthMatrix(float n, float f, float r, float l, float t, float b);
	Matrix4 orthoMatrix(float n, float f, float r, float l, float t, float b);
	Matrix4 rotation(const Vector3& angles);
	Matrix4 transfromMatrix(const Vector3& position, const Vector3& scale, const Vector3& rot);
	Matrix4 lookAt(const Vector3& eye, const Vector3& cursor, const Vector3& up);
}