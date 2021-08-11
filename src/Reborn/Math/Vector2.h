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
		Vector2 operator-() const {
			return Vector2(-x, -y);
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
			x *= t.x;
			y *= t.y;
		}
		void operator*=(float t) {
			x *= t;
			y *= t;
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
			REBORN_SWIZZLE2_2_MEMBERS(x, y)
			REBORN_SWIZZLE2_2_MEMBERS(r, g)
			//REBORN_SWIZZLE2_3_MEMBERS(x, y)
			//REBORN_SWIZZLE2_3_MEMBERS(r, g)
			//REBORN_SWIZZLE2_4_MEMBERS(x, y)
			//REBORN_SWIZZLE2_4_MEMBERS(r, g)
		};
	};


	inline std::ostream& operator<<(std::ostream& os, const Vector2& vec)
	{
		os << vec.toString();
		return os;
	}

	inline float dot(const Vector2& a, const Vector2& b) {
		return a.x * b.x + a.y * b.y;
	}
}