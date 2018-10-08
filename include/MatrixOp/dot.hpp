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
	inline STYPE _dot(CNST_STYPE* V, CNST_STYPE* W, CNST_ITYPE N)
	{
        return SDOT(&N, V, &ONEI, W, &ONEI);
	}

	inline STYPE _dotc(CNST_STYPE* V, CNST_STYPE* W, CNST_ITYPE N)
	{
        return SDOT(&N, V, &ONEI, W, &ONEI);
	}

    // double
	inline DTYPE _dot(CNST_DTYPE* V, CNST_DTYPE* W, CNST_ITYPE N)
	{
        return DDOT(&N, V, &ONEI, W, &ONEI);
	}

	inline DTYPE _dotc(CNST_DTYPE* V, CNST_DTYPE* W, CNST_ITYPE N)
	{
        return DDOT(&N, V, &ONEI, W, &ONEI);
	}

    // complex
	inline CTYPE _dot(CNST_CTYPE* V, CNST_CTYPE* W, CNST_ITYPE N)
	{
        return CDOTU(&N, V, &ONEI, W, &ONEI);
	}

	inline CTYPE _dotc(CNST_CTYPE* V, CNST_CTYPE* W, CNST_ITYPE N)
	{
        return CDOTC(&N, V, &ONEI, W, &ONEI);
	}

    // complex*16
	inline ZTYPE _dot(CNST_ZTYPE* V, CNST_ZTYPE* W, CNST_ITYPE N)
	{
        return ZDOTU(&N, V, &ONEI, W, &ONEI);
	}

	inline ZTYPE _dotc(CNST_ZTYPE* V, CNST_ZTYPE* W, CNST_ITYPE N)
	{
        return ZDOTC(&N, V, &ONEI, W, &ONEI);
	}

    // interfaces
    template<typename T>
        inline T dot(const vector<T>& V, const vector<T>& W) {
            return _dot(&V[0], &W[0], static_cast<ITYPE>(V.size()));
        }

    template<typename T>
        inline T dotc(const vector<T>& V, const vector<T>& W) {
            return _dotc(&V[0], &W[0], static_cast<ITYPE>(V.size()));
        }

};

#endif // _MATRIXOP_DOT_HPP
