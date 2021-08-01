#pragma once

namespace Reborn {
	template<unsigned int I>
	struct scalarSwizzle
	{
		float v[1];
		float& operator=(const float x)
		{
			elem() = x;
			return elem();
		}
		float& operator=(const scalarSwizzle& sw)
		{
			elem() = sw.elem();
			return elem();
		}
		operator float() const
		{
			return elem();
		}
		float operator++(int)
		{
			return elem()++;
		}
		float operator++()
		{
			return ++elem();
		}
		float operator--(int)
		{
			return elem()--;
		}
		float operator--()
		{
			return --elem();
		}
		void operator+=(float a)
		{
			elem() += a;
		}
		void operator+=(const scalarSwizzle& sw)
		{
			elem() += sw.elem();
		}
		void operator-=(float a)
		{
			elem() -= a;
		}
		void operator-=(const scalarSwizzle& sw)
		{
			elem() -= sw.elem();
		}
		void operator*=(float a)
		{
			elem() *= a;
		}
		void operator*=(const scalarSwizzle& sw)
		{
			elem() *= sw.elem();
		}
	private:
		float& elem() {
			return (reinterpret_cast<float*>(v))[I];
		}
		float const& elem() const {
			return (reinterpret_cast<const float*>(v))[I];
		}
	};

	template<unsigned int I>
	inline std::ostream& operator<<(std::ostream& os, const scalarSwizzle<I>& sw)
	{
		os << float(sw);
		return os;
	}

	template<typename vec_type, unsigned int A, unsigned int B>
	struct vec2Swizzle
	{
		float d[1];
		vec_type operator=(const vec_type& vec)
		{
			return vec_type(d[A] = vec.x, d[B] = vec.y);
		}
		vec_type& operator=(const vec2Swizzle& sw)
		{
			(*this) = vec_type(sw);
			return vec_type(*this);
		}
		operator vec_type() const
		{
			return vec_type(d[A], d[B]);
		}
		vec_type operator+(const vec2Swizzle& sw)
		{
			return vec_type(*this) + vec_type(sw);
		}
		vec_type operator-(const vec2Swizzle& sw)
		{
			return vec_type(*this) - vec_type(sw);
		}
		vec_type operator*(const vec2Swizzle& sw)
		{
			return vec_type(*this) * vec_type(sw);
		}
	};

	template<typename vec_type, unsigned int A, unsigned int B>
	vec_type operator+(const vec_type& vec, const vec2Swizzle<vec_type, A, B>& sw)
	{
		return vec + vec_type(sw);
	}

	template<typename vec_type, unsigned int A, unsigned int B>
	vec_type operator+(const vec2Swizzle<vec_type, A, B>& sw, const vec_type& vec)
	{
		return vec_type(sw) + vec;
	}

	template<typename vec_type, unsigned int A, unsigned int B>
	vec_type operator-(const vec_type& vec, const vec2Swizzle<vec_type, A, B>& sw)
	{
		return vec - vec_type(sw);
	}
	
	template<typename vec_type, unsigned int A, unsigned int B>
	vec_type operator-(const vec2Swizzle<vec_type, A, B>& sw, const vec_type& vec)
	{
		return vec_type(sw) - vec;
	}

	template<typename vec_type, unsigned int A, unsigned int B>
	vec_type operator*(const vec_type& vec, const vec2Swizzle<vec_type, A, B>& sw)
	{
		return vec * vec_type(sw);
	}

	template<typename vec_type, unsigned int A, unsigned int B>
	vec_type operator*(const vec2Swizzle<vec_type, A, B>& sw, const vec_type& vec)
	{
		return vec_type(sw) * vec;
	}

	template<typename vec_type, unsigned int A, unsigned int B>
	inline std::ostream& operator<<(std::ostream& os, const vec2Swizzle<vec_type, A, B>& sw)
	{
		os << vec_type(sw);
		return os;
	}

	template<typename vec_type, unsigned int A, unsigned int B, unsigned int C>
	struct vec3Swizzle
	{
		float d[1];
		vec_type operator=(const vec_type& vec)
		{
			return vec_type(d[A] = vec.x, d[B] = vec.y, d[C] = vec.z);
		}
		vec_type& operator=(const vec3Swizzle& sw)
		{
			(*this) = vec_type(sw);
			return vec_type(*this);
		}
		operator vec_type() const
		{
			return vec_type(d[A], d[B], d[C]);
		}
		vec_type operator+(const vec3Swizzle& sw)
		{
			return vec_type(*this) + vec_type(sw);
		}
		vec_type operator-(const vec3Swizzle& sw)
		{
			return vec_type(*this) - vec_type(sw);
		}
		vec_type operator*(const vec3Swizzle& sw)
		{
			return vec_type(*this) * vec_type(sw);
		}
	};

	template<typename vec_type, unsigned int A, unsigned int B, unsigned int C>
	vec_type operator+(const vec_type& vec, const vec3Swizzle<vec_type, A, B, C>& sw)
	{
		return vec + vec_type(sw);
	}

	template<typename vec_type, unsigned int A, unsigned int B, unsigned int C>
	vec_type operator+(const vec3Swizzle<vec_type, A, B, C>& sw, const vec_type& vec)
	{
		return vec_type(sw) + vec;
	}

	template<typename vec_type, unsigned int A, unsigned int B, unsigned int C>
	vec_type operator-(const vec_type& vec, const vec3Swizzle<vec_type, A, B, C>& sw)
	{
		return vec - vec_type(sw);
	}

	template<typename vec_type, unsigned int A, unsigned int B, unsigned int C>
	vec_type operator-(const vec3Swizzle<vec_type, A, B, C>& sw, const vec_type& vec)
	{
		return vec_type(sw) - vec;
	}

	template<typename vec_type, unsigned int A, unsigned int B, unsigned int C>
	vec_type operator*(const vec_type& vec, const vec3Swizzle<vec_type, A, B, C>& sw)
	{
		return vec * vec_type(sw);
	}

	template<typename vec_type, unsigned int A, unsigned int B, unsigned int C>
	vec_type operator*(const vec3Swizzle<vec_type, A, B, C>& sw, const vec_type& vec)
	{
		return vec_type(sw) * vec;
	}

