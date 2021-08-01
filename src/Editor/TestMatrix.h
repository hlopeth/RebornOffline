#include "Math/Matrix.h"

namespace Reborn {
    void testMatrix2() {
#if 0 //fast test
        {
            LOG_DEBUG << "Matrix2::zero = " << Matrix2::zero();
            LOG_DEBUG << "Matrix2::one = " << Matrix2::one();

            Matrix2 matA(1, 2, 3, 4);
            Matrix2 matB(4, 3, 2, 1);

            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "determinant = " << matA.determinant();
            LOG_DEBUG << "transpose = " << matA.transpose();
            LOG_DEBUG << "inverce = " << matA.inverse();
        }
#endif

#if 0
        {
            Matrix2 m(1, 2, 3, 4);
            float scalar = 5;
            LOG_DEBUG << "m = " << m;
            LOG_DEBUG << "scalar = " << scalar;
            m += scalar;
            LOG_DEBUG << "m + scalar = " << m << std::endl;
        }
        {
            Matrix2 m(1, 2, 3, 4);
            float scalar = 5;
            LOG_DEBUG << "m = " << m;
            LOG_DEBUG << "scalar = " << scalar;
            m -= scalar;
            LOG_DEBUG << "m - scalar = " << m << std::endl;
        }
        {
            Matrix2 m(1, 2, 3, 4);
            float scalar = 5;
            LOG_DEBUG << "m = " << m;
            LOG_DEBUG << "scalar = " << scalar;
            m *= scalar;
            LOG_DEBUG << "m * scalar = " << m << std::endl;
        }
        {
            Matrix2 m(1, 2, 3, 4);
            float scalar = 5;
            LOG_DEBUG << "m = " << m;
            LOG_DEBUG << "scalar = " << scalar;
            m /= scalar;
            LOG_DEBUG << "m / scalar = " << m << std::endl;
        }
        {
            Matrix2 matA(1, 2, 3, 4);
            Matrix2 matB(4, 3, 2, 1);
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            matA += matB;
            LOG_DEBUG << "matA + matB = " << matA << std::endl;
        }
        {
            Matrix2 matA(1, 2, 3, 4);
            Matrix2 matB(4, 3, 2, 1);
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            matA -= matB;
            LOG_DEBUG << "matA - matB = " << matA << std::endl;
        }
        {
            Matrix2 matA(1, 2, 3, 4);
            Matrix2 matB(4, 3, 2, 1);
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            matA *= matB;
            LOG_DEBUG << "matA * matB = " << matA << std::endl;
        }
        {
            Matrix2 matA(1, 2, 3, 4);
            Matrix2 matB(4, 3, 2, 1);
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            matA /= matB;
            LOG_DEBUG << "matA / matB = " << matA << std::endl;
        }
#endif

#if 1 
        {
            const Matrix2 m(1, 2, 3, 4);
            const float scalar = 5;
            LOG_DEBUG << "m = " << m;
            LOG_DEBUG << "scalar = " << scalar;
            LOG_DEBUG << "m + scalar = " << m + scalar << std::endl;
        }
        {
            const Matrix2 m(1, 2, 3, 4);
            const float scalar = 5;
            LOG_DEBUG << "m = " << m;
            LOG_DEBUG << "scalar = " << scalar;
            LOG_DEBUG << "m - scalar = " << m - scalar << std::endl;
        }
        {
            const Matrix2 m(1, 2, 3, 4);
            const float scalar = 5;
            LOG_DEBUG << "m = " << m;
            LOG_DEBUG << "scalar = " << scalar;
            LOG_DEBUG << "m * scalar = " << m * scalar << std::endl;
        }
        {
            const Matrix2 m(1, 2, 3, 4);
            const float scalar = 5;
            LOG_DEBUG << "m = " << m;
            LOG_DEBUG << "scalar = " << scalar;
            LOG_DEBUG << "m / scalar = " << m / scalar << std::endl;
        }
        {
            const Matrix2 matA(1, 2, 3, 4);
            const Matrix2 matB(4, 3, 2, 1);
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            LOG_DEBUG << "matA + matB = " << matA + matB << std::endl;
        }
        {
            const Matrix2 matA(1, 2, 3, 4);
            const Matrix2 matB(4, 3, 2, 1);
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            LOG_DEBUG << "matA - matB = " << matA - matB << std::endl;
        }
        {
            const Matrix2 matA(1, 2, 3, 4);
            const Matrix2 matB(4, 3, 2, 1);
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            LOG_DEBUG << "matA * matB = " << matA * matB << std::endl;
        }
        {
            const Matrix2 matA(1, 2, 3, 4);
            const Matrix2 matB(4, 3, 2, 1);
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            LOG_DEBUG << "matA / matB = " << matA / matB << std::endl;
        }
#endif
    }

