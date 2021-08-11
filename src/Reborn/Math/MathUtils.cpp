#include <Core.h>
#include "MathUtils.h"

namespace Reborn {
	degree toDegrees(radian r) {
		return r * 180 / PI;
	}

	radian toRadians(degree d) {
		return d * PI / 180;
	}

	Matrix4 perspectiveMatrix(float n, float f, float r, float l, float t, float b) {
		return Matrix4(
			2 * n / (r - l), 0, (r + l) / (r - l), 0,
			0, 2 * n / (t - b), (t + b) / (t - b), 0,
			0, 0, -(f + n) / (f - n), -1,
			0, 0, -2 * n * f / (f - n), 0
		);
	}

	Matrix4 perspectiveFOVMatrix(float fovy, float aspect, float n, float f) {
		float tanHalfFov = tan(fovy / 2.0);
		return Matrix4(
			1.0 / (aspect * tanHalfFov), 0, 0, 0,
			0, 1.0 / tanHalfFov, 0, 0,
			0, 0, -(f + n) / (f - n), -1,
			0, 0, -2 * f * n / (f - n), 0
		);
	}

	Matrix4 perspectiveInfiniteDepthMatrix(float n, float f, float r, float l, float t, float b) {
		return Matrix4(
			2 * n / (r - l), 0, 0, 0,
			0, 2 * n / (t - b), (t + b) / (t - b), 0,
			(r + l) / (r - l), 0, -1, -2 * n,
			0, 0, -1, 0
		);
	}

	Matrix4 orthoMatrix(float n, float f, float r, float l, float t, float b) {
		return Matrix4(
			2 / (r - l), 0, 0, 0,
			0, 2 / (t - b), 0, 0,
			0, 0, -2 / (f - n), 0,
			-(r + l) / (r - l), -(t + b) / (t - b), -(f + n) / (f - n), 1
		);
	}

	Matrix4 rotation(const Vector3& angles) {
		Matrix4 m_x = Matrix4::one();
		m_x(1, 1) = cos(angles.x);
		m_x(1, 2) = -sin(angles.x);
		m_x(2, 1) = sin(angles.x);
		m_x(2, 2) = cos(angles.x);

		Matrix4 m_y = Matrix4::one();
		m_y(0, 0) = cos(angles.y);
		m_y(0, 2) = sin(angles.y);
		m_y(2, 0) = -sin(angles.y);
		m_y(2, 2) = cos(angles.y);

		Matrix4 m_z = Matrix4::one();
		m_z(0, 0) = cos(angles.z);
		m_z(0, 1) = -sin(angles.z);
		m_z(1, 0) = sin(angles.z);
		m_z(1, 1) = cos(angles.z);
		return m_x * m_y * m_z;
	}


	Matrix4 transfromMatrix(const Vector3& position, const Vector3& scale, const Vector3& rot) {
		Matrix4 t = Matrix4::one();
		t(0, 3) = position.x;
		t(1, 3) = position.y;
		t(2, 3) = position.z;

		Matrix4 s = Matrix4::one();
		s(0, 0) = scale.x;
		s(1, 1) = scale.y;
		s(2, 2) = scale.z;

		Matrix4 r = rotation(rot);
		return t * r * s;
	}
	Matrix4 lookAt(const Vector3& eye, const Vector3& cursor, const Vector3& up)
	{
		Vector3 b = normalize(eye - cursor);
		Vector3 r = cross(up, b).normalize();
		Vector3 u = cross(r, b);
		return Matrix4(
			r.x, r.y, r.z, 0,
			u.x, u.y, u.z, 0,
			b.x, b.y, b.z, 0,
			0, 0, 0, 1
		);
	}
}