	template<typename vec_type, unsigned int A, unsigned int B, unsigned int C>
	inline std::ostream& operator<<(std::ostream& os, const vec3Swizzle<vec_type, A, B, C>& sw)
	{
		os << vec_type(sw);
		return os;
	}

	template<typename vec_type, unsigned int A, unsigned int B, unsigned int C, unsigned int D>
	struct vec4Swizzle
	{
		float d[1];
		vec_type operator=(const vec_type& vec)
		{
			return vec_type(d[A] = vec.x, d[B] = vec.y, d[C] = vec.z, d[D] = vec.w);
		}
		vec_type& operator=(const vec4Swizzle& sw)
		{
			(*this) = vec_type(sw);
			return vec_type(*this);
		}
		operator vec_type() const
		{
			return vec_type(d[A], d[B], d[C], d[D]);
		}
		vec_type operator+(const vec4Swizzle& sw)
		{
			return vec_type(*this) + vec_type(sw);
		}
		vec_type operator-(const vec4Swizzle& sw)
		{
			return vec_type(*this) - vec_type(sw);
		}
		vec_type operator*(const vec4Swizzle& sw)
		{
			return vec_type(*this) * vec_type(sw);
		}
	};

	template<typename vec_type, unsigned int A, unsigned int B, unsigned int C, unsigned int D>
	vec_type operator+(const vec_type& vec, const vec4Swizzle<vec_type, A, B, C, D>& sw)
	{
		return vec + vec_type(sw);
	}

	template<typename vec_type, unsigned int A, unsigned int B, unsigned int C, unsigned int D>
	vec_type operator+(const vec4Swizzle<vec_type, A, B, C, D>& sw, const vec_type& vec)
	{
		return vec_type(sw) + vec;
	}

	template<typename vec_type, unsigned int A, unsigned int B, unsigned int C, unsigned int D>
	vec_type operator-(const vec_type& vec, const vec4Swizzle<vec_type, A, B, C, D>& sw)
	{
		return vec - vec_type(sw);
	}

	template<typename vec_type, unsigned int A, unsigned int B, unsigned int C, unsigned int D>
	vec_type operator-(const vec4Swizzle<vec_type, A, B, C, D>& sw, const vec_type& vec)
	{
		return vec_type(sw) - vec;
	}

	template<typename vec_type, unsigned int A, unsigned int B, unsigned int C, unsigned int D>
	vec_type operator*(const vec_type& vec, const vec4Swizzle<vec_type, A, B, C, D>& sw)
	{
		return vec * vec_type(sw);
	}

	template<typename vec_type, unsigned int A, unsigned int B, unsigned int C, unsigned int D>
	vec_type operator*(const vec4Swizzle<vec_type, A, B, C, D>& sw, const vec_type& vec)
	{
		return vec_type(sw) * vec;
	}

	template<typename vec_type, unsigned int A, unsigned int B, unsigned int C, unsigned int D>
	inline std::ostream& operator<<(std::ostream& os, const vec4Swizzle<vec_type, A, B, C, D>& sw)
	{
		os << vec_type(sw);
		return os;
	}
}

#define REBORN_SWIZZLE2_2_MEMBERS(E0,E1) \
	vec2Swizzle<Vector2, 0,0> E0 ## E0; \
	vec2Swizzle<Vector2, 0,1> E0 ## E1; \
	vec2Swizzle<Vector2, 1,0> E1 ## E0; \
	vec2Swizzle<Vector2, 1,1> E1 ## E1; 

#define REBORN_SWIZZLE3_2_MEMBERS(E0,E1,E2) \
	vec2Swizzle<Vector2, 0,0> E0 ## E0; \
	vec2Swizzle<Vector2, 0,1> E0 ## E1; \
	vec2Swizzle<Vector2, 0,2> E0 ## E2; \
	vec2Swizzle<Vector2, 1,0> E1 ## E0; \
	vec2Swizzle<Vector2, 1,1> E1 ## E1; \
	vec2Swizzle<Vector2, 1,2> E1 ## E2; \
	vec2Swizzle<Vector2, 2,0> E2 ## E0; \
	vec2Swizzle<Vector2, 2,1> E2 ## E1; \
	vec2Swizzle<Vector2, 2,2> E2 ## E2; 

#define REBORN_SWIZZLE3_3_MEMBERS(E0,E1,E2) \
	vec3Swizzle<Vector3, 0,0,0> E0 ## E0 ## E0; \
	vec3Swizzle<Vector3, 0,0,1> E0 ## E0 ## E1; \
	vec3Swizzle<Vector3, 0,0,2> E0 ## E0 ## E2; \
	vec3Swizzle<Vector3, 0,1,0> E0 ## E1 ## E0; \
	vec3Swizzle<Vector3, 0,1,1> E0 ## E1 ## E1; \
	vec3Swizzle<Vector3, 0,1,2> E0 ## E1 ## E2; \
	vec3Swizzle<Vector3, 0,2,0> E0 ## E2 ## E0; \
	vec3Swizzle<Vector3, 0,2,1> E0 ## E2 ## E1; \
	vec3Swizzle<Vector3, 0,2,2> E0 ## E2 ## E2; \
	vec3Swizzle<Vector3, 1,0,0> E1 ## E0 ## E0; \
	vec3Swizzle<Vector3, 1,0,1> E1 ## E0 ## E1; \
	vec3Swizzle<Vector3, 1,0,2> E1 ## E0 ## E2; \
	vec3Swizzle<Vector3, 1,1,0> E1 ## E1 ## E0; \
	vec3Swizzle<Vector3, 1,1,1> E1 ## E1 ## E1; \
	vec3Swizzle<Vector3, 1,1,2> E1 ## E1 ## E2; \
	vec3Swizzle<Vector3, 1,2,0> E1 ## E2 ## E0; \
	vec3Swizzle<Vector3, 1,2,1> E1 ## E2 ## E1; \
	vec3Swizzle<Vector3, 1,2,2> E1 ## E2 ## E2; \
	vec3Swizzle<Vector3, 2,0,0> E2 ## E0 ## E0; \
	vec3Swizzle<Vector3, 2,0,1> E2 ## E0 ## E1; \
	vec3Swizzle<Vector3, 2,0,2> E2 ## E0 ## E2; \
	vec3Swizzle<Vector3, 2,1,0> E2 ## E1 ## E0; \
	vec3Swizzle<Vector3, 2,1,1> E2 ## E1 ## E1; \
	vec3Swizzle<Vector3, 2,1,2> E2 ## E1 ## E2; \
	vec3Swizzle<Vector3, 2,2,0> E2 ## E2 ## E0; \
	vec3Swizzle<Vector3, 2,2,1> E2 ## E2 ## E1; \
	vec3Swizzle<Vector3, 2,2,2> E2 ## E2 ## E2;

