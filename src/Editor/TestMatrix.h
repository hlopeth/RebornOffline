#include "Math/Matrix.h"

namespace Reborn {
    void testMatrix2() {
#if 0
        {
            LOG_DEBUG << "Matrix2::zero = " << Matrix2::zero();
            LOG_DEBUG << "Matrix2::one = " << Matrix2::one();

            Matrix2 matA(1, 2, 3, 4);
            Matrix2 matB(4, 3, 2, 1);

            LOG_DEBUG << "matA = " << matA;
            LOG_DEBUG << "determinant = " << matA.determinant();
            LOG_DEBUG << "transpose = " << matA.transpose();
            LOG_DEBUG << "inverce = " << matA.inverce();
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

	void testMatrix() {
#if 1
        testMatrix2();
#endif
	}
}