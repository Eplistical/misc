#ifndef _MATRIXOP_INV_HPP
#define _MATRIXOP_INV_HPP

/*  
 *  matrixop::inv(A)
 *
 *  function for inversing a matrix A
 *
 *
 * 	param   A:  matrix A (N*N)
 *
 *  return  A^-1
 *
 ****************************************
 *
 *  matrixop::inv_inplace(A)
 *
 *  function for inversing a matrix A inplace
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
    VOID _inv(STYPE* A, CNST_ITYPE N) 
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
    VOID _inv(DTYPE* A, CNST_ITYPE N) 
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
    VOID _inv(CTYPE* A, CNST_ITYPE N) 
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
    VOID _inv(ZTYPE* A, CNST_ITYPE N) 
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
        inline vector<T> inv(const vector<T>& A)
        {
            vector<T> rst(A);
            _inv(&rst[0], static_cast<ITYPE>(sqrt(A.size())));
            return rst;
        }

    template <typename T>
        inline VOID inv_inplace(vector<T>& A)
        {
            _inv(&A[0], static_cast<ITYPE>(sqrt(A.size())));
        }

};

#endif // _MATRIXOP_INV_HPP