#define REBORN_SWIZZLE4_2_MEMBERS(E0,E1,E2,E3) \
	vec2Swizzle<Vector2, 0,0> E0 ## E0; \
	vec2Swizzle<Vector2, 0,1> E0 ## E1; \
	vec2Swizzle<Vector2, 0,2> E0 ## E2; \
	vec2Swizzle<Vector2, 0,3> E0 ## E3; \
	vec2Swizzle<Vector2, 1,0> E1 ## E0; \
	vec2Swizzle<Vector2, 1,1> E1 ## E1; \
	vec2Swizzle<Vector2, 1,2> E1 ## E2; \
	vec2Swizzle<Vector2, 1,3> E1 ## E3; \
	vec2Swizzle<Vector2, 2,0> E2 ## E0; \
	vec2Swizzle<Vector2, 2,1> E2 ## E1; \
	vec2Swizzle<Vector2, 2,2> E2 ## E2; \
	vec2Swizzle<Vector2, 2,3> E2 ## E3; \
	vec2Swizzle<Vector2, 3,0> E3 ## E0; \
	vec2Swizzle<Vector2, 3,1> E3 ## E1; \
	vec2Swizzle<Vector2, 3,2> E3 ## E2; \
	vec2Swizzle<Vector2, 3,3> E3 ## E3; 

#define REBORN_SWIZZLE4_3_MEMBERS(E0,E1,E2,E3) \
	vec3Swizzle<Vector3, 0,0,0> E0 ## E0 ## E0; \
	vec3Swizzle<Vector3, 0,0,1> E0 ## E0 ## E1; \
	vec3Swizzle<Vector3, 0,0,2> E0 ## E0 ## E2; \
	vec3Swizzle<Vector3, 0,0,3> E0 ## E0 ## E3; \
	vec3Swizzle<Vector3, 0,1,0> E0 ## E1 ## E0; \
	vec3Swizzle<Vector3, 0,1,1> E0 ## E1 ## E1; \
	vec3Swizzle<Vector3, 0,1,2> E0 ## E1 ## E2; \
	vec3Swizzle<Vector3, 0,1,3> E0 ## E1 ## E3; \
	vec3Swizzle<Vector3, 0,2,0> E0 ## E2 ## E0; \
	vec3Swizzle<Vector3, 0,2,1> E0 ## E2 ## E1; \
	vec3Swizzle<Vector3, 0,2,2> E0 ## E2 ## E2; \
	vec3Swizzle<Vector3, 0,2,3> E0 ## E2 ## E3; \
	vec3Swizzle<Vector3, 0,3,0> E0 ## E3 ## E0; \
	vec3Swizzle<Vector3, 0,3,1> E0 ## E3 ## E1; \
	vec3Swizzle<Vector3, 0,3,2> E0 ## E3 ## E2; \
	vec3Swizzle<Vector3, 0,3,3> E0 ## E3 ## E3; \
	vec3Swizzle<Vector3, 1,0,0> E1 ## E0 ## E0; \
	vec3Swizzle<Vector3, 1,0,1> E1 ## E0 ## E1; \
	vec3Swizzle<Vector3, 1,0,2> E1 ## E0 ## E2; \
	vec3Swizzle<Vector3, 1,0,3> E1 ## E0 ## E3; \
	vec3Swizzle<Vector3, 1,1,0> E1 ## E1 ## E0; \
	vec3Swizzle<Vector3, 1,1,1> E1 ## E1 ## E1; \
	vec3Swizzle<Vector3, 1,1,2> E1 ## E1 ## E2; \
	vec3Swizzle<Vector3, 1,1,3> E1 ## E1 ## E3; \
	vec3Swizzle<Vector3, 1,2,0> E1 ## E2 ## E0; \
	vec3Swizzle<Vector3, 1,2,1> E1 ## E2 ## E1; \
	vec3Swizzle<Vector3, 1,2,2> E1 ## E2 ## E2; \
	vec3Swizzle<Vector3, 1,2,3> E1 ## E2 ## E3; \
	vec3Swizzle<Vector3, 1,3,0> E1 ## E3 ## E0; \
	vec3Swizzle<Vector3, 1,3,1> E1 ## E3 ## E1; \
	vec3Swizzle<Vector3, 1,3,2> E1 ## E3 ## E2; \
	vec3Swizzle<Vector3, 1,3,3> E1 ## E3 ## E3; \
	vec3Swizzle<Vector3, 2,0,0> E2 ## E0 ## E0; \
	vec3Swizzle<Vector3, 2,0,1> E2 ## E0 ## E1; \
	vec3Swizzle<Vector3, 2,0,2> E2 ## E0 ## E2; \
	vec3Swizzle<Vector3, 2,0,3> E2 ## E0 ## E3; \
	vec3Swizzle<Vector3, 2,1,0> E2 ## E1 ## E0; \
	vec3Swizzle<Vector3, 2,1,1> E2 ## E1 ## E1; \
	vec3Swizzle<Vector3, 2,1,2> E2 ## E1 ## E2; \
	vec3Swizzle<Vector3, 2,1,3> E2 ## E1 ## E3; \
	vec3Swizzle<Vector3, 2,2,0> E2 ## E2 ## E0; \
	vec3Swizzle<Vector3, 2,2,1> E2 ## E2 ## E1; \
	vec3Swizzle<Vector3, 2,2,2> E2 ## E2 ## E2; \
	vec3Swizzle<Vector3, 2,2,3> E2 ## E2 ## E3; \
	vec3Swizzle<Vector3, 2,3,0> E2 ## E3 ## E0; \
	vec3Swizzle<Vector3, 2,3,1> E2 ## E3 ## E1; \
	vec3Swizzle<Vector3, 2,3,2> E2 ## E3 ## E2; \
	vec3Swizzle<Vector3, 2,3,3> E2 ## E3 ## E3; \
	vec3Swizzle<Vector3, 3,0,0> E3 ## E0 ## E0; \
	vec3Swizzle<Vector3, 3,0,1> E3 ## E0 ## E1; \
	vec3Swizzle<Vector3, 3,0,2> E3 ## E0 ## E2; \
	vec3Swizzle<Vector3, 3,0,3> E3 ## E0 ## E3; \
	vec3Swizzle<Vector3, 3,1,0> E3 ## E1 ## E0; \
	vec3Swizzle<Vector3, 3,1,1> E3 ## E1 ## E1; \
	vec3Swizzle<Vector3, 3,1,2> E3 ## E1 ## E2; \
	vec3Swizzle<Vector3, 3,1,3> E3 ## E1 ## E3; \
	vec3Swizzle<Vector3, 3,2,0> E3 ## E2 ## E0; \
	vec3Swizzle<Vector3, 3,2,1> E3 ## E2 ## E1; \
	vec3Swizzle<Vector3, 3,2,2> E3 ## E2 ## E2; \
	vec3Swizzle<Vector3, 3,2,3> E3 ## E2 ## E3; \
	vec3Swizzle<Vector3, 3,3,0> E3 ## E3 ## E0; \
	vec3Swizzle<Vector3, 3,3,1> E3 ## E3 ## E1; \
	vec3Swizzle<Vector3, 3,3,2> E3 ## E3 ## E2; \
	vec3Swizzle<Vector3, 3,3,3> E3 ## E3 ## E3;

