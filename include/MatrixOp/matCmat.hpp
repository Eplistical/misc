#ifndef _MATRIXOP_MATCMAT_HPP
#define _MATRIXOP_MATCMAT_HPP

/*  
 *  matrixop::matCmat(A, B, K)
 *
 *  function for matrix-matrix multiplication
 *
 * 	param   A:  matrix A (K*M)
 * 	param   B:  matrix B (K*N)
 * 	param   K:  matrix dimensions
 *
 * 	return A.H * B
 *
 */


#include <vector>
#include "matrixop_config.hpp"

namespace matrixop {
	using std::vector;

    // single
	vector<STYPE> matCmat_(const vector<STYPE>& A, const vector<STYPE>& B, CNST_ITYPE K)
	{
        CNST_ITYPE M(static_cast<ITYPE>(A.size() / K));
        CNST_ITYPE N(static_cast<ITYPE>(B.size() / K));
		vector<STYPE> rst(M * N);

        SGEMM(&CHARC, &CHARN, &M, &N, &K, &ONES, 
                &A[0], &K, &B[0], &K, 
                &ZEROS, &rst[0], &M);
		return rst;
	}

    // double
	vector<DTYPE> matCmat_(const vector<DTYPE>& A, const vector<DTYPE>& B, CNST_ITYPE K)
	{
        CNST_ITYPE M(static_cast<ITYPE>(A.size() / K));
        CNST_ITYPE N(static_cast<ITYPE>(B.size() / K));
		vector<DTYPE> rst(M * N);

        DGEMM(&CHARC, &CHARN, &M, &N, &K, &ONED, 
                &A[0], &K, &B[0], &K, 
                &ZEROD, &rst[0], &M);
		return rst;
	}

    // complex
	vector<CTYPE> matCmat_(const vector<CTYPE>& A, const vector<CTYPE>& B, CNST_ITYPE K)
	{
        CNST_ITYPE M(static_cast<ITYPE>(A.size() / K));
        CNST_ITYPE N(static_cast<ITYPE>(B.size() / K));
		vector<CTYPE> rst(M * N);

        CGEMM(&CHARC, &CHARN, &M, &N, &K, &ONEC, 
                &A[0], &K, &B[0], &K, 
                &ZEROC, &rst[0], &M);
		return rst;
	}

    // complex*16
	vector<ZTYPE> matCmat_(const vector<ZTYPE>& A, const vector<ZTYPE>& B, CNST_ITYPE K)
	{
        CNST_ITYPE M(static_cast<ITYPE>(A.size() / K));
        CNST_ITYPE N(static_cast<ITYPE>(B.size() / K));
		vector<ZTYPE> rst(M * N);

        ZGEMM(&CHARC, &CHARN, &M, &N, &K, &ONEZ, 
                &A[0], &K, &B[0], &K, 
                &ZEROZ, &rst[0], &M);
		return rst;
	}

    // interfaces
    template<typename T>
        vector<T> matCmat(const vector<T>& A, const vector<T>& B, CNST_ITYPE K) {
            return matCmat_(A, B, K);
        }
};

#endif // _MATRIXOP_MATCMAT_HPP
