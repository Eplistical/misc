#ifndef _MATRIXOP_LOGM_HPP
#define _MATRIXOP_LOGM_HPP

/*  
 *  matrixop::logmh(A) 
 *
 *  function for calculating matrix log(A)
 *
 *  param   A: Hermitian matrix A (N*N)
 *
 *  return A^p
 *
 ****************************************
 *
 *  matrixop::logmh_inplace(A, p) 
 *
 *  function for calculating matrix log(A) inplace
 *
 *  param   A: Hermitian matrix A (N*N)
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

    // TODO: write logmh and logmh_inplace
    template <typename T1, typename T2>
	inline vector<T1> logmh(const vector<T1>& A, const T2& p) 
	{
	}

    template <typename T1, typename T2>
	inline VOID logmh_inplace(vector<T1>& A, const T2& p) 
	{
	}
};

#endif
