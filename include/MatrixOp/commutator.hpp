#ifndef _MATRIXOP_COMMUTATOR_HPP
#define _MATRIXOP_COMMUTATOR_HPP

/*  
 *  matrixop::commutator(A, B)
 *
 *  function for calculating commutator
 *
 * 	param   A:  square matrix A (K*K)
 * 	param   B:  square matrix B (K*K)
 *
 * 	return AB - BA
 *
 */


#include <vector>
#include <cmath>
#include "matrixop_config.hpp"
#include "matmat.hpp"

namespace matrixop {
	using std::vector;
	using std::sqrt;

    template <typename T>
        inline vector<T> commutator(const vector<T>& A, const vector<T>& B) {
            const int K = sqrt(A.size());
            return matmat(A, B, K) - matmat(B, A, K);
        }

};

#endif // _MATRIXOP_COMMUTATOR_HPP
