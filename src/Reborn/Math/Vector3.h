#pragma once
#include "Vector2.h"

namespace Reborn {
	struct Vector3
	{
		Vector3() {
			x = 0.f;
			y = 0.f;
			z = 0.f;
		};
		Vector3(float t) {
			x = t;
			y = t;
			z = t;
		};
		Vector3(float _x, float _y, float _z) {
			x = _x;
			y = _y;
			z = _z;
		};
		Vector3(const Vector2& v, float _z) {
			x = v.x;
			y = v.y;
			z = _z;
		}
		Vector3(const Vector3& v) {
			xyz = v.xyz;
		};
		void operator=(const Vector3& t) {
			x = float(t.x);
			y = float(t.y);
			z = float(t.z);
		}
		Vector3 operator+(const Vector3& t) const {
			return Vector3(x + t.x, y + t.y, z + t.z);
		}
		void operator+=(const Vector3& t) {
			x += t.x;
			y += t.y;
			z += t.z;
		}
		Vector3 operator+(float t) const {
			return Vector3(x + t, y + t, z + t);
		}
		void operator+=(float t) {
			x += t;
			y += t;
			z += t;
		}
		Vector3 operator-() const {
			return Vector3(- x, -y, -z);
		}
		Vector3 operator-(const Vector3& t) const {
			return Vector3(x - t.x, y - t.y, z - t.z);
		}
		void operator-=(const Vector3& t) {
			x -= t.x;
			y -= t.y;
			z -= t.z;
		}
		Vector3 operator-(float t) const {
			return Vector3(x - t, y - t, z - t);
		}
		void operator-=(float t) {
			x -= t;
			y -= t;
			z -= t;
		}
		Vector3 operator*(const Vector3& t) const {
			return Vector3(x * t.x, y * t.y, z * t.z);
		}
		Vector3 operator*(float t) const {
			return Vector3(x * t, y * t, z * t);
		}
		void operator*=(const Vector3& t) {
			x *= t.x;
			y *= t.y;
			z *= t.z;
		}
		void operator*=(float t) {
			x *= t;
			y *= t;
			z *= t;
		}
		Vector3 operator/(const Vector3& t) const {
			return Vector3(x / t.x, y / t.y, z / t.z);
		}
		Vector3 operator/(float t) const {
			return Vector3(x / t, y / t, z / t);
		}
		void operator/=(const Vector3& t) {
			x /= t.x;
			y /= t.y;
			z /= t.z;
		}
		void operator/=(float t) {
			x /= t;
			y /= t;
			z /= t;
		}
		float length() const {
			return sqrt(x * x + y * y + z * z);
		}
		Vector3& normalize() {
			(*this) /= length();
			return *this;
		}

		std::string toString() const {
			std::stringstream str;
			str << "Vector3( " << x << "; " << y << "; " << z << ")";
			return str.str();
		}

		union {
			float d[3];
			scalarSwizzle<0> x, r;
			scalarSwizzle<1> y, g;
			scalarSwizzle<2> z, b;

			REBORN_SWIZZLE3_2_MEMBERS(x, y, z)
			REBORN_SWIZZLE3_2_MEMBERS(r, g, b)
			REBORN_SWIZZLE3_3_MEMBERS(x, y, z)
			REBORN_SWIZZLE3_3_MEMBERS(r, g, b)
		};
	};

	inline std::ostream& operator<<(std::ostream& os, const Vector3& vec)
	{
		os << vec.toString();
		return os;
	}

	inline Vector3 operator+(const float t, const Vector3& v)
	{
		return v + t;
	}
	inline Vector3 operator*(const float t, const Vector3& v)
	{
		return v * t;
	}

	inline Vector3 normalize(const Vector3& v) {
		return v / v.length();
	}

	inline float dot(const Vector3& a, const Vector3& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	inline Vector3 cross(const Vector3& a, const Vector3& b) {
		return Vector3(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);
	}
}