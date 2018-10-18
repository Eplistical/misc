#ifndef _MATRIXOP_EYE_HPP
#define _MATRIXOP_EYE_HPP

/*  
 *  matrixop::eye(N, [M])
 *
 *  get an N*M identity matrix
 *
 *  param   N: # rows of matrix
 *  param   M: # cols of matrix, default M = N
 *
 * 	return I(N*M)
 *
 ****************************************
 * 
 *  matrixop::eye_inplace(A, N, [M])
 *
 *  get an N*M identity matrix
 *
 *  param   A: matrix A to store result
 *  param   N: # rows of matrix
 *  param   M: # cols of matrix, default M = N
 *
 */

#include <vector>
#include <complex>
#include "matrixop_config.hpp"

namespace matrixop {
	using std::vector;

    template <typename T>
        inline VOID _eye(T* A, CNST_ITYPE N, CNST_ITYPE M) 
        {
            CNST_ITYPE interval(N + 1);
            CNST_ITYPE imax( (N >= M) ? M : N );
            ITYPE idx(0);
            for (ITYPE i(0); i < imax; ++i) {
                A[idx] = static_cast<T>(1.0);
                idx += interval;
            }
        } 

    // interfaces
    template <typename T = DTYPE>
        inline vector<T> eye(CNST_ITYPE N, ITYPE M = -1) {
            M = (M <= 0 ? N : M);
            vector<T> A(N * M, static_cast<T>(0.0));
            _eye(&A[0], N, M);
            return A;
        }

    template <typename T>
        inline VOID eye_inplace(vector<T>& A, CNST_ITYPE N, ITYPE M = -1) {
            M = (M <= 0 ? N : M);
            A.assign(N * M, static_cast<T>(0.0));
            _eye(&A[0], N, M);
        }
};

#endif // _MATRIXOP_EYE_HPP
