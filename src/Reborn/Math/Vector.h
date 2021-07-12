#pragma once
#include "Swizzle.h"

namespace Reborn {
	struct Vector2
	{
		Vector2() {
			x = 0.f;
			y = 0.f;
		};
		Vector2(float t) {
			x = t;
			y = t;
		};
		Vector2(float _x, float _y) {
			x = _x;
			y = _y;
		};
		void operator=(const Vector2& t) { 
			xy = t.xy;
		}
		Vector2 operator+(const Vector2& t) const { 
			return Vector2(x + t.x, y + t.y); 
		}
		void operator+=(const Vector2& t) {
			x += t.x;
			y += t.y; 
		}
		Vector2 operator+(float t) const {
			return Vector2(x + t, y + t); 
		}
		void operator+=(float t) { 
			x += t;
			y += t; 
		}
		Vector2 operator-(const Vector2& t) const {
			return Vector2(x - t.x, y - t.y);
		}
		void operator-=(const Vector2& t) {
			x -= t.x;
			y -= t.y; 
		}
		Vector2 operator-(float t) const {
			return Vector2(x - t, y - t);
		}
		void operator-=(float t) { 
			x -= t; 
			y -= t;
		}
		Vector2 operator*(const Vector2& t) const {
			return Vector2(x * t.x, y * t.y); 
		}
		Vector2 operator*(float t) const {
			return Vector2(x * t, y * t);
		}
		void operator*=(const Vector2& t) {
			x*= t.x;
			y*= t.y; 
		}
		void operator*=(float t) { 
			x*= t; 
			y*= t; 
		}

		std::string toString() const {
			std::stringstream str;
			str << "Vector2( " << x << "; " << y << ")";
			return str.str();
		}

		union {
			float d[2];
			scalarSwizzle<0> x, r;
			scalarSwizzle<1> y, g;
			vec2Swizzle<Vector2, 0, 0> xx, rr;
			vec2Swizzle<Vector2, 0, 1> xy, rg;
			vec2Swizzle<Vector2, 1, 0> yx, gr;
			vec2Swizzle<Vector2, 1, 1> yy, gg;
		};
	};


	union MyUnion
	{
		int i;
		float f;
		double d;
	};

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

			vec2Swizzle<Vector2, 0, 0> xx, rr;
			vec2Swizzle<Vector2, 0, 1> xy, rg;
			vec2Swizzle<Vector2, 0, 2> xz, rb;
			vec2Swizzle<Vector2, 1, 0> yx, gr;
			vec2Swizzle<Vector2, 1, 1> yy, gg;
			vec2Swizzle<Vector2, 1, 2> yz, gb;
			vec2Swizzle<Vector2, 2, 0> zx, br;
			vec2Swizzle<Vector2, 2, 1> zy, bg;
			vec2Swizzle<Vector2, 2, 2> zz, bb;

			vec3Swizzle<Vector3, 0, 0, 0> xxx, rrr;
			vec3Swizzle<Vector3, 0, 0, 1> xxy, rrg;
			vec3Swizzle<Vector3, 0, 0, 2> xxz, rrb;
			vec3Swizzle<Vector3, 0, 1, 0> xyx, rgr;
			vec3Swizzle<Vector3, 0, 1, 1> xyy, rgg;
			vec3Swizzle<Vector3, 0, 1, 2> xyz, rgb;
			vec3Swizzle<Vector3, 0, 2, 0> xzx, rbr;
			vec3Swizzle<Vector3, 0, 2, 1> xzy, rbg;
			vec3Swizzle<Vector3, 0, 2, 2> xzz, rbb;

			vec3Swizzle<Vector3, 1, 0, 0> yxx, grr;
			vec3Swizzle<Vector3, 1, 0, 1> yxy, grg;
			vec3Swizzle<Vector3, 1, 0, 2> yxz, grb;
			vec3Swizzle<Vector3, 1, 1, 0> yyx, ggr;
			vec3Swizzle<Vector3, 1, 1, 1> yyy, ggg;
			vec3Swizzle<Vector3, 1, 1, 2> yyz, ggb;
			vec3Swizzle<Vector3, 1, 2, 0> yzx, gbr;
			vec3Swizzle<Vector3, 1, 2, 1> yzy, gbg;
			vec3Swizzle<Vector3, 1, 2, 2> yzz, gbb;

			vec3Swizzle<Vector3, 2, 0, 0> zxx, brr;
			vec3Swizzle<Vector3, 2, 0, 1> zxy, brg;
			vec3Swizzle<Vector3, 2, 0, 2> zxz, brb;
			vec3Swizzle<Vector3, 2, 1, 0> zyx, bgr;
			vec3Swizzle<Vector3, 2, 1, 1> zyy, bgg;
			vec3Swizzle<Vector3, 2, 1, 2> zyz, bgb;
			vec3Swizzle<Vector3, 2, 2, 0> zzx, bbr;
			vec3Swizzle<Vector3, 2, 2, 1> zzy, bbg;
			vec3Swizzle<Vector3, 2, 2, 2> zzz, bbb;
		};
	};


	inline std::ostream& operator<<(std::ostream& os, const Vector2& vec)
	{
		os << vec.toString();
		return os;
	}

	inline std::ostream& operator<<(std::ostream& os, const Vector3& vec)
	{
		os << vec.toString();
		return os;
	}
}