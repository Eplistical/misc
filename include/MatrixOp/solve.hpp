#ifndef _MATRIXOP_SOLVE_HPP
#define _MATRIXOP_SOLVE_HPP

/*  
 *  matrixop::solve(A, B, [NHRS]) 
 *
 *  function for solving AX = B
 *
 * 	param      A:  matrix A (N * N)
 * 	param      B:  matrix B (N * NHRS)
 * 	param   NHRS:  number of columns in B, default NHRS = 1
 *
 * 	return vector X
 *
 ****************************************
 *   
 *  matrixop::solve_inplace(A, B, [NHRS]) 
 *
 *  function for inplace solving AX = B
 *
 * 	param      A:  matrix A (N * N)
 * 	param      B:  matrix B (N * NHRS)
 * 	                on exit, B is X
 * 	param   NHRS:  number of columns in B, default NHRS = 1
 */


#include <vector>
#include <cmath>
#include <algorithm>
#include "matrixop_config.hpp"

namespace matrixop {
	using std::sqrt;
	using std::copy;
	using std::vector;

    // single
    VOID _solve(STYPE* A, STYPE* B, CNST_ITYPE N, CNST_ITYPE NHRS)
    {
        MATRIXOP_STATIC vector<ITYPE> ipiv;

        ITYPE info(-1);
        ipiv.resize(N);
        SGESV(&N, &NHRS, A, &N, &ipiv[0], B, &N, &info);
    }
    // double
    VOID _solve(DTYPE* A, DTYPE* B, CNST_ITYPE N, CNST_ITYPE NHRS)
    {
        MATRIXOP_STATIC vector<ITYPE> ipiv;

        ITYPE info(-1);
        ipiv.resize(N);
        DGESV(&N, &NHRS, A, &N, &ipiv[0], B, &N, &info);
    }
    // complex
    VOID _solve(CTYPE* A, CTYPE* B, CNST_ITYPE N, CNST_ITYPE NHRS)
    {
        MATRIXOP_STATIC vector<ITYPE> ipiv;

        ITYPE info(-1);
        ipiv.resize(N);
        CGESV(&N, &NHRS, A, &N, &ipiv[0], B, &N, &info);
    }
    // complex*16
    VOID _solve(ZTYPE* A, ZTYPE* B, CNST_ITYPE N, CNST_ITYPE NHRS)
    {
        MATRIXOP_STATIC vector<ITYPE> ipiv;

        ITYPE info(-1);
        ipiv.resize(N);
        ZGESV(&N, &NHRS, A, &N, &ipiv[0], B, &N, &info);
    }

    // interfaces
    template <typename T>
        vector<T> solve(const vector<T>& A, const vector<T>& B, CNST_ITYPE NHRS = 1) 
        {
            CNST_ITYPE N(static_cast<ITYPE>(B.size() / NHRS));
            vector<T> Mat(A), X(B);
            _solve(&Mat[0], &X[0], N, NHRS);
            return X;
        }

    template <typename T>
        VOID solve_inplace(const vector<T>& A, vector<T>& B, CNST_ITYPE NHRS = 1) 
        {
            CNST_ITYPE N(static_cast<ITYPE>(B.size() / NHRS));
            vector<T> Mat(A);
            _solve(&Mat[0], &B[0], N, NHRS);
        }
};

#endif // _MATRIXOP_SOLVE_HPP
