#ifndef _MATRIXOP_ZEROS_HPP
#define _MATRIXOP_ZEROS_HPP

/*  
 *  matrixop::zeros(N, [M])
 *
 *  get an N*M zero matrix
 *
 *  param   N: # rows of matrix
 *  param   M: # cols of matrix, default M = N
 *
 * 	return I(N*M)
 *
 ****************************************
 * 
 *  matrixop::zeros_inplace(A, N, [M])
 *
 *  get an N*M zero matrix
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

    // interfaces
    template <typename T = DTYPE>
        inline vector<T> zeros(CNST_ITYPE N, ITYPE M = -1) {
            M = (M <= 0 ? N : M);
            return vector<T>(N * M, static_cast<T>(0.0));
        }

    template <typename T>
        inline VOID zeros_inplace(vector<T>& A, CNST_ITYPE N, ITYPE M = -1) {
            M = (M <= 0 ? N : M);
            A.assign(N * M, static_cast<T>(0.0));
        }
};

#endif // _MATRIXOP_ZEROS_HPP
