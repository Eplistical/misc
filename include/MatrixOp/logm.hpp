#ifndef _MATRIXOP_LOGM_HPP
#define _MATRIXOP_LOGM_HPP

/*  
 *  matrixop::logm(A) 
 *
 *  function for calculating matrix log(A)
 *
 *  param   A: matrix A (N*N)
 *
 *  return A^p
 *
 ****************************************
 *
 *  matrixop::logm_inplace(A, p) 
 *
 *  function for calculating matrix log(A) inplace
 *
 *  param   A: matrix A (N*N)
 *              on exit, A is A^p
 *  param   p: power
 *
 */

#include <vector>
#include <cmath>
#include "matrixop_config.hpp"
#include "matmat.hpp"
#include "matCmat.hpp"


namespace matrixop {
	using std::vector;

    // TODO: write logm and logm_inplace
    template <typename T1, typename T2>
	inline vector<T1> logm(const vector<T1>& A, const T2& p) 
	{
	}

    template <typename T1, typename T2>
	inline VOID logm_inplace(vector<T1>& A, const T2& p) 
	{
	}
};

#endif
