#ifndef _MATRIXOP_MATMAT_HPP
#define _MATRIXOP_MATMAT_HPP

/*  
 *  matrixop::matmat(A, B, K)
 *
 *  function for matrix-matrix multiplication
 *
 * 	param   A:  matrix A (M*K)
 * 	param   B:  matrix B (K*N)
 * 	param   K:  matrix dimensions
 *
 * 	return A * B
 *
 */


#include <vector>
#include "matrixop_config.hpp"

namespace matrixop {
	using std::vector;

    // single
	inline VOID _matmat(CNST_STYPE* A, CNST_STYPE* B, CNST_ITYPE M, CNST_ITYPE K, CNST_ITYPE N, STYPE* rst)
	{
        SGEMM(&CHARN, &CHARN, &M, &N, &K, &ONES, 
                A, &M, B, &K, 
                &ZEROS, rst, &M);
	}

    // double
	inline VOID _matmat(CNST_DTYPE* A, CNST_DTYPE* B, CNST_ITYPE M, CNST_ITYPE K, CNST_ITYPE N, DTYPE* rst)
	{
        DGEMM(&CHARN, &CHARN, &M, &N, &K, &ONED, 
                A, &M, B, &K, 
                &ZEROD, rst, &M);
	}

    // complex
	inline VOID _matmat(CNST_CTYPE* A, CNST_CTYPE* B, CNST_ITYPE M, CNST_ITYPE K, CNST_ITYPE N, CTYPE* rst)
	{
        CGEMM(&CHARN, &CHARN, &M, &N, &K, &ONEC, 
                A, &M, B, &K, 
                &ZEROC, rst, &M);
	}

    // complex*16
	inline VOID _matmat(CNST_ZTYPE* A, CNST_ZTYPE* B, CNST_ITYPE M, CNST_ITYPE K, CNST_ITYPE N, ZTYPE* rst)
	{
        ZGEMM(&CHARN, &CHARN, &M, &N, &K, &ONEZ, 
                A, &M, B, &K, 
                &ZEROZ, rst, &M);
	}

    // interfaces
    template<typename T>
        vector<T> matmat(const vector<T>& A, const vector<T>& B, CNST_ITYPE K) {
            CNST_ITYPE M(static_cast<ITYPE>(A.size() / K));
            CNST_ITYPE N(static_cast<ITYPE>(B.size() / K));
            vector<T> rst(N * M);
            _matmat(&A[0], &B[0], M, K, N, &rst[0]);
            return rst;
        }
};

#endif // _MATRIXOP_MATMAT_HPP
