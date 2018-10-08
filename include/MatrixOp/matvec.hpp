#ifndef _MATRIXOP_MATVEC_HPP
#define _MATRIXOP_MATVEC_HPP

/*  
 *  matrixop::matvec(A, V)
 *
 *  function for matrix-vector multiplication
 *
 * 	param   A:  matrix
 * 	param   V:  vector
 *
 */


#include <vector>
#include "matrixop_config.hpp"

namespace matrixop {
	using std::vector;

    // single
	vector<STYPE> matvec_(const vector<STYPE>& A, const vector<STYPE>& V)
	{
        CNST_ITYPE N(static_cast<ITYPE>(V.size()));
        CNST_ITYPE M(static_cast<ITYPE>(A.size() / N));
		vector<STYPE> rst(N);

        SGEMV(&CHARN, &M, &N, &ONES, 
                &A[0], &M, &V[0], &ONEI,
                &ZEROS, &rst[0], &ONEI);
		return rst;
	}

    // double
	vector<DTYPE> matvec_(const vector<DTYPE>& A, const vector<DTYPE>& V)
	{
        CNST_ITYPE N(static_cast<ITYPE>(V.size()));
        CNST_ITYPE M(static_cast<ITYPE>(A.size() / N));
		vector<DTYPE> rst(N);

        DGEMV(&CHARN, &M, &N, &ONED, 
                &A[0], &M, &V[0], &ONEI,
                &ZEROD, &rst[0], &ONEI);
		return rst;
	}

    // complex
	vector<CTYPE> matvec_(const vector<CTYPE>& A, const vector<CTYPE>& V)
	{
        CNST_ITYPE N(static_cast<ITYPE>(V.size()));
        CNST_ITYPE M(static_cast<ITYPE>(A.size() / N));
		vector<CTYPE> rst(N);

        CGEMV(&CHARN, &M, &N, &ONEC, 
                &A[0], &M, &V[0], &ONEI,
                &ZEROC, &rst[0], &ONEI);
		return rst;
	}

    // complex*16
	vector<ZTYPE> matvec_(const vector<ZTYPE>& A, const vector<ZTYPE>& V)
	{
        CNST_ITYPE N(static_cast<ITYPE>(V.size()));
        CNST_ITYPE M(static_cast<ITYPE>(A.size() / N));
		vector<ZTYPE> rst(N);

        ZGEMV(&CHARN, &M, &N, &ONEZ, 
                &A[0], &M, &V[0], &ONEI,
                &ZEROZ, &rst[0], &ONEI);
		return rst;
	}

    // interfaces
    template<typename T>
        vector<T> matvec(const vector<T>& A, const vector<T>& V) {
            return matvec_(A, V);
        }
};

#endif // _MATRIXOP_MATVEC_HPP
