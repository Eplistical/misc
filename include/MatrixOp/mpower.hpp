#ifndef _MATRIXOP_MPOWER_HPP
#define _MATRIXOP_MPOWER_HPP

/*  
 *  matrixop::mpower(A, p) 
 *
 *  function for calculating matrix power A^p
 *
 *  param   A: matrix A (N*N)
 *  param   p: power
 *
 *  return A^p
 *
 ****************************************
 *
 *  matrixop::mpower_inplace(A, p) 
 *
 *  function for calculating matrix power A^p inplace
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

    // TODO: write mpower and mpower_inplace
    template <typename T1, typename T2>
	inline vector<T1> mpower(const vector<T1>& A, const T2& p) 
	{
	}

    template <typename T1, typename T2>
	inline VOID mpower_inplace(vector<T1>& A, const T2& p) 
	{
	}
};

#endif
