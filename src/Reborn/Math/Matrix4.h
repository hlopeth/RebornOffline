#pragma once
#include "Vector4.h"

namespace Reborn {
	class Matrix4 {
	public:
		Matrix4() {
			for (int i = 0; i < this->length(); i++) {
				_d[i] = 0;
			}
		}

		Matrix4(const Matrix4& m) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] = m._d[i];
			}
		}

		Matrix4(
			const Vector4& row1,
			const Vector4& row2,
			const Vector4& row3,
			const Vector4& row4
		) {
			_d[0] = row1.x;
			_d[1] = row1.y;
			_d[2] = row1.z;
			_d[3] = row1.w;

			_d[4] = row2.x;
			_d[5] = row2.y;
			_d[6] = row2.z;
			_d[7] = row2.w;

			_d[8] = row3.x;
			_d[9] = row3.y;
			_d[10] = row3.z;
			_d[11] = row3.w;

			_d[12] = row4.x;
			_d[13] = row4.y;
			_d[14] = row4.z;
			_d[15] = row4.w;
		}

		Matrix4(
			const float& m00, const float& m01, const float& m02, const float& m03,
			const float& m10, const float& m11, const float& m12, const float& m13,
			const float& m20, const float& m21, const float& m22, const float& m23,
			const float& m30, const float& m31, const float& m32, const float& m33
		) {
			_d[0] = m00;
			_d[1] = m01;
			_d[2] = m02;
			_d[3] = m03;

			_d[4] = m10;
			_d[5] = m11;
			_d[6] = m12;
			_d[7] = m13;

			_d[8] = m20;
			_d[9] = m21;
			_d[10] = m22;
			_d[11] = m23;

			_d[12] = m30;
			_d[13] = m31;
			_d[14] = m32;
			_d[15] = m33;
		}

		Vector2 shape() const {
			return Vector2(4, 4);
		}

		size_t length() const {
			return 16;
		}

		float operator()(size_t i) const {
			return _d[i];
		}

		float& operator()(size_t i) {
			return _d[i];
		}

		float operator()(size_t i, size_t j) const {
			return _d[i * 4 + j];
		}

		float& operator()(size_t i, size_t j) {
			return _d[i * 4 + j];
		}

		Matrix4 operator+(float scalar) const {
			Matrix4 res = Matrix4::zero();
			for (int i = 0; i < this->length(); i++) {
				res(i) = _d[i] + scalar;
			}
			return res;
		}

		Matrix4 operator-(float scalar) const {
			Matrix4 res = Matrix4::zero();
			for (int i = 0; i < this->length(); i++) {
				res(i) = _d[i] - scalar;
			}
			return res;
		}

		Matrix4 operator*(float scalar) const {
			Matrix4 res = Matrix4::zero();
			for (int i = 0; i < this->length(); i++) {
				res(i) = _d[i] * scalar;
			}
			return res;
		}

		Matrix4 operator/(float scalar) const {
			Matrix4 res = Matrix4::zero();
			for (int i = 0; i < this->length(); i++) {
				res(i) = _d[i] / scalar;
			}
			return res;
		}

		Matrix4& operator+=(float scalar) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] += scalar;
			}
			return *this;
		}

		Matrix4& operator-=(float scalar) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] -= scalar;
			}
			return *this;
		}

		Matrix4& operator*=(float scalar) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] *= scalar;
			}
			return *this;
		}

		Matrix4& operator/=(float scalar) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] /= scalar;
			}
			return *this;
		}

		Matrix4 operator+(const Matrix4 mat) const {
			Matrix4 result = Matrix4::zero();
			for (int i = 0; i < this->length(); i++) {
				result(i) = _d[i] + mat._d[i];
			}
			return result;
		}

		Matrix4 operator-(const Matrix4 mat) const {
			Matrix4 result = Matrix4::zero();
			for (int i = 0; i < this->length(); i++) {
				result(i) = _d[i] - mat._d[i];
			}
			return result;
		}

		Matrix4 operator*(const Matrix4 mat) const {
			const float SrcA00 = (*this)(0, 0);
			const float SrcA01 = (*this)(0, 1);
			const float SrcA02 = (*this)(0, 2);
			const float SrcA03 = (*this)(0, 3);
			const float SrcA10 = (*this)(1, 0);
			const float SrcA11 = (*this)(1, 1);
			const float SrcA12 = (*this)(1, 2);
			const float SrcA13 = (*this)(1, 3);
			const float SrcA20 = (*this)(2, 0);
			const float SrcA21 = (*this)(2, 1);
			const float SrcA22 = (*this)(2, 2);
			const float SrcA23 = (*this)(2, 3);
			const float SrcA30 = (*this)(3, 0);
			const float SrcA31 = (*this)(3, 1);
			const float SrcA32 = (*this)(3, 2);
			const float SrcA33 = (*this)(3, 3);

			const float SrcB00 = mat(0, 0);
			const float SrcB01 = mat(0, 1);
			const float SrcB02 = mat(0, 2);
			const float SrcB03 = mat(0, 3);
			const float SrcB10 = mat(1, 0);
			const float SrcB11 = mat(1, 1);
			const float SrcB12 = mat(1, 2);
			const float SrcB13 = mat(1, 3);
			const float SrcB20 = mat(2, 0);
			const float SrcB21 = mat(2, 1);
			const float SrcB22 = mat(2, 2);
			const float SrcB23 = mat(2, 3);
			const float SrcB30 = mat(3, 0);
			const float SrcB31 = mat(3, 1);
			const float SrcB32 = mat(3, 2);
			const float SrcB33 = mat(3, 3);

			Matrix4 result;
			result(0, 0) = SrcA00 * SrcB00 + SrcA01 * SrcB10 + SrcA02 * SrcB20 + SrcA03 * SrcB30;
			result(0, 1) = SrcA00 * SrcB01 + SrcA01 * SrcB11 + SrcA02 * SrcB21 + SrcA03 * SrcB31;
			result(0, 2) = SrcA00 * SrcB02 + SrcA01 * SrcB12 + SrcA02 * SrcB22 + SrcA03 * SrcB32;
			result(0, 3) = SrcA00 * SrcB03 + SrcA01 * SrcB13 + SrcA02 * SrcB23 + SrcA03 * SrcB33;

			result(1, 0) = SrcA10 * SrcB00 + SrcA11 * SrcB10 + SrcA12 * SrcB20 + SrcA13 * SrcB30;
			result(1, 1) = SrcA10 * SrcB01 + SrcA11 * SrcB11 + SrcA12 * SrcB21 + SrcA13 * SrcB31;
			result(1, 2) = SrcA10 * SrcB02 + SrcA11 * SrcB12 + SrcA12 * SrcB22 + SrcA13 * SrcB32;
			result(1, 3) = SrcA10 * SrcB03 + SrcA11 * SrcB13 + SrcA12 * SrcB23 + SrcA13 * SrcB33;

			result(2, 0) = SrcA20 * SrcB00 + SrcA21 * SrcB10 + SrcA22 * SrcB20 + SrcA23 * SrcB30;
			result(2, 1) = SrcA20 * SrcB01 + SrcA21 * SrcB11 + SrcA22 * SrcB21 + SrcA23 * SrcB31;
			result(2, 2) = SrcA20 * SrcB02 + SrcA21 * SrcB12 + SrcA22 * SrcB22 + SrcA23 * SrcB32;
			result(2, 3) = SrcA20 * SrcB03 + SrcA21 * SrcB13 + SrcA22 * SrcB23 + SrcA23 * SrcB33;

			result(3, 0) = SrcA30 * SrcB00 + SrcA31 * SrcB10 + SrcA32 * SrcB20 + SrcA33 * SrcB30;
			result(3, 1) = SrcA30 * SrcB01 + SrcA31 * SrcB11 + SrcA32 * SrcB21 + SrcA33 * SrcB31;
			result(3, 2) = SrcA30 * SrcB02 + SrcA31 * SrcB12 + SrcA32 * SrcB22 + SrcA33 * SrcB32;
			result(3, 3) = SrcA30 * SrcB03 + SrcA31 * SrcB13 + SrcA32 * SrcB23 + SrcA33 * SrcB33;
			return result;
		}

		Matrix4 operator/(const Matrix4& mat) const {
			Matrix4 result;
			result = (*this) * mat.inverse();
			return result;
		}

		Matrix4& operator+=(const Matrix4& mat) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] += mat._d[i];
			}
			return *this;
		}

		Matrix4& operator-=(const Matrix4& mat) {
			for (int i = 0; i < this->length(); i++) {
				_d[i] -= mat._d[i];
			}
			return *this;
		}

		Matrix4& operator*=(const Matrix4& mat) {
			return (*this = *this * mat);
		}

		Matrix4& operator/=(const Matrix4& mat) {
			return *this *= mat.inverse();
		}

		Matrix4 transpose() const {
			Matrix4 result;
			result(0,0) = (*this)(0,0);
			result(0,1) = (*this)(1,0);
			result(0,2) = (*this)(2,0);
			result(0,3) = (*this)(3,0);

			result(1,0) = (*this)(0,1);
			result(1,1) = (*this)(1,1);
			result(1,2) = (*this)(2,1);
			result(1,3) = (*this)(3,1);

			result(2,0) = (*this)(0,2);
			result(2,1) = (*this)(1,2);
			result(2,2) = (*this)(2,2);
			result(2,3) = (*this)(3,2);

			result(3,0) = (*this)(0,3);
			result(3,1) = (*this)(1,3);
			result(3,2) = (*this)(2,3);
			result(3,3) = (*this)(3,3);
			return result;
		}

		float determinant() const {
			const Matrix4& m = *this;
			float SubFactor00 = m(2,2) * m(3,3) - m(3,2) * m(2,3);
			float SubFactor01 = m(2,1) * m(3,3) - m(3,1) * m(2,3);
			float SubFactor02 = m(2,1) * m(3,2) - m(3,1) * m(2,2);
			float SubFactor03 = m(2,0) * m(3,3) - m(3,0) * m(2,3);
			float SubFactor04 = m(2,0) * m(3,2) - m(3,0) * m(2,2);
			float SubFactor05 = m(2,0) * m(3,1) - m(3,0) * m(2,1);

			Vector4 DetCof(
				+(m(1,1) * SubFactor00 - m(1,2) * SubFactor01 + m(1,3) * SubFactor02),
				-(m(1,0) * SubFactor00 - m(1,2) * SubFactor03 + m(1,3) * SubFactor04),
				+(m(1,0) * SubFactor01 - m(1,1) * SubFactor03 + m(1,3) * SubFactor05),
				-(m(1,0) * SubFactor02 - m(1,1) * SubFactor04 + m(1,2) * SubFactor05));

			return
				m(0,0) * DetCof.d[0] + m(0,1) * DetCof.d[1] +
				m(0,2) * DetCof.d[2] + m(0,3) * DetCof.d[3];
		}

		Matrix4 inverse() const {
			const Matrix4& m = *this;
			float Coef00 = m(2,2) * m(3,3) - m(3,2) * m(2,3);
			float Coef02 = m(1,2) * m(3,3) - m(3,2) * m(1,3);
			float Coef03 = m(1,2) * m(2,3) - m(2,2) * m(1,3);

			float Coef04 = m(2,1) * m(3,3) - m(3,1) * m(2,3);
			float Coef06 = m(1,1) * m(3,3) - m(3,1) * m(1,3);
			float Coef07 = m(1,1) * m(2,3) - m(2,1) * m(1,3);

			float Coef08 = m(2,1) * m(3,2) - m(3,1) * m(2,2);
			float Coef10 = m(1,1) * m(3,2) - m(3,1) * m(1,2);
			float Coef11 = m(1,1) * m(2,2) - m(2,1) * m(1,2);

			float Coef12 = m(2,0) * m(3,3) - m(3,0) * m(2,3);
			float Coef14 = m(1,0) * m(3,3) - m(3,0) * m(1,3);
			float Coef15 = m(1,0) * m(2,3) - m(2,0) * m(1,3);

			float Coef16 = m(2,0) * m(3,2) - m(3,0) * m(2,2);
			float Coef18 = m(1,0) * m(3,2) - m(3,0) * m(1,2);
			float Coef19 = m(1,0) * m(2,2) - m(2,0) * m(1,2);

			float Coef20 = m(2,0) * m(3,1) - m(3,0) * m(2,1);
			float Coef22 = m(1,0) * m(3,1) - m(3,0) * m(1,1);
			float Coef23 = m(1,0) * m(2,1) - m(2,0) * m(1,1);

			Vector4 Fac0(Coef00, Coef00, Coef02, Coef03);
			Vector4 Fac1(Coef04, Coef04, Coef06, Coef07);
			Vector4 Fac2(Coef08, Coef08, Coef10, Coef11);
			Vector4 Fac3(Coef12, Coef12, Coef14, Coef15);
			Vector4 Fac4(Coef16, Coef16, Coef18, Coef19);
			Vector4 Fac5(Coef20, Coef20, Coef22, Coef23);

			Vector4 Vec0(m(1,0), m(0,0), m(0,0), m(0,0));
			Vector4 Vec1(m(1,1), m(0,1), m(0,1), m(0,1));
			Vector4 Vec2(m(1,2), m(0,2), m(0,2), m(0,2));
			Vector4 Vec3(m(1,3), m(0,3), m(0,3), m(0,3));

			Vector4 Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
			Vector4 Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
			Vector4 Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
			Vector4 Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

			Vector4 SignA(+1, -1, +1, -1);
			Vector4 SignB(-1, +1, -1, +1);
			Matrix4 Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

			float OneOverDeterminant = 1.0f / m.determinant();

			return Inverse * OneOverDeterminant;
		}

		static Matrix4 zero() {
			return Matrix4(
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0
			);
		}
		static Matrix4 one() {
			return Matrix4(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
			);
		}

		std::string toString() const {
			std::stringstream str;
			str << "Matrix4: \n" <<
				"[" << _d[0] << "; " << _d[1] << "; " << _d[2] << "; " << _d[3] << " ]\n" <<
				"[" << _d[4] << "; " << _d[5] << "; " << _d[6] << "; " << _d[7] << " ]\n" <<
				"[" << _d[8] << "; " << _d[9] << "; " << _d[10] << "; " << _d[11] << " ]\n" <<
				"[" << _d[12] << "; " << _d[13] << "; " << _d[14] << "; " << _d[15] << " ]";
			return str.str();
		}
	private:
		float _d[16];
	};

	inline std::ostream& operator<<(std::ostream& os, const Matrix4& mat)
	{
		os << mat.toString();
		return os;
	}
}