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
}