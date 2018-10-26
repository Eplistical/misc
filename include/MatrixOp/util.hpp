#ifndef _MATRIXOP_UTIL_HPP
#define _MATRIXOP_UTIL_HPP

/*  
 *  Addtional utilities for MatrixOp
 *
 *  matrixop::vecCmatvec(V, A, W)
 *
 *  function for calculating <V|A|W>
 *
 * 	param   V:  vector V (M)
 * 	param   A:  matrix A (M*N)
 * 	param   W:  vector W (N)
 *
 * 	return <V|A|W> (scalar)
 *
 *
 ****************************************
 *
 *  matrixop::matCmatmat(A, B, C, L, K)
 *
 *  function for calculating A' * B * C
 *
 * 	param   A:  matrix A (L*M)
 * 	param   B:  matrix B (L*K)
 * 	param   C:  matrix C (K*N)
 * 	param   L, K: matrix B dimensions
 *
 * 	return A' * B * C (M*N)
 *
 *
 ****************************************
 *
 *  matrixop::matmatmatC(A, B, C, L, K)
 *
 *  function for calculating A * B * C'
 *
 * 	param   A:  matrix A (M*L)
 * 	param   B:  matrix B (L*K)
 * 	param   C:  matrix C (N*K)
 * 	param   L, K: matrix B dimensions
 *
 * 	return A * B * C' (M*N)
 *
 */

#include <vector>
#include <cmath>
#include "matrixop_config.hpp"
#include "matvec.hpp"
#include "matmat.hpp"
#include "matCmat.hpp"
#include "dot.hpp"
#include "adjoint.hpp"


namespace matrixop {
	using std::vector;

    template <typename T>
        inline T vecmatvec(const vector<T>& V, const vector<T>& A, const vector<T>& W) {
            return dot(V, matvec(A, W));
        }

    template <typename T>
        inline T vecCmatvec(const vector<T>& V, const vector<T>& A, const vector<T>& W) {
            return dotc(V, matvec(A, W));
        }

    template <typename T>
        inline T vecmatCvec(const vector<T>& V, const vector<T>& A, const vector<T>& W) {
            return dot(V, matCvec(A, W));
        }

    template <typename T>
        inline T vecCmatCvec(const vector<T>& V, const vector<T>& A, const vector<T>& W) {
            return dotc(V, matCvec(A, W));
        }

    template <typename T>
        inline vector<T> matmatmat(const vector<T>& A, const vector<T>& B, const vector<T>& C, CNST_ITYPE L, CNST_ITYPE K) {
            return matmat(A, matmat(B, C, K), L);
        }

    template <typename T>
        inline vector<T> matCmatmat(const vector<T>& A, const vector<T>& B, const vector<T>& C, CNST_ITYPE L, CNST_ITYPE K) {
            return matCmat(A, matmat(B, C, K), L);
        }

    template <typename T>
        inline vector<T> matmatmatC(const vector<T>& A, const vector<T>& B, const vector<T>& C, CNST_ITYPE L, CNST_ITYPE K) {
            return matmat(A, matmatC(B, C, K), L);
        }

    template <typename T>
        inline vector<T> matmatCmat(const vector<T>& A, const vector<T>& B, const vector<T>& C, CNST_ITYPE L, CNST_ITYPE K) {
            return matmat(A, matCmat(B, C, K), L);
        }

    template <typename T>
        inline vector<T> matCmatmatC(const vector<T>& A, const vector<T>& B, const vector<T>& C, CNST_ITYPE L, CNST_ITYPE K) {
            return matCmat(A, matmatC(B, C, K), L);
        }

    template <typename T>
        inline vector<T> matCmatCmatC(const vector<T>& A, const vector<T>& B, const vector<T>& C, CNST_ITYPE L, CNST_ITYPE K) {
            return matCmat(A, matCmatC(B, C, K), L);
        }
};

#endif
