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
	vector<STYPE> matmat_(const vector<STYPE>& A, const vector<STYPE>& B, CNST_ITYPE K)
	{
        CNST_ITYPE M(static_cast<ITYPE>(A.size() / K));
        CNST_ITYPE N(static_cast<ITYPE>(B.size() / K));
		vector<STYPE> rst(N * M);

        SGEMM(&CHARN, &CHARN, &M, &N, &K, &ONES, 
                &A[0], &M, &B[0], &K, 
                &ZEROS, &rst[0], &M);
		return rst;
	}

    // double
	vector<DTYPE> matmat_(const vector<DTYPE>& A, const vector<DTYPE>& B, CNST_ITYPE K)
	{
        CNST_ITYPE M(static_cast<ITYPE>(A.size() / K));
        CNST_ITYPE N(static_cast<ITYPE>(B.size() / K));
		vector<DTYPE> rst(N * M);

        DGEMM(&CHARN, &CHARN, &M, &N, &K, &ONED, 
                &A[0], &M, &B[0], &K, 
                &ZEROD, &rst[0], &M);
		return rst;
	}

    // complex
	vector<CTYPE> matmat_(const vector<CTYPE>& A, const vector<CTYPE>& B, CNST_ITYPE K)
	{
        CNST_ITYPE M(static_cast<ITYPE>(A.size() / K));
        CNST_ITYPE N(static_cast<ITYPE>(B.size() / K));
		vector<CTYPE> rst(N * M);

        CGEMM(&CHARN, &CHARN, &M, &N, &K, &ONEC, 
                &A[0], &M, &B[0], &K, 
                &ZEROC, &rst[0], &M);
		return rst;
	}

    // complex*16
	vector<ZTYPE> matmat_(const vector<ZTYPE>& A, const vector<ZTYPE>& B, CNST_ITYPE K)
	{
        CNST_ITYPE M(static_cast<ITYPE>(A.size() / K));
        CNST_ITYPE N(static_cast<ITYPE>(B.size() / K));
		vector<ZTYPE> rst(N * M);

        ZGEMM(&CHARN, &CHARN, &M, &N, &K, &ONEZ, 
                &A[0], &M, &B[0], &K, 
                &ZEROZ, &rst[0], &M);
		return rst;
	}

    // interfaces
    template<typename T>
        vector<T> matmat(const vector<T>& A, const vector<T>& B, CNST_ITYPE K) {
            return matmat_(A, B, K);
        }
};

#endif // _MATRIXOP_MATMAT_HPP
