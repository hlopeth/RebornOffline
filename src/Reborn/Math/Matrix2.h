#pragma once
#include "Vector.h"

namespace Reborn {
	class Matrix2 {
	public:
		Matrix2() {
			for (int i = 0; i < this->length(); i++) {
				_d[i] = 0;
			}
		}

		Matrix2(const Matrix2& m) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] = m._d[i];
			}
		}

		Matrix2(
			const float& m00, const float& m01,
			const float& m10, const float& m11
		) {
			_d[0] = m00;
			_d[1] = m01;
			_d[2] = m10;
			_d[3] = m11;
		}

		Vector2 shape() const {
			return Vector2(2, 2);
		}

		size_t length() const {
			return 4;
		}

		float operator()(size_t i) const {
			return _d[i];
		}

		float& operator()(size_t i) {
			return _d[i];
		}

		float operator()(size_t i, size_t j) const {
			return _d[i * 2 + j];
		}

		float& operator()(size_t i, size_t j) {
			return _d[i * 2 + j];
		}

		Matrix2 operator+(float scalar) const {
			Matrix2 res = Matrix2::zero();
			for (int i = 0; i < this->length(); i++) {
				res(i) = _d[i] + scalar;
			}
			return res;
		}

		Matrix2 operator-(float scalar) const {
			Matrix2 res = Matrix2::zero();
			for (int i = 0; i < this->length(); i++) {
				res(i) = _d[i] - scalar;
			}
			return res;
		}

		Matrix2 operator*(float scalar) const {
			Matrix2 res = Matrix2::zero();
			for (int i = 0; i < this->length(); i++) {
				res(i) = _d[i] * scalar;
			}
			return res;
		}

		Matrix2 operator/(float scalar) const {
			Matrix2 res = Matrix2::zero();
			for (int i = 0; i < this->length(); i++) {
				res(i) = _d[i] / scalar;
			}
			return res;
		}

		Matrix2& operator+=(float scalar) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] += scalar;
			}
			return *this;
		}

		Matrix2& operator-=(float scalar) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] -= scalar;
			}
			return *this;
		}

		Matrix2& operator*=(float scalar) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] *= scalar;
			}
			return *this;
		}

		Matrix2& operator/=(float scalar) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] /= scalar;
			}
			return *this;
		}

		Matrix2 operator+(const Matrix2& mat) const {
			Matrix2 result = Matrix2::zero();
			for (int i = 0; i < this->length(); i++) {
				result(i) = _d[i] + mat._d[i];
			}
			return result;
		}
		Matrix2 operator-(const Matrix2& mat) const {
			Matrix2 result = Matrix2::zero();
			for (int i = 0; i < this->length(); i++) {
				result(i) = _d[i] - mat._d[i];
			}
			return result;
		}

		Matrix2 operator*(const Matrix2& m) const {
			return Matrix2(
				(*this)(0, 0) * m(0, 0) + (*this)(0, 1) * m(1, 0),
				(*this)(0, 0) * m(0, 1) + (*this)(0, 1) * m(1, 1),
				(*this)(1, 0) * m(0, 0) + (*this)(1, 1) * m(1, 0),
				(*this)(1, 0) * m(0, 1) + (*this)(1, 1) * m(1, 1)
			);
		}

		Matrix2 operator/(const Matrix2& mat) const {
			Matrix2 result;
			result = *this * mat.inverce();
			return result;
		}

		Matrix2& operator+=(const Matrix2& mat) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] += mat._d[i];
			}
			return *this;
		}

		Matrix2& operator-=(const Matrix2& mat) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] -= mat._d[i];
			}
			return *this;
		}

		Matrix2& operator*=(const Matrix2& mat) {
			return (*this = *this * mat);
		}

		Matrix2& operator/=(const Matrix2& mat) {
			return *this *= mat.inverce();
		}

		Matrix2 transpose() const {
			Matrix2 result;
			result(0,0) = (*this)(0,0);
			result(0,1) = (*this)(1,0);
			result(1,0) = (*this)(0,1);
			result(1,1) = (*this)(1,1);
			return result;
		}

		float determinant() const {
			return (*this)(0, 0) * (*this)(1, 1) - (*this)(1, 0) * (*this)(0, 1);
		}

		Matrix2 inverce() const {
			float OneOverDeterminant = 1.f / this->determinant();

			Matrix2 inverse(
				+(*this)(1, 1) * OneOverDeterminant,
				-(*this)(0, 1) * OneOverDeterminant,
				-(*this)(1, 0) * OneOverDeterminant,
				+(*this)(0, 0) * OneOverDeterminant);

			return inverse;
		}

		static Matrix2 zero() {
			return Matrix2(0, 0, 0, 0);
		}
		static Matrix2 one() {
			return Matrix2(
				1, 0,
				0, 1
			);
		}
		std::string toString() const {
			std::stringstream str;
			str << "Matrix2: \n" << 
				"[" << _d[0] << "; " << _d[1] << " ]\n" <<
				"[" << _d[2] << "; " << _d[3] << " ]";
			return str.str();
		}
	private:
		float _d[4];
	};

	inline std::ostream& operator<<(std::ostream& os, const Matrix2& mat)
	{
		os << mat.toString();
		return os;
	}

}