#define REBORN_SWIZZLE4_4_MEMBERS(E0,E1,E2,E3) \
	vec4Swizzle<Vector4, 0, 0, 0, 0> E0 ## E0 ## E0 ## E0;\
	vec4Swizzle<Vector4, 0, 0, 0, 1> E0 ## E0 ## E0 ## E1;\
	vec4Swizzle<Vector4, 0, 0, 0, 2> E0 ## E0 ## E0 ## E2;\
	vec4Swizzle<Vector4, 0, 0, 0, 3> E0 ## E0 ## E0 ## E3;\
	vec4Swizzle<Vector4, 0, 0, 1, 0> E0 ## E0 ## E1 ## E0;\
	vec4Swizzle<Vector4, 0, 0, 1, 1> E0 ## E0 ## E1 ## E1;\
	vec4Swizzle<Vector4, 0, 0, 1, 2> E0 ## E0 ## E1 ## E2;\
	vec4Swizzle<Vector4, 0, 0, 1, 3> E0 ## E0 ## E1 ## E3;\
	vec4Swizzle<Vector4, 0, 0, 2, 0> E0 ## E0 ## E2 ## E0;\
	vec4Swizzle<Vector4, 0, 0, 2, 1> E0 ## E0 ## E2 ## E1;\
	vec4Swizzle<Vector4, 0, 0, 2, 2> E0 ## E0 ## E2 ## E2;\
	vec4Swizzle<Vector4, 0, 0, 2, 3> E0 ## E0 ## E2 ## E3;\
	vec4Swizzle<Vector4, 0, 0, 3, 0> E0 ## E0 ## E3 ## E0;\
	vec4Swizzle<Vector4, 0, 0, 3, 1> E0 ## E0 ## E3 ## E1;\
	vec4Swizzle<Vector4, 0, 0, 3, 2> E0 ## E0 ## E3 ## E2;\
	vec4Swizzle<Vector4, 0, 0, 3, 3> E0 ## E0 ## E3 ## E3;\
	vec4Swizzle<Vector4, 0, 1, 0, 0> E0 ## E1 ## E0 ## E0;\
	vec4Swizzle<Vector4, 0, 1, 0, 1> E0 ## E1 ## E0 ## E1;\
	vec4Swizzle<Vector4, 0, 1, 0, 2> E0 ## E1 ## E0 ## E2;\
	vec4Swizzle<Vector4, 0, 1, 0, 3> E0 ## E1 ## E0 ## E3;\
	vec4Swizzle<Vector4, 0, 1, 1, 0> E0 ## E1 ## E1 ## E0;\
	vec4Swizzle<Vector4, 0, 1, 1, 1> E0 ## E1 ## E1 ## E1;\
	vec4Swizzle<Vector4, 0, 1, 1, 2> E0 ## E1 ## E1 ## E2;\
	vec4Swizzle<Vector4, 0, 1, 1, 3> E0 ## E1 ## E1 ## E3;\
	vec4Swizzle<Vector4, 0, 1, 2, 0> E0 ## E1 ## E2 ## E0;\
	vec4Swizzle<Vector4, 0, 1, 2, 1> E0 ## E1 ## E2 ## E1;\
	vec4Swizzle<Vector4, 0, 1, 2, 2> E0 ## E1 ## E2 ## E2;\
	vec4Swizzle<Vector4, 0, 1, 2, 3> E0 ## E1 ## E2 ## E3;\
	vec4Swizzle<Vector4, 0, 1, 3, 0> E0 ## E1 ## E3 ## E0;\
	vec4Swizzle<Vector4, 0, 1, 3, 1> E0 ## E1 ## E3 ## E1;\
	vec4Swizzle<Vector4, 0, 1, 3, 2> E0 ## E1 ## E3 ## E2;\
	vec4Swizzle<Vector4, 0, 1, 3, 3> E0 ## E1 ## E3 ## E3;\
	vec4Swizzle<Vector4, 0, 2, 0, 0> E0 ## E2 ## E0 ## E0;\
	vec4Swizzle<Vector4, 0, 2, 0, 1> E0 ## E2 ## E0 ## E1;\
	vec4Swizzle<Vector4, 0, 2, 0, 2> E0 ## E2 ## E0 ## E2;\
	vec4Swizzle<Vector4, 0, 2, 0, 3> E0 ## E2 ## E0 ## E3;\
	vec4Swizzle<Vector4, 0, 2, 1, 0> E0 ## E2 ## E1 ## E0;\
	vec4Swizzle<Vector4, 0, 2, 1, 1> E0 ## E2 ## E1 ## E1;\
	vec4Swizzle<Vector4, 0, 2, 1, 2> E0 ## E2 ## E1 ## E2;\
	vec4Swizzle<Vector4, 0, 2, 1, 3> E0 ## E2 ## E1 ## E3;\
	vec4Swizzle<Vector4, 0, 2, 2, 0> E0 ## E2 ## E2 ## E0;\
	vec4Swizzle<Vector4, 0, 2, 2, 1> E0 ## E2 ## E2 ## E1;\
	vec4Swizzle<Vector4, 0, 2, 2, 2> E0 ## E2 ## E2 ## E2;\
	vec4Swizzle<Vector4, 0, 2, 2, 3> E0 ## E2 ## E2 ## E3;\
	vec4Swizzle<Vector4, 0, 2, 3, 0> E0 ## E2 ## E3 ## E0;\
	vec4Swizzle<Vector4, 0, 2, 3, 1> E0 ## E2 ## E3 ## E1;\
	vec4Swizzle<Vector4, 0, 2, 3, 2> E0 ## E2 ## E3 ## E2;\
	vec4Swizzle<Vector4, 0, 2, 3, 3> E0 ## E2 ## E3 ## E3;\
	vec4Swizzle<Vector4, 0, 3, 0, 0> E0 ## E3 ## E0 ## E0;\
	vec4Swizzle<Vector4, 0, 3, 0, 1> E0 ## E3 ## E0 ## E1;\
	vec4Swizzle<Vector4, 0, 3, 0, 2> E0 ## E3 ## E0 ## E2;\
	vec4Swizzle<Vector4, 0, 3, 0, 3> E0 ## E3 ## E0 ## E3;\
	vec4Swizzle<Vector4, 0, 3, 1, 0> E0 ## E3 ## E1 ## E0;\
	vec4Swizzle<Vector4, 0, 3, 1, 1> E0 ## E3 ## E1 ## E1;\
	vec4Swizzle<Vector4, 0, 3, 1, 2> E0 ## E3 ## E1 ## E2;\
	vec4Swizzle<Vector4, 0, 3, 1, 3> E0 ## E3 ## E1 ## E3;\
	vec4Swizzle<Vector4, 0, 3, 2, 0> E0 ## E3 ## E2 ## E0;\
	vec4Swizzle<Vector4, 0, 3, 2, 1> E0 ## E3 ## E2 ## E1;\
	vec4Swizzle<Vector4, 0, 3, 2, 2> E0 ## E3 ## E2 ## E2;\
	vec4Swizzle<Vector4, 0, 3, 2, 3> E0 ## E3 ## E2 ## E3;\
	vec4Swizzle<Vector4, 0, 3, 3, 0> E0 ## E3 ## E3 ## E0;\
	vec4Swizzle<Vector4, 0, 3, 3, 1> E0 ## E3 ## E3 ## E1;\
	vec4Swizzle<Vector4, 0, 3, 3, 2> E0 ## E3 ## E3 ## E2;\
	vec4Swizzle<Vector4, 0, 3, 3, 3> E0 ## E3 ## E3 ## E3;\
	vec4Swizzle<Vector4, 1, 0, 0, 0> E1 ## E0 ## E0 ## E0;\
	vec4Swizzle<Vector4, 1, 0, 0, 1> E1 ## E0 ## E0 ## E1;\
	vec4Swizzle<Vector4, 1, 0, 0, 2> E1 ## E0 ## E0 ## E2;\
	vec4Swizzle<Vector4, 1, 0, 0, 3> E1 ## E0 ## E0 ## E3;\
	vec4Swizzle<Vector4, 1, 0, 1, 0> E1 ## E0 ## E1 ## E0;\
	vec4Swizzle<Vector4, 1, 0, 1, 1> E1 ## E0 ## E1 ## E1;\
	vec4Swizzle<Vector4, 1, 0, 1, 2> E1 ## E0 ## E1 ## E2;\
	vec4Swizzle<Vector4, 1, 0, 1, 3> E1 ## E0 ## E1 ## E3;\
	vec4Swizzle<Vector4, 1, 0, 2, 0> E1 ## E0 ## E2 ## E0;\
	vec4Swizzle<Vector4, 1, 0, 2, 1> E1 ## E0 ## E2 ## E1;\
	vec4Swizzle<Vector4, 1, 0, 2, 2> E1 ## E0 ## E2 ## E2;\
	vec4Swizzle<Vector4, 1, 0, 2, 3> E1 ## E0 ## E2 ## E3;\
	vec4Swizzle<Vector4, 1, 0, 3, 0> E1 ## E0 ## E3 ## E0;\
	vec4Swizzle<Vector4, 1, 0, 3, 1> E1 ## E0 ## E3 ## E1;\
	vec4Swizzle<Vector4, 1, 0, 3, 2> E1 ## E0 ## E3 ## E2;\
	vec4Swizzle<Vector4, 1, 0, 3, 3> E1 ## E0 ## E3 ## E3;\
	vec4Swizzle<Vector4, 1, 1, 0, 0> E1 ## E1 ## E0 ## E0;\
	vec4Swizzle<Vector4, 1, 1, 0, 1> E1 ## E1 ## E0 ## E1;\
	vec4Swizzle<Vector4, 1, 1, 0, 2> E1 ## E1 ## E0 ## E2;\
	vec4Swizzle<Vector4, 1, 1, 0, 3> E1 ## E1 ## E0 ## E3;\
	vec4Swizzle<Vector4, 1, 1, 1, 0> E1 ## E1 ## E1 ## E0;\
	vec4Swizzle<Vector4, 1, 1, 1, 1> E1 ## E1 ## E1 ## E1;\
	vec4Swizzle<Vector4, 1, 1, 1, 2> E1 ## E1 ## E1 ## E2;\
	vec4Swizzle<Vector4, 1, 1, 1, 3> E1 ## E1 ## E1 ## E3;\
	vec4Swizzle<Vector4, 1, 1, 2, 0> E1 ## E1 ## E2 ## E0;\
	vec4Swizzle<Vector4, 1, 1, 2, 1> E1 ## E1 ## E2 ## E1;\
	vec4Swizzle<Vector4, 1, 1, 2, 2> E1 ## E1 ## E2 ## E2;\
	vec4Swizzle<Vector4, 1, 1, 2, 3> E1 ## E1 ## E2 ## E3;\
	vec4Swizzle<Vector4, 1, 1, 3, 0> E1 ## E1 ## E3 ## E0;\
	vec4Swizzle<Vector4, 1, 1, 3, 1> E1 ## E1 ## E3 ## E1;\
	vec4Swizzle<Vector4, 1, 1, 3, 2> E1 ## E1 ## E3 ## E2;\
	vec4Swizzle<Vector4, 1, 1, 3, 3> E1 ## E1 ## E3 ## E3;\
	vec4Swizzle<Vector4, 1, 2, 0, 0> E1 ## E2 ## E0 ## E0;\
	vec4Swizzle<Vector4, 1, 2, 0, 1> E1 ## E2 ## E0 ## E1;\
	vec4Swizzle<Vector4, 1, 2, 0, 2> E1 ## E2 ## E0 ## E2;\
	vec4Swizzle<Vector4, 1, 2, 0, 3> E1 ## E2 ## E0 ## E3;\
	vec4Swizzle<Vector4, 1, 2, 1, 0> E1 ## E2 ## E1 ## E0;\
	vec4Swizzle<Vector4, 1, 2, 1, 1> E1 ## E2 ## E1 ## E1;\
	vec4Swizzle<Vector4, 1, 2, 1, 2> E1 ## E2 ## E1 ## E2;\
	vec4Swizzle<Vector4, 1, 2, 1, 3> E1 ## E2 ## E1 ## E3;\
	vec4Swizzle<Vector4, 1, 2, 2, 0> E1 ## E2 ## E2 ## E0;\
	vec4Swizzle<Vector4, 1, 2, 2, 1> E1 ## E2 ## E2 ## E1;\
	vec4Swizzle<Vector4, 1, 2, 2, 2> E1 ## E2 ## E2 ## E2;\
	vec4Swizzle<Vector4, 1, 2, 2, 3> E1 ## E2 ## E2 ## E3;\
	vec4Swizzle<Vector4, 1, 2, 3, 0> E1 ## E2 ## E3 ## E0;\
	vec4Swizzle<Vector4, 1, 2, 3, 1> E1 ## E2 ## E3 ## E1;\
	vec4Swizzle<Vector4, 1, 2, 3, 2> E1 ## E2 ## E3 ## E2;\
	vec4Swizzle<Vector4, 1, 2, 3, 3> E1 ## E2 ## E3 ## E3;\
	vec4Swizzle<Vector4, 1, 3, 0, 0> E1 ## E3 ## E0 ## E0;\
	vec4Swizzle<Vector4, 1, 3, 0, 1> E1 ## E3 ## E0 ## E1;\
	vec4Swizzle<Vector4, 1, 3, 0, 2> E1 ## E3 ## E0 ## E2;\
	vec4Swizzle<Vector4, 1, 3, 0, 3> E1 ## E3 ## E0 ## E3;\
	vec4Swizzle<Vector4, 1, 3, 1, 0> E1 ## E3 ## E1 ## E0;\
	vec4Swizzle<Vector4, 1, 3, 1, 1> E1 ## E3 ## E1 ## E1;\
	vec4Swizzle<Vector4, 1, 3, 1, 2> E1 ## E3 ## E1 ## E2;\
	vec4Swizzle<Vector4, 1, 3, 1, 3> E1 ## E3 ## E1 ## E3;\
	vec4Swizzle<Vector4, 1, 3, 2, 0> E1 ## E3 ## E2 ## E0;\
	vec4Swizzle<Vector4, 1, 3, 2, 1> E1 ## E3 ## E2 ## E1;\
	vec4Swizzle<Vector4, 1, 3, 2, 2> E1 ## E3 ## E2 ## E2;\
	vec4Swizzle<Vector4, 1, 3, 2, 3> E1 ## E3 ## E2 ## E3;\
	vec4Swizzle<Vector4, 1, 3, 3, 0> E1 ## E3 ## E3 ## E0;\
	vec4Swizzle<Vector4, 1, 3, 3, 1> E1 ## E3 ## E3 ## E1;\
	vec4Swizzle<Vector4, 1, 3, 3, 2> E1 ## E3 ## E3 ## E2;\
	vec4Swizzle<Vector4, 1, 3, 3, 3> E1 ## E3 ## E3 ## E3;\
	vec4Swizzle<Vector4, 2, 0, 0, 0> E2 ## E0 ## E0 ## E0;\
	vec4Swizzle<Vector4, 2, 0, 0, 1> E2 ## E0 ## E0 ## E1;\
	vec4Swizzle<Vector4, 2, 0, 0, 2> E2 ## E0 ## E0 ## E2;\
	vec4Swizzle<Vector4, 2, 0, 0, 3> E2 ## E0 ## E0 ## E3;\
	vec4Swizzle<Vector4, 2, 0, 1, 0> E2 ## E0 ## E1 ## E0;\
	vec4Swizzle<Vector4, 2, 0, 1, 1> E2 ## E0 ## E1 ## E1;\
	vec4Swizzle<Vector4, 2, 0, 1, 2> E2 ## E0 ## E1 ## E2;\
	vec4Swizzle<Vector4, 2, 0, 1, 3> E2 ## E0 ## E1 ## E3;\
	vec4Swizzle<Vector4, 2, 0, 2, 0> E2 ## E0 ## E2 ## E0;\
	vec4Swizzle<Vector4, 2, 0, 2, 1> E2 ## E0 ## E2 ## E1;\
	vec4Swizzle<Vector4, 2, 0, 2, 2> E2 ## E0 ## E2 ## E2;\
	vec4Swizzle<Vector4, 2, 0, 2, 3> E2 ## E0 ## E2 ## E3;\
	vec4Swizzle<Vector4, 2, 0, 3, 0> E2 ## E0 ## E3 ## E0;\
	vec4Swizzle<Vector4, 2, 0, 3, 1> E2 ## E0 ## E3 ## E1;\
	vec4Swizzle<Vector4, 2, 0, 3, 2> E2 ## E0 ## E3 ## E2;\
	vec4Swizzle<Vector4, 2, 0, 3, 3> E2 ## E0 ## E3 ## E3;\
	vec4Swizzle<Vector4, 2, 1, 0, 0> E2 ## E1 ## E0 ## E0;\
	vec4Swizzle<Vector4, 2, 1, 0, 1> E2 ## E1 ## E0 ## E1;\
	vec4Swizzle<Vector4, 2, 1, 0, 2> E2 ## E1 ## E0 ## E2;\
	vec4Swizzle<Vector4, 2, 1, 0, 3> E2 ## E1 ## E0 ## E3;\
	vec4Swizzle<Vector4, 2, 1, 1, 0> E2 ## E1 ## E1 ## E0;\
	vec4Swizzle<Vector4, 2, 1, 1, 1> E2 ## E1 ## E1 ## E1;\
	vec4Swizzle<Vector4, 2, 1, 1, 2> E2 ## E1 ## E1 ## E2;\
	vec4Swizzle<Vector4, 2, 1, 1, 3> E2 ## E1 ## E1 ## E3;\
	vec4Swizzle<Vector4, 2, 1, 2, 0> E2 ## E1 ## E2 ## E0;\
	vec4Swizzle<Vector4, 2, 1, 2, 1> E2 ## E1 ## E2 ## E1;\
	vec4Swizzle<Vector4, 2, 1, 2, 2> E2 ## E1 ## E2 ## E2;\
	vec4Swizzle<Vector4, 2, 1, 2, 3> E2 ## E1 ## E2 ## E3;\
	vec4Swizzle<Vector4, 2, 1, 3, 0> E2 ## E1 ## E3 ## E0;\
	vec4Swizzle<Vector4, 2, 1, 3, 1> E2 ## E1 ## E3 ## E1;\
	vec4Swizzle<Vector4, 2, 1, 3, 2> E2 ## E1 ## E3 ## E2;\
	vec4Swizzle<Vector4, 2, 1, 3, 3> E2 ## E1 ## E3 ## E3;\
	vec4Swizzle<Vector4, 2, 2, 0, 0> E2 ## E2 ## E0 ## E0;\
	vec4Swizzle<Vector4, 2, 2, 0, 1> E2 ## E2 ## E0 ## E1;\
	vec4Swizzle<Vector4, 2, 2, 0, 2> E2 ## E2 ## E0 ## E2;\
	vec4Swizzle<Vector4, 2, 2, 0, 3> E2 ## E2 ## E0 ## E3;\
	vec4Swizzle<Vector4, 2, 2, 1, 0> E2 ## E2 ## E1 ## E0;\
	vec4Swizzle<Vector4, 2, 2, 1, 1> E2 ## E2 ## E1 ## E1;\
	vec4Swizzle<Vector4, 2, 2, 1, 2> E2 ## E2 ## E1 ## E2;\
	vec4Swizzle<Vector4, 2, 2, 1, 3> E2 ## E2 ## E1 ## E3;\
	vec4Swizzle<Vector4, 2, 2, 2, 0> E2 ## E2 ## E2 ## E0;\
	vec4Swizzle<Vector4, 2, 2, 2, 1> E2 ## E2 ## E2 ## E1;\
	vec4Swizzle<Vector4, 2, 2, 2, 2> E2 ## E2 ## E2 ## E2;\
	vec4Swizzle<Vector4, 2, 2, 2, 3> E2 ## E2 ## E2 ## E3;\
	vec4Swizzle<Vector4, 2, 2, 3, 0> E2 ## E2 ## E3 ## E0;\
	vec4Swizzle<Vector4, 2, 2, 3, 1> E2 ## E2 ## E3 ## E1;\
	vec4Swizzle<Vector4, 2, 2, 3, 2> E2 ## E2 ## E3 ## E2;\
	vec4Swizzle<Vector4, 2, 2, 3, 3> E2 ## E2 ## E3 ## E3;\
	vec4Swizzle<Vector4, 2, 3, 0, 0> E2 ## E3 ## E0 ## E0;\
	vec4Swizzle<Vector4, 2, 3, 0, 1> E2 ## E3 ## E0 ## E1;\
	vec4Swizzle<Vector4, 2, 3, 0, 2> E2 ## E3 ## E0 ## E2;\
	vec4Swizzle<Vector4, 2, 3, 0, 3> E2 ## E3 ## E0 ## E3;\
	vec4Swizzle<Vector4, 2, 3, 1, 0> E2 ## E3 ## E1 ## E0;\
	vec4Swizzle<Vector4, 2, 3, 1, 1> E2 ## E3 ## E1 ## E1;\
	vec4Swizzle<Vector4, 2, 3, 1, 2> E2 ## E3 ## E1 ## E2;\
	vec4Swizzle<Vector4, 2, 3, 1, 3> E2 ## E3 ## E1 ## E3;\
	vec4Swizzle<Vector4, 2, 3, 2, 0> E2 ## E3 ## E2 ## E0;\
	vec4Swizzle<Vector4, 2, 3, 2, 1> E2 ## E3 ## E2 ## E1;\
	vec4Swizzle<Vector4, 2, 3, 2, 2> E2 ## E3 ## E2 ## E2;\
	vec4Swizzle<Vector4, 2, 3, 2, 3> E2 ## E3 ## E2 ## E3;\
	vec4Swizzle<Vector4, 2, 3, 3, 0> E2 ## E3 ## E3 ## E0;\
	vec4Swizzle<Vector4, 2, 3, 3, 1> E2 ## E3 ## E3 ## E1;\
	vec4Swizzle<Vector4, 2, 3, 3, 2> E2 ## E3 ## E3 ## E2;\
	vec4Swizzle<Vector4, 2, 3, 3, 3> E2 ## E3 ## E3 ## E3;\
	vec4Swizzle<Vector4, 3, 0, 0, 0> E3 ## E0 ## E0 ## E0;\
	vec4Swizzle<Vector4, 3, 0, 0, 1> E3 ## E0 ## E0 ## E1;\
	vec4Swizzle<Vector4, 3, 0, 0, 2> E3 ## E0 ## E0 ## E2;\
	vec4Swizzle<Vector4, 3, 0, 0, 3> E3 ## E0 ## E0 ## E3;\
	vec4Swizzle<Vector4, 3, 0, 1, 0> E3 ## E0 ## E1 ## E0;\
	vec4Swizzle<Vector4, 3, 0, 1, 1> E3 ## E0 ## E1 ## E1;\
	vec4Swizzle<Vector4, 3, 0, 1, 2> E3 ## E0 ## E1 ## E2;\
	vec4Swizzle<Vector4, 3, 0, 1, 3> E3 ## E0 ## E1 ## E3;\
	vec4Swizzle<Vector4, 3, 0, 2, 0> E3 ## E0 ## E2 ## E0;\
	vec4Swizzle<Vector4, 3, 0, 2, 1> E3 ## E0 ## E2 ## E1;\
	vec4Swizzle<Vector4, 3, 0, 2, 2> E3 ## E0 ## E2 ## E2;\
	vec4Swizzle<Vector4, 3, 0, 2, 3> E3 ## E0 ## E2 ## E3;\
	vec4Swizzle<Vector4, 3, 0, 3, 0> E3 ## E0 ## E3 ## E0;\
	vec4Swizzle<Vector4, 3, 0, 3, 1> E3 ## E0 ## E3 ## E1;\
	vec4Swizzle<Vector4, 3, 0, 3, 2> E3 ## E0 ## E3 ## E2;\
	vec4Swizzle<Vector4, 3, 0, 3, 3> E3 ## E0 ## E3 ## E3;\
	vec4Swizzle<Vector4, 3, 1, 0, 0> E3 ## E1 ## E0 ## E0;\
	vec4Swizzle<Vector4, 3, 1, 0, 1> E3 ## E1 ## E0 ## E1;\
	vec4Swizzle<Vector4, 3, 1, 0, 2> E3 ## E1 ## E0 ## E2;\
	vec4Swizzle<Vector4, 3, 1, 0, 3> E3 ## E1 ## E0 ## E3;\
	vec4Swizzle<Vector4, 3, 1, 1, 0> E3 ## E1 ## E1 ## E0;\
	vec4Swizzle<Vector4, 3, 1, 1, 1> E3 ## E1 ## E1 ## E1;\
	vec4Swizzle<Vector4, 3, 1, 1, 2> E3 ## E1 ## E1 ## E2;\
	vec4Swizzle<Vector4, 3, 1, 1, 3> E3 ## E1 ## E1 ## E3;\
	vec4Swizzle<Vector4, 3, 1, 2, 0> E3 ## E1 ## E2 ## E0;\
	vec4Swizzle<Vector4, 3, 1, 2, 1> E3 ## E1 ## E2 ## E1;\
	vec4Swizzle<Vector4, 3, 1, 2, 2> E3 ## E1 ## E2 ## E2;\
	vec4Swizzle<Vector4, 3, 1, 2, 3> E3 ## E1 ## E2 ## E3;\
	vec4Swizzle<Vector4, 3, 1, 3, 0> E3 ## E1 ## E3 ## E0;\
	vec4Swizzle<Vector4, 3, 1, 3, 1> E3 ## E1 ## E3 ## E1;\
	vec4Swizzle<Vector4, 3, 1, 3, 2> E3 ## E1 ## E3 ## E2;\
	vec4Swizzle<Vector4, 3, 1, 3, 3> E3 ## E1 ## E3 ## E3;\
	vec4Swizzle<Vector4, 3, 2, 0, 0> E3 ## E2 ## E0 ## E0;\
	vec4Swizzle<Vector4, 3, 2, 0, 1> E3 ## E2 ## E0 ## E1;\
	vec4Swizzle<Vector4, 3, 2, 0, 2> E3 ## E2 ## E0 ## E2;\
	vec4Swizzle<Vector4, 3, 2, 0, 3> E3 ## E2 ## E0 ## E3;\
	vec4Swizzle<Vector4, 3, 2, 1, 0> E3 ## E2 ## E1 ## E0;\
	vec4Swizzle<Vector4, 3, 2, 1, 1> E3 ## E2 ## E1 ## E1;\
	vec4Swizzle<Vector4, 3, 2, 1, 2> E3 ## E2 ## E1 ## E2;\
	vec4Swizzle<Vector4, 3, 2, 1, 3> E3 ## E2 ## E1 ## E3;\
	vec4Swizzle<Vector4, 3, 2, 2, 0> E3 ## E2 ## E2 ## E0;\
	vec4Swizzle<Vector4, 3, 2, 2, 1> E3 ## E2 ## E2 ## E1;\
	vec4Swizzle<Vector4, 3, 2, 2, 2> E3 ## E2 ## E2 ## E2;\
	vec4Swizzle<Vector4, 3, 2, 2, 3> E3 ## E2 ## E2 ## E3;\
	vec4Swizzle<Vector4, 3, 2, 3, 0> E3 ## E2 ## E3 ## E0;\
	vec4Swizzle<Vector4, 3, 2, 3, 1> E3 ## E2 ## E3 ## E1;\
	vec4Swizzle<Vector4, 3, 2, 3, 2> E3 ## E2 ## E3 ## E2;\
	vec4Swizzle<Vector4, 3, 2, 3, 3> E3 ## E2 ## E3 ## E3;\
	vec4Swizzle<Vector4, 3, 3, 0, 0> E3 ## E3 ## E0 ## E0;\
	vec4Swizzle<Vector4, 3, 3, 0, 1> E3 ## E3 ## E0 ## E1;\
	vec4Swizzle<Vector4, 3, 3, 0, 2> E3 ## E3 ## E0 ## E2;\
	vec4Swizzle<Vector4, 3, 3, 0, 3> E3 ## E3 ## E0 ## E3;\
	vec4Swizzle<Vector4, 3, 3, 1, 0> E3 ## E3 ## E1 ## E0;\
	vec4Swizzle<Vector4, 3, 3, 1, 1> E3 ## E3 ## E1 ## E1;\
	vec4Swizzle<Vector4, 3, 3, 1, 2> E3 ## E3 ## E1 ## E2;\
	vec4Swizzle<Vector4, 3, 3, 1, 3> E3 ## E3 ## E1 ## E3;\
	vec4Swizzle<Vector4, 3, 3, 2, 0> E3 ## E3 ## E2 ## E0;\
	vec4Swizzle<Vector4, 3, 3, 2, 1> E3 ## E3 ## E2 ## E1;\
	vec4Swizzle<Vector4, 3, 3, 2, 2> E3 ## E3 ## E2 ## E2;\
	vec4Swizzle<Vector4, 3, 3, 2, 3> E3 ## E3 ## E2 ## E3;\
	vec4Swizzle<Vector4, 3, 3, 3, 0> E3 ## E3 ## E3 ## E0;\
	vec4Swizzle<Vector4, 3, 3, 3, 1> E3 ## E3 ## E3 ## E1;\
	vec4Swizzle<Vector4, 3, 3, 3, 2> E3 ## E3 ## E3 ## E2;\
	vec4Swizzle<Vector4, 3, 3, 3, 3> E3 ## E3 ## E3 ## E3;\
