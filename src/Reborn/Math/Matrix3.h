#pragma once
#include "Matrix2.h"

namespace Reborn {
	class Matrix3 {
	public:
		Matrix3() {
			for (int i = 0; i < this->length(); i++) {
				_d[i] = 0;
			}
		}

		Matrix3(const Matrix3& m) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] = m._d[i];
			}
		}

		Matrix3(
			const float& m00, const float& m01, const float& m02,
			const float& m10, const float& m11, const float& m12,
			const float& m20, const float& m21, const float& m22
		) {
			_d[0] = m00;
			_d[1] = m01;
			_d[2] = m02;

			_d[3] = m10;
			_d[4] = m11;
			_d[5] = m12;

			_d[6] = m20;
			_d[7] = m21;
			_d[8] = m22;
		}

		Vector2 shape() const {
			return Vector2(3, 3);
		}

		size_t length() const {
			return 9;
		}

		float operator()(size_t i) const {
			return _d[i];
		}

		float& operator()(size_t i) {
			return _d[i];
		}

		float operator()(size_t i, size_t j) const {
			return _d[i * 3 + j];
		}

		float& operator()(size_t i, size_t j) {
			return _d[i * 3 + j];
		}

		Matrix3 operator+(float scalar) const {
			Matrix3 res = Matrix3::zero();
			for (int i = 0; i < this->length(); i++) {
				res(i) = _d[i] + scalar;
			}
			return res;
		}

		Matrix3 operator-(float scalar) const {
			Matrix3 res = Matrix3::zero();
			for (int i = 0; i < this->length(); i++) {
				res(i) = _d[i] - scalar;
			}
			return res;
		}

		Matrix3 operator*(float scalar) const {
			Matrix3 res = Matrix3::zero();
			for (int i = 0; i < this->length(); i++) {
				res(i) = _d[i] * scalar;
			}
			return res;
		}

		Matrix3 operator/(float scalar) const {
			Matrix3 res = Matrix3::zero();
			for (int i = 0; i < this->length(); i++) {
				res(i) = _d[i] / scalar;
			}
			return res;
		}

		Matrix3& operator+=(float scalar) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] += scalar;
			}
			return *this;
		}

		Matrix3& operator-=(float scalar) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] -= scalar;
			}
			return *this;
		}

		Matrix3& operator*=(float scalar) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] *= scalar;
			}
			return *this;
		}

		Matrix3& operator/=(float scalar) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] /= scalar;
			}
			return *this;
		}

		Matrix3 operator+(const Matrix3& mat) const {
			Matrix3 result = Matrix3::zero();
			for (int i = 0; i < this->length(); i++) {
				result(i) = _d[i] + mat._d[i];
			}
			return result;
		}

		Matrix3 operator-(const Matrix3& mat) const {
			Matrix3 result = Matrix3::zero();
			for (int i = 0; i < this->length(); i++) {
				result(i) = _d[i] - mat._d[i];
			}
			return result;
		}

		Matrix3 operator*(const Matrix3& m) const {
			const float SrcA00 = (*this)(0,0);
			const float SrcA01 = (*this)(0,1);
			const float SrcA02 = (*this)(0,2);
			const float SrcA10 = (*this)(1,0);
			const float SrcA11 = (*this)(1,1);
			const float SrcA12 = (*this)(1,2);
			const float SrcA20 = (*this)(2,0);
			const float SrcA21 = (*this)(2,1);
			const float SrcA22 = (*this)(2,2);

			const float SrcB00 = m(0,0);
			const float SrcB01 = m(0,1);
			const float SrcB02 = m(0,2);
			const float SrcB10 = m(1,0);
			const float SrcB11 = m(1,1);
			const float SrcB12 = m(1,2);
			const float SrcB20 = m(2,0);
			const float SrcB21 = m(2,1);
			const float SrcB22 = m(2,2);

			Matrix3 result;
			result(0,0) = SrcA00 * SrcB00 + SrcA01 * SrcB10 + SrcA02 * SrcB20;
			result(0,1) = SrcA00 * SrcB01 + SrcA01 * SrcB11 + SrcA02 * SrcB21;
			result(0,2) = SrcA00 * SrcB02 + SrcA01 * SrcB12 + SrcA02 * SrcB22;
			result(1,0) = SrcA10 * SrcB00 + SrcA11 * SrcB10 + SrcA12 * SrcB20;
			result(1,1) = SrcA10 * SrcB01 + SrcA11 * SrcB11 + SrcA12 * SrcB21;
			result(1,2) = SrcA10 * SrcB02 + SrcA11 * SrcB12 + SrcA12 * SrcB22;
			result(2,0) = SrcA20 * SrcB00 + SrcA21 * SrcB10 + SrcA22 * SrcB20;
			result(2,1) = SrcA20 * SrcB01 + SrcA21 * SrcB11 + SrcA22 * SrcB21;
			result(2,2) = SrcA20 * SrcB02 + SrcA21 * SrcB12 + SrcA22 * SrcB22;
			return result;
		}

		Matrix3 operator/(const Matrix3& mat) const {
			Matrix3 result;
			result = (*this) * mat.inverse();
			return result;
		}

		Matrix3& operator+=(const Matrix3& mat) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] += mat._d[i];
			}
			return *this;
		}

		Matrix3& operator-=(const Matrix3& mat) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] -= mat._d[i];
			}
			return *this;
		}

		Matrix3& operator*=(const Matrix3& mat) {
			return (*this = *this * mat);
		}

		Matrix3& operator/=(const Matrix3& mat) {
			return *this *= mat.inverse();
		}

		Matrix3 transpose() const {
			Matrix3 result;
			result(0,0) = (*this)(0,0);
			result(0,1) = (*this)(1,0);
			result(0,2) = (*this)(2,0);

			result(1,0) = (*this)(0,1);
			result(1,1) = (*this)(1,1);
			result(1,2) = (*this)(2,1);

			result(2,0) = (*this)(0,2);
			result(2,1) = (*this)(1,2);
			result(2,2) = (*this)(2,2);
			return result;
		}

		float determinant() const {
			return
				+(*this)(0,0) * ((*this)(1,1) * (*this)(2,2) - (*this)(2,1) * (*this)(1,2))
				-(*this)(1,0) * ((*this)(0,1) * (*this)(2,2) - (*this)(2,1) * (*this)(0,2))
				+(*this)(2,0) * ((*this)(0,1) * (*this)(1,2) - (*this)(1,1) * (*this)(0,2));
		}

		Matrix3 inverse() const {
			const Matrix3& m = *this;
			float oneOverDeterminant = 1.f / this->determinant();

			Matrix3 inverse;
			inverse(0,0) = +(m(1,1) * m(2,2) - m(2,1) * m(1,2)) * oneOverDeterminant;
			inverse(1,0) = -(m(1,0) * m(2,2) - m(2,0) * m(1,2)) * oneOverDeterminant;
			inverse(2,0) = +(m(1,0) * m(2,1) - m(2,0) * m(1,1)) * oneOverDeterminant;
			inverse(0,1) = -(m(0,1) * m(2,2) - m(2,1) * m(0,2)) * oneOverDeterminant;
			inverse(1,1) = +(m(0,0) * m(2,2) - m(2,0) * m(0,2)) * oneOverDeterminant;
			inverse(2,1) = -(m(0,0) * m(2,1) - m(2,0) * m(0,1)) * oneOverDeterminant;
			inverse(0,2) = +(m(0,1) * m(1,2) - m(1,1) * m(0,2)) * oneOverDeterminant;
			inverse(1,2) = -(m(0,0) * m(1,2) - m(1,0) * m(0,2)) * oneOverDeterminant;
			inverse(2,2) = +(m(0,0) * m(1,1) - m(1,0) * m(0,1)) * oneOverDeterminant;

			return inverse;
		}

		static Matrix3 zero() {
			return Matrix3(
				0, 0, 0,
				0, 0, 0, 
				0, 0, 0
			);
		}
		static Matrix3 one() {
			return Matrix3(
				1, 0, 0,
				0, 1, 0,
				0, 0, 1
			);
		}

		std::string toString() const {
			std::stringstream str;
			str << "Matrix3: \n" <<
				"[" << _d[0] << "; " << _d[1] << "; " << _d[2] << " ]\n" <<
				"[" << _d[3] << "; " << _d[4] << "; " << _d[5] << " ]\n" <<
				"[" << _d[6] << "; " << _d[7] << "; " << _d[8] << " ]";
			return str.str();
		}
	private:
		float _d[9];
	};

	inline std::ostream& operator<<(std::ostream& os, const Matrix3& mat)
	{
		os << mat.toString();
		return os;
	}
}