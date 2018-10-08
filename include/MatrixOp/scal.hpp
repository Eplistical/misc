#ifndef _MATRIXOP_scal_HPP
#define _MATRIXOP_scal_HPP

/*  
 *  matrixop::scal(V, k)
 *
 *  function for vector scaling
 *
 * 	param   V:  vector
 * 	param   k:  scaling const
 *
 * 	return k*V
 *
 ****************************************
 *
 *  matrixop::scal_inplace(V, k)
 *
 *  function for inplace vector scaling
 *
 * 	param   V:  vector
 * 	            on exit, V is k*V
 * 	param   k:  scaling const
 *
 *
 */


#include <vector>
#include "matrixop_config.hpp"

namespace matrixop {
	using std::vector;

    // single
	inline VOID _scal(STYPE* V, CNST_STYPE k, CNST_ITYPE N)
	{
        SSCAL(&N, &k, V, &ONEI);
	}

    // double
	inline VOID _scal(DTYPE* V, CNST_DTYPE k, CNST_ITYPE N)
	{
        DSCAL(&N, &k, V, &ONEI);
	}

    // complex
	inline VOID _scal(CTYPE* V, CNST_CTYPE k, CNST_ITYPE N)
	{
        CSCAL(&N, &k, V, &ONEI);
	}

	inline VOID _scal(CTYPE* V, CNST_STYPE k, CNST_ITYPE N)
	{
        CSSCAL(&N, &k, V, &ONEI);
	}

    // complex*16
	inline VOID _scal(ZTYPE* V, CNST_ZTYPE k, CNST_ITYPE N)
	{
        ZSCAL(&N, &k, V, &ONEI);
	}

	inline VOID _scal(ZTYPE* V, CNST_DTYPE k, CNST_ITYPE N)
	{
        ZDSCAL(&N, &k, V, &ONEI);
	}

    // interfaces
    template<typename T>
        inline vector<T> scal(const vector<T>& V, const T k) {
            vector<T> rst(V);
            _scal(&rst[0], k, static_cast<ITYPE>(V.size()));
            return rst;
        }

    template<typename T>
        inline VOID scal_inplace(vector<T>& V, const T k) {
            _scal(&V[0], k, static_cast<ITYPE>(V.size()));
        }
};

#endif // _MATRIXOP_scal_HPP