    void testMatrix4() {
#if 0 //fast test
        {
            LOG_DEBUG << "Matrix4::zero = " << Matrix4::zero();
            LOG_DEBUG << "Matrix4::one = " << Matrix4::one();

            Matrix4 matA(
                1, 2, 3, 423,
                5, 126, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );
            Matrix4 matB(
                11, 5, 9, 13,
                2, -126, 10, 14,
                3, 7, 11, 15,
                423, 8, 12, 16
            );

            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "determinant = " << matA.determinant();
            LOG_DEBUG << "transpose = " << matA.transpose();
            LOG_DEBUG << "inverce = " << matA.inverse();
            LOG_DEBUG << "A * B = " << matA * matB;
        }
#endif

#if 0
        {
            Matrix4 m(
                1, 2, 3, 423,
                5, 126, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );
            const float scalar = 5;
            LOG_DEBUG << "m = " << m;
            LOG_DEBUG << "scalar = " << scalar;
            LOG_DEBUG << "m + scalar = " << m + scalar << std::endl;
        }
        {
            Matrix4 m(
                1, 2, 3, 423,
                5, 126, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );
            const float scalar = 5;
            LOG_DEBUG << "m = " << m;
            LOG_DEBUG << "scalar = " << scalar;
            LOG_DEBUG << "m - scalar = " << m - scalar << std::endl;
        }
        {
            Matrix4 m(
                1, 2, 3, 423,
                5, 126, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );
            const float scalar = 5;
            LOG_DEBUG << "m = " << m;
            LOG_DEBUG << "scalar = " << scalar;
            LOG_DEBUG << "m * scalar = " << m * scalar << std::endl;
        }
        {
            Matrix4 m(
                1, 2, 3, 423,
                5, 126, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );
            const float scalar = 5;
            LOG_DEBUG << "m = " << m;
            LOG_DEBUG << "scalar = " << scalar;
            LOG_DEBUG << "m / scalar = " << m / scalar << std::endl;
        } 
        {
            Matrix4 matA(
                1, 2, 3, 423,
                5, 126, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );
            Matrix4 matB(
                11, 5, 9, 13,
                2, -126, 10, 14,
                3, 7, 11, 15,
                423, 8, 12, 16
            );
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            matA += matB;
            LOG_DEBUG << "matA + matB = " << matA << std::endl;
        } 
        {
            Matrix4 matA(
                1, 2, 3, 423,
                5, 126, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );
            Matrix4 matB(
                11, 5, 9, 13,
                2, -126, 10, 14,
                3, 7, 11, 15,
                423, 8, 12, 16
            );
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            matA -= matB;
            LOG_DEBUG << "matA - matB = " << matA << std::endl;
        } 
        {
            Matrix4 matA(
                1, 2, 3, 423,
                5, 126, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );
            Matrix4 matB(
                11, 5, 9, 13,
                2, -126, 10, 14,
                3, 7, 11, 15,
                423, 8, 12, 16
            );
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            matA *= matB;
            LOG_DEBUG << "matA * matB = " << matA << std::endl;
        }
        {
            Matrix4 matA(
                1, 2, 3, 423,
                5, 126, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );
            Matrix4 matB(
                11, 5, 9, 13,
                2, -126, 10, 14,
                3, 7, 11, 15,
                423, 8, 12, 16
            );
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            matA /= matB;
            LOG_DEBUG << "matA / matB = " << matA << std::endl;
        }
#endif

#if 1
        {
            Matrix4 matA(
                1, 2, 3, 423,
                5, 126, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );
            Matrix4 matB(
                11, 5, 9, 13,
                2, -126, 10, 14,
                3, 7, 11, 15,
                423, 8, 12, 16
            );
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            LOG_DEBUG << "matA + matB = " << matA + matB << std::endl;
        }
        {
            Matrix4 matA(
                1, 2, 3, 423,
                5, 126, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );
            Matrix4 matB(
                11, 5, 9, 13,
                2, -126, 10, 14,
                3, 7, 11, 15,
                423, 8, 12, 16
            );
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            LOG_DEBUG << "matA - matB = " << matA - matB << std::endl;
        }
        {
            Matrix4 matA(
                1, 2, 3, 423,
                5, 126, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );
            Matrix4 matB(
                11, 5, 9, 13,
                2, -126, 10, 14,
                3, 7, 11, 15,
                423, 8, 12, 16
            );
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            LOG_DEBUG << "matA * matB = " << matA * matB << std::endl;
        }
        {
            Matrix4 matA(
                1, 2, 3, 423,
                5, 126, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            );
            Matrix4 matB(
                11, 5, 9, 13,
                2, -126, 10, 14,
                3, 7, 11, 15,
                423, 8, 12, 16
            );
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            LOG_DEBUG << "matA / matB = " << matA / matB << std::endl;
        }
#endif 
    }

