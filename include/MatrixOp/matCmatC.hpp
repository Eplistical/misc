#ifndef _MATRIXOP_MATCMATC_HPP
#define _MATRIXOP_MATCMATC_HPP

/*  
 *  matrixop::matCmatC(A, B, K)
 *
 *  function for matrix-matrix multiplication
 *
 * 	param   A:  matrix A (K*M)
 * 	param   B:  matrix B (N*K)
 * 	param   K:  matrix dimensions
 *
 * 	return A' * B'
 *
 */


#include <vector>
#include "matrixop_config.hpp"

namespace matrixop {
	using std::vector;

    // single
	inline VOID _matCmatC(CNST_STYPE* A, CNST_STYPE* B, CNST_ITYPE M, CNST_ITYPE K, CNST_ITYPE N, STYPE* rst)
	{
        SGEMM(&CHARC, &CHARC, &M, &N, &K, &ONES, 
                A, &K, B, &N, 
                &ZEROS, rst, &M);
	}

    // double
	inline VOID _matCmatC(CNST_DTYPE* A, CNST_DTYPE* B, CNST_ITYPE M, CNST_ITYPE K, CNST_ITYPE N, DTYPE* rst)
	{
        DGEMM(&CHARC, &CHARC, &M, &N, &K, &ONED, 
                A, &K, B, &N, 
                &ZEROD, rst, &M);
	}

    // complex
	inline VOID _matCmatC(CNST_CTYPE* A, CNST_CTYPE* B, CNST_ITYPE M, CNST_ITYPE K, CNST_ITYPE N, CTYPE* rst)
	{
        CGEMM(&CHARC, &CHARC, &M, &N, &K, &ONEC, 
                A, &K, B, &N, 
                &ZEROC, rst, &M);
	}

    // complex*16
	inline VOID _matCmatC(CNST_ZTYPE* A, CNST_ZTYPE* B, CNST_ITYPE M, CNST_ITYPE K, CNST_ITYPE N, ZTYPE* rst)
	{
        ZGEMM(&CHARC, &CHARC, &M, &N, &K, &ONEZ, 
                A, &K, B, &N, 
                &ZEROZ, rst, &M);
	}

    // interfaces
    template<typename T>
        vector<T> matCmatC(const vector<T>& A, const vector<T>& B, CNST_ITYPE K) {
            CNST_ITYPE M(static_cast<ITYPE>(A.size() / K));
            CNST_ITYPE N(static_cast<ITYPE>(B.size() / K));
            vector<T> rst(N * M);
            _matCmatC(&A[0], &B[0], M, K, N, &rst[0]);
            return rst;
        }
};

#endif // _MATRIXOP_MATCMATC_HPP
