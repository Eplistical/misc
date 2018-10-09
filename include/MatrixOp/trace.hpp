#ifndef _MATRIXOP_TRACE_HPP
#define _MATRIXOP_TRACE_HPP

/*  
 *  matrixop::trace(A)  matrixop::tr(A) 
 *
 *  function for caluclating matrix trace
 *
 * 	param   A:  matrix (N*N)
 *
 * 	return Tr(A)
 *
 */


#include <vector>
#include <complex>
#include "matrixop_config.hpp"

namespace matrixop {
	using std::vector;
	using std::forward;

    template <typename T>
        inline T _trace(const T* A, CNST_ITYPE N) 
        {
            ITYPE idx(0);
            CNST_ITYPE interval(N + 1);

            T rst(0.0);
            for (ITYPE i(0); i < N; ++i) {
                rst += A[idx];
                idx += interval;
            }
        } 

    // interfaces
    template <typename T>
        inline T trace(const vector<T>& A) {
            return _trace(&A[0], static_cast<ITYPE>(sqrt(A.size())));
        }

    template <typename T>
        inline T tr(const vector<T>& A) {
            return trace(A);
        }
};

#endif // _MATRIXOP_TRACE_HPP
