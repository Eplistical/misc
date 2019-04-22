#ifndef _MATRIXOP_DIAG_HPP
#define _MATRIXOP_DIAG_HPP

/*  
 *  matrixop::diag_v2m(v)
 *
 *  convert a vector to a diagonal matrix
 *
 *  param   v: the vector
 *
 * 	return  mat: the matrix
 *
 ****************************************
 * 
 *  matrixop::diag_m2v(mat)
 *
 *  extract diagonal elements of a squared matrix
 *
 * 	param  mat: the matrix
 *
 *  return   v: the diagonal vector
 *
 */

#include <cmath>
#include <vector>
#include <complex>
#include "matrixop_config.hpp"

namespace matrixop {
	using std::vector;

    // interfaces
    template <typename T>
        inline vector<T> diag_v2m(const vector<T>& v) {
            CNST_ITYPE N(v.size());
            vector<T> mat(N * N);
            for (ITYPE i(0); i < N; ++i) {
                mat[i+i*N] = v[i];
            }
            return mat;
        }

    template <typename T>
        inline vector<T> diag_m2v(const vector<T>& mat) {
            CNST_ITYPE N(std::sqrt(mat.size()));
            vector<T> v(N);
            for (ITYPE i(0); i < N; ++i) {
                v[i] = mat[i+i*N];
            }
            return v;
        }
};

#endif // _MATRIXOP_DIAG_HPP
