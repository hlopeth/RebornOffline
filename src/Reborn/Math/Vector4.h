#pragma once
#include "Vector3.h"

namespace Reborn {
	struct Vector4
	{
		Vector4() {
			x = 0.f;
			y = 0.f;
			z = 0.f;
			w = 0.f;
		};
		Vector4(float t) {
			x = t;
			y = t;
			z = t;
			w = t;
		};
		Vector4(float _x, float _y, float _z, float _w) {
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		};
		Vector4(const Vector2& v, float _z, float _w) {
			x = v.x;
			y = v.y;
			z = _z;
			w = _w;
		};
		Vector4(const Vector3& v, float _w) {
			x = v.x;
			y = v.y;
			z = v.z;
			w = _w;
		};
		Vector4(const Vector4& v) {
			xyzw = v.xyzw;
		};
		void operator=(const Vector4& t) {
			x = float(t.x);
			y = float(t.y);
			z = float(t.z);
			w = float(t.w);
		}
		Vector4 operator+(const Vector4& t) const {
			return Vector4(x + t.x, y + t.y, z + t.z, w + t.w);
		}
		void operator+=(const Vector4& t) {
			x += t.x;
			y += t.y;
			z += t.z;
			w += t.w;
		}
		Vector4 operator+(float t) const {
			return Vector4(x + t, y + t, z + t, w + t);
		}
		void operator+=(float t) {
			x += t;
			y += t;
			z += t;
			w += t;
		}
		Vector4 operator-(const Vector4& t) const {
			return Vector4(x - t.x, y - t.y, z - t.z, w - t.w);
		}
		void operator-=(const Vector4& t) {
			x -= t.x;
			y -= t.y;
			z -= t.z;
			w -= t.w;
		}
		Vector4 operator-() const {
			return Vector4(-x, -y, -z, -w);
		}
		Vector4 operator-(float t) const {
			return Vector4(x - t, y - t, z - t, w - t);
		}
		void operator-=(float t) {
			x -= t;
			y -= t;
			z -= t;
			w -= t;
		}
		Vector4 operator*(const Vector4& t) const {
			return Vector4(x * t.x, y * t.y, z * t.z, w * t.w);
		}
		Vector4 operator*(float t) const {
			return Vector4(x * t, y * t, z * t, w * t);
		}
		void operator*=(const Vector4& t) {
			x *= t.x;
			y *= t.y;
			z *= t.z;
			w *= t.w;
		}
		void operator*=(float t) {
			x *= t;
			y *= t;
			z *= t;
			w *= t;
		}

		std::string toString() const {
			std::stringstream str;
			str << "Vector4( " << x << "; " << y << "; " << z << "; " << w << ")";
			return str.str();
		}

		union {
			float d[4];
			scalarSwizzle<0> x, r;
			scalarSwizzle<1> y, g;
			scalarSwizzle<2> z, b;
			scalarSwizzle<3> w, a;
			REBORN_SWIZZLE4_2_MEMBERS(x,y,z,w)
			REBORN_SWIZZLE4_2_MEMBERS(r,g,b,a)
			REBORN_SWIZZLE4_3_MEMBERS(x,y,z,w)
			REBORN_SWIZZLE4_3_MEMBERS(r,g,b,a)
			REBORN_SWIZZLE4_4_MEMBERS(x,y,z,w)
			REBORN_SWIZZLE4_4_MEMBERS(r,g,b,a)
		};
	};

	inline std::ostream& operator<<(std::ostream& os, const Vector4& vec)
	{
		os << vec.toString();
		return os;
	}

	inline Vector4 operator+(const float t, const Vector4& v) 
	{
		return v + t;
	}
	inline Vector4 operator*(const float t, const Vector4& v) 
	{
		return v * t;
	}

	inline float dot(const Vector4& a, const Vector4& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}
}