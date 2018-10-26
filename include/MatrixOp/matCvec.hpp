#ifndef _MATRIXOP_MATCVEC_HPP
#define _MATRIXOP_MATCVEC_HPP

/*  
 *  matrixop::matCvec(A, V)
 *
 *  function for matrix-vector multiplication
 *
 * 	param   A:  matrix (N*M)
 * 	param   V:  vector (N)
 *
 * 	return  A' * v
 *
 */


#include <vector>
#include "matrixop_config.hpp"

namespace matrixop {
	using std::vector;

    // single
	inline VOID _matCvec(CNST_STYPE* A, CNST_STYPE* V, CNST_ITYPE M, CNST_ITYPE N, STYPE* rst)
	{
        SGEMV(&CHARC, &N, &M, &ONES, 
                A, &N, V, &ONEI,
                &ZEROS, rst, &ONEI);
	}

    // double
	inline VOID _matCvec(CNST_DTYPE* A, CNST_DTYPE* V, CNST_ITYPE M, CNST_ITYPE N, DTYPE* rst)
	{
        DGEMV(&CHARC, &N, &M, &ONED, 
                A, &N, V, &ONEI,
                &ZEROD, rst, &ONEI);
	}

    // complex
	inline VOID _matCvec(CNST_CTYPE* A, CNST_CTYPE* V, CNST_ITYPE M, CNST_ITYPE N, CTYPE* rst)
	{
        CGEMV(&CHARC, &N, &M, &ONEC, 
                A, &N, V, &ONEI,
                &ZEROC, rst, &ONEI);
	}

    // complex*16
	inline VOID _matCvec(CNST_ZTYPE* A, CNST_ZTYPE* V, CNST_ITYPE M, CNST_ITYPE N, ZTYPE* rst)
	{
        ZGEMV(&CHARC, &N, &M, &ONEZ, 
                A, &N, V, &ONEI,
                &ZEROZ, rst, &ONEI);
	}

    // interfaces
    template<typename T>
        vector<T> matCvec(const vector<T>& A, const vector<T>& V) {
            CNST_ITYPE N(static_cast<ITYPE>(V.size()));
            CNST_ITYPE M(static_cast<ITYPE>(A.size() / N));
            vector<T> rst(N);
            _matCvec(&A[0], &V[0], M, N, &rst[0]);
            return rst;
        }
};

#endif // _MATRIXOP_MATCVEC_HPP
