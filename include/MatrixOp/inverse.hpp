#ifndef _MATRIXOP_INVERSE_HPP
#define _MATRIXOP_INVERSE_HPP

/*  
 *  matrixop::inverse(A)  matrixop::inv(A)
 *
 *  function for inverseersing a matrix A
 *
 *
 * 	param   A:  matrix A (N*N)
 *
 *  return  A^-1
 *
 ****************************************
 *
 *  matrixop::inverse_inplace(A)  martixop::inv_inplace(A)
 *
 *  function for inverseersing a matrix A inplace
 *
 *
 * 	param   A:  matrix A (N*N)
 * 	            on exit, A is A^-1
 *
 */


#include <vector>
#include <cmath>
#include "matrixop_config.hpp"

namespace matrixop {
	using std::sqrt;
	using std::copy;
	using std::vector;

    // single
    VOID _inverse(STYPE* A, CNST_ITYPE N) 
    {
        MATRIXOP_STATIC vector<ITYPE> ipiv;
        MATRIXOP_STATIC vector<STYPE> work;

        ITYPE info(-1), lwork(-1);

        ipiv.resize(N);
        SGETRF(&N, &N, A, &N, &ipiv[0], &info);

        work.resize(1);
        SGETRI(&N, A, &N, &ipiv[0], &work[0], &lwork, &info);

        lwork = static_cast<ITYPE>(work[0]);
        work.resize(lwork);
        SGETRI(&N, A, &N, &ipiv[0], &work[0], &lwork, &info);
    }

    // double
    VOID _inverse(DTYPE* A, CNST_ITYPE N) 
    {
        MATRIXOP_STATIC vector<ITYPE> ipiv;
        MATRIXOP_STATIC vector<DTYPE> work;

        ITYPE info(-1), lwork(-1);

        ipiv.resize(N);
        DGETRF(&N, &N, A, &N, &ipiv[0], &info);

        work.resize(1);
        DGETRI(&N, A, &N, &ipiv[0], &work[0], &lwork, &info);

        lwork = static_cast<ITYPE>(work[0]);
        work.resize(lwork);
        DGETRI(&N, A, &N, &ipiv[0], &work[0], &lwork, &info);
    }

    // complex
    VOID _inverse(CTYPE* A, CNST_ITYPE N) 
    {
        MATRIXOP_STATIC vector<ITYPE> ipiv;
        MATRIXOP_STATIC vector<CTYPE> work;

        ITYPE info(-1), lwork(-1);

        ipiv.resize(N);
        CGETRF(&N, &N, A, &N, &ipiv[0], &info);

        work.resize(1);
        CGETRI(&N, A, &N, &ipiv[0], &work[0], &lwork, &info);

        lwork = static_cast<ITYPE>(work[0].real());
        work.resize(lwork);
        CGETRI(&N, A, &N, &ipiv[0], &work[0], &lwork, &info);
    }

    // complex*16
    VOID _inverse(ZTYPE* A, CNST_ITYPE N) 
    {
        MATRIXOP_STATIC vector<ITYPE> ipiv;
        MATRIXOP_STATIC vector<ZTYPE> work;

        ITYPE info(-1), lwork(-1);

        ipiv.resize(N);
        ZGETRF(&N, &N, A, &N, &ipiv[0], &info);

        work.resize(1);
        ZGETRI(&N, A, &N, &ipiv[0], &work[0], &lwork, &info);

        lwork = static_cast<ITYPE>(work[0].real());
        work.resize(lwork);
        ZGETRI(&N, A, &N, &ipiv[0], &work[0], &lwork, &info);
    }

    // interfaces
    template <typename T>
        inline vector<T> inverse(const vector<T>& A)
        {
            MATRIXOP_STATIC vector<T> rst;
            rst.assign(A.begin(), A.end());
            _inverse(&rst[0], static_cast<ITYPE>(sqrt(rst.size())));
            return rst;
        }

    template <typename T>
        inline vector<T> inv(const vector<T>& A)
        {
            return inverse(A);
        }


    template <typename T>
        inline VOID inverse_inplace(vector<T>& A)
        {
            _inverse(&A[0], static_cast<ITYPE>(sqrt(A.size())));
        }

    template <typename T>
        inline VOID inv_inplace(vector<T>& A)
        {
            inverse_inplace(A);
        }
};

#endif // _MATRIXOP_INVERSE_HPP
