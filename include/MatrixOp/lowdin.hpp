#ifndef _MATRIXOP_LOWDIN_HPP
#define _MATRIXOP_LOWDIN_HPP

/*  
 *  matrixop::lowdin(A, N) 
 *
 *  function for orthogonalizing matrix A (Lowdin algorithm)
 *  i.e. A => A * (A^H * A)^(-1/2)
 *
 *  param   A: matrix A (M*N)
 *  param   N: # columns in A
 *
 *  return orthogonalized matrix
 *  
 *
 ****************************************
 *
 *  matrixop::lowdin_inplace(A, N) 
 *
 *  function for orthogonalizing matrix A inplace (Lowdin algorithm)
 *  i.e. A => A * (A^H * A)^(-1/2)
 *
 *  param   A: matrix A (M*N)
 *              on exit, A is orthogonalized M*N matrix
 *  param   N: # columns in A
 *
 */

#include <vector>
#include <cmath>
#include "matrixop_config.hpp"
#include "matmat.hpp"
#include "matCmat.hpp"
#include "mpower.hpp"


namespace matrixop {
	using std::vector;

    // TODO: write lowdin and lowdin_inplace
    template <typename T>
	inline vector<T> lowdin(const vector<T>& A, CNST_ITYPE N) 
	{
		//return matmat(A, mpower(matCmat(A, A, N), -0.5), N);
	}
};

#endif
