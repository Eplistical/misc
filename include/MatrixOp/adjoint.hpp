#ifndef _MATRIXOP_ADJOINT_HPP
#define _MATRIXOP_ADJOINT_HPP

/*  
 *  matrixop::transpose(A, M)  matrixop::trans(A, M)
 *
 *  function for caluclating matrix transpose
 *
 * 	param   A:  matrix (M*N)
 * 	param   M:  number of rows in A
 *
 * 	return A.T
 *
 ****************************************
 *
 *  matrixop::adjoint(A, M)  matrixop::adj(A, M)
 *
 *  function for caluclating matrix adjoint
 *
 * 	param   A:  matrix (M*N)
 * 	param   M:  number of rows in A
 *
 * 	return A.H
 *
 */


#include <vector>
#include <complex>
#include "matrixop_config.hpp"

namespace matrixop {
	using std::vector;
	using std::forward;
	using std::complex;
	using std::conj;

    template <typename T> 
        inline vector<T> _transpose(const vector<T>& A, CNST_ITYPE M, CNST_ITYPE N)
        {
            vector<T> rst(M * N);
            for (ITYPE r(0); r < M; ++r) {
                for (ITYPE c(0); c < N; ++c) {
                    rst[c + r * N] = A[r + c * M];
                }
            }
            return rst;
        }

    template <typename T> 
        inline vector< complex<T> > _adjoint(const vector< complex<T> >& A, CNST_ITYPE M, CNST_ITYPE N)
        {
            vector< complex<T> > rst(M * N);
            for (ITYPE r(0); r < M; ++r) {
                for (ITYPE c(0); c < N; ++c) {
                    rst[c + r * N] = conj(A[r + c * M]);
                }
            }
            return rst;
        }

    inline vector<STYPE> _adjoint(const vector<STYPE>& A, CNST_ITYPE M, CNST_ITYPE N)
    {
        return _transpose(A);
    }

    inline vector<DTYPE> _adjoint(const vector<DTYPE>& A, CNST_ITYPE M, CNST_ITYPE N)
    {
        return _transpose(A);
    }

    // interfaces
    template<typename T>
        inline vector<T> transpose(const vector<T>& A, CNST_ITYPE M) {
            CNST_ITYPE N(static_cast<ITYPE>(A.size() / M));
            return _transpose(A, M, N);
        }

    template<typename T>
        inline vector<T> trans(const vector<T>& A, CNST_ITYPE M) {
            return transpose(A, M);
        }

    template<typename T>
        inline vector<T> adjoint(const vector<T>& A, CNST_ITYPE M) {
            CNST_ITYPE N(static_cast<ITYPE>(A.size() / M));
            return _adjoint(A, M, N);
        }

    template<typename T>
        inline vector<T> adj(const vector<T>& A, CNST_ITYPE M) {
            return adjoint(A, M);
        }

};

#endif // _MATRIXOP_ADJOINT_HPP