    void testMatrix3() {
#if 0 //fast test
        {
            LOG_DEBUG << "Matrix3::zero = " << Matrix3::zero();
            LOG_DEBUG << "Matrix3::one = " << Matrix3::one();

            Matrix3 matA(
                2, 2, 3, 
                4, 5, 6,
                7, 8, 9
            );
            Matrix3 matB(
                9, 8, 7,
                6, 5, 4,
                3, 2, 2
            );

            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "determinant = " << matA.determinant();
            LOG_DEBUG << "transpose = " << matA.transpose();
            LOG_DEBUG << "inverce = " << matA.inverse();
            LOG_DEBUG << "A * B = " << matA * matB;
        }
#endif

#if 1
        {
            const Matrix3 m(
                2, 2, 3,
                4, 5, 6,
                7, 8, 9
            );
            const float scalar = 5;
            LOG_DEBUG << "m = " << m;
            LOG_DEBUG << "scalar = " << scalar;
            LOG_DEBUG << "m + scalar = " << m + scalar << std::endl;
        }
        {
            const Matrix3 m(
                2, 2, 3,
                4, 5, 6,
                7, 8, 9
            );
            const float scalar = 5;
            LOG_DEBUG << "m = " << m;
            LOG_DEBUG << "scalar = " << scalar;
            LOG_DEBUG << "m - scalar = " << m - scalar << std::endl;
        }
        {
            const Matrix3 m(
                2, 2, 3,
                4, 5, 6,
                7, 8, 9
            );
            const float scalar = 5;
            LOG_DEBUG << "m = " << m;
            LOG_DEBUG << "scalar = " << scalar;
            LOG_DEBUG << "m * scalar = " << m * scalar << std::endl;
        }
        {
            const Matrix3 m(
                2, 2, 3,
                4, 5, 6,
                7, 8, 9
            );
            const float scalar = 5;
            LOG_DEBUG << "m = " << m;
            LOG_DEBUG << "scalar = " << scalar;
            LOG_DEBUG << "m / scalar = " << m / scalar << std::endl;
        } 
        {
            Matrix3 matA(
                2, 2, 3,
                4, 5, 6,
                7, 8, 9
            );
            Matrix3 matB(
                9, 8, 7,
                6, 5, 4,
                3, 2, 2
            );
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            matA += matB;
            LOG_DEBUG << "matA + matB = " << matA << std::endl;
        } 
        {
            Matrix3 matA(
                2, 2, 3,
                4, 5, 6,
                7, 8, 9
            );
            Matrix3 matB(
                9, 8, 7,
                6, 5, 4,
                3, 2, 2
            );
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            matA -= matB;
            LOG_DEBUG << "matA - matB = " << matA << std::endl;
        } 
        {
            Matrix3 matA(
                2, 2, 3,
                4, 5, 6,
                7, 8, 9
            );
            Matrix3 matB(
                9, 8, 7,
                6, 5, 4,
                3, 2, 2
            );
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            matA *= matB;
            LOG_DEBUG << "matA * matB = " << matA << std::endl;
        }
        {
            Matrix3 matA(
                2, 2, 3,
                4, 5, 6,
                7, 8, 9
            );
            Matrix3 matB(
                9, 8, 7,
                6, 5, 4,
                3, 2, 2
            );
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            matA /= matB;
            LOG_DEBUG << "matA / matB = " << matA << std::endl;
        }
#endif

#if 0
        {
            const Matrix3 matA(
                2, 2, 3,
                4, 5, 6,
                7, 8, 9
            );
            const Matrix3 matB(
                9, 8, 7,
                6, 5, 4,
                3, 2, 2
            );
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            LOG_DEBUG << "matA + matB = " << matA + matB << std::endl;
        }
        {
            const Matrix3 matA(
                2, 2, 3,
                4, 5, 6,
                7, 8, 9
            );
            const Matrix3 matB(
                9, 8, 7,
                6, 5, 4,
                3, 2, 2
            );
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            LOG_DEBUG << "matA - matB = " << matA - matB << std::endl;
        }
        {
            const Matrix3 matA(
                2, 2, 3,
                4, 5, 6,
                7, 8, 9
            );
            const Matrix3 matB(
                9, 8, 7,
                6, 5, 4,
                3, 2, 2
            );
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            LOG_DEBUG << "matA * matB = " << matA * matB << std::endl;
        }
        {
            const Matrix3 matA(
                2, 2, 3,
                4, 5, 6,
                7, 8, 9
            );
            const Matrix3 matB(
                9, 8, 7,
                6, 5, 4,
                3, 2, 2
            );
            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "matB = " << matB;
            LOG_DEBUG << "matA / matB = " << matA / matB << std::endl;
        }
#endif 
    }

	void testMatrix() {
#if 0
        testMatrix2();
#endif
#if 0
        testMatrix3();
#endif
#if 1
        testMatrix4();
#endif
	}
}