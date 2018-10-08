#ifndef _MATRIXOP_DOT_HPP
#define _MATRIXOP_DOT_HPP

/*  
 *  matrixop::dot(V, W)
 *
 *  function for vector inner product 
 *
 * 	param   V:  vector 1
 * 	param   W:  vector 2
 *
 * 	return V.T * W
 *
 ****************************************
 *
 *  matrixop::dotc(V, W)
 *
 *  function for vector inner product 
 *
 * 	param   V:  vector 1
 * 	param   W:  vector 2
 *
 * 	return V.H * W
 *
 */


#include <vector>
#include "matrixop_config.hpp"

namespace matrixop {
	using std::vector;

    // single
	inline STYPE dot_(CNST_STYPE* V, CNST_STYPE* W, CNST_ITYPE N)
	{
        return SDOT(&N, V, &ONEI, W, &ONEI);
	}

	inline STYPE dotc_(CNST_STYPE* V, CNST_STYPE* W, CNST_ITYPE N)
	{
        return SDOT(&N, V, &ONEI, W, &ONEI);
	}

    // double
	inline DTYPE dot_(CNST_DTYPE* V, CNST_DTYPE* W, CNST_ITYPE N)
	{
        return DDOT(&N, V, &ONEI, W, &ONEI);
	}

	inline DTYPE dotc_(CNST_DTYPE* V, CNST_DTYPE* W, CNST_ITYPE N)
	{
        return DDOT(&N, V, &ONEI, W, &ONEI);
	}

    // complex
	inline CTYPE dot_(CNST_CTYPE* V, CNST_CTYPE* W, CNST_ITYPE N)
	{
        return CDOTU(&N, V, &ONEI, W, &ONEI);
	}

	inline CTYPE dotc_(CNST_CTYPE* V, CNST_CTYPE* W, CNST_ITYPE N)
	{
        return CDOTC(&N, V, &ONEI, W, &ONEI);
	}

    // complex*16
	inline ZTYPE dot_(CNST_ZTYPE* V, CNST_ZTYPE* W, CNST_ITYPE N)
	{
        return ZDOTU(&N, V, &ONEI, W, &ONEI);
	}

	inline ZTYPE dotc_(CNST_ZTYPE* V, CNST_ZTYPE* W, CNST_ITYPE N)
	{
        return ZDOTC(&N, V, &ONEI, W, &ONEI);
	}

    // interfaces
    template<typename T>
        inline T dot(const vector<T>& V, const vector<T>& W) {
            return dot_(V, W, V.size());
        }

    template<typename T>
        inline T dotc(const vector<T>& V, const vector<T>& W) {
            return dotc_(V, W, V.size());
        }

};

#endif // _MATRIXOP_DOT_HPP