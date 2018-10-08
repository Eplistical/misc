#ifndef _MATRIXOP_NRM_HPP
#define _MATRIXOP_NRM_HPP

/*  
 *  matrixop::nrm2(V)
 *
 *  function for vector norm^2
 *
 * 	param   V:  vector
 *
 * 	return norm square of V
 *
 ****************************************
 *
 *  matrixop::nrm(V)
 *
 *  function for vector norm
 *
 * 	param   V:  vector
 *
 *  return norm of V
 *
 */


#include <vector>
#include <cmath>
#include "matrixop_config.hpp"

namespace matrixop {
	using std::vector;
	using std::sqrt;

    // single
	inline STYPE nrm2_(CNST_STYPE* V, CNST_ITYPE N)
	{
        return SNRM2(&N, V, &ONEI);
	}

    // double
	inline DTYPE nrm2_(CNST_DTYPE* V, CNST_ITYPE N)
	{
        return DNRM2(&N, V, &ONEI);
	}
    
    // complex
	inline STYPE nrm2_(CNST_CTYPE* V, CNST_ITYPE N)
	{
        return SCNRM2(&N, V, &ONEI);
	}

    // complex*16
	inline DTYPE nrm2_(CNST_ZTYPE* V, CNST_ITYPE N)
	{
        return DZNRM2(&N, V, &ONEI);
	}

    // interfaces
    inline STYPE nrm2(const vector<STYPE>& V) 
    { 
        return nrm2_(&V[0], V.size());
    }

    inline DTYPE nrm2(const vector<DTYPE>& V) 
    { 
        return nrm2_(&V[0], V.size());
    }

    inline STYPE nrm2(const vector<CTYPE>& V) 
    { 
        return nrm2_(&V[0], V.size());
    }

    inline DTYPE nrm2(const vector<ZTYPE>& V) 
    { 
        return nrm2_(&V[0], V.size());
    }

    inline STYPE nrm(const vector<STYPE>& V) 
    { 
        return std::sqrt(nrm2(V));
    }

    inline DTYPE nrm(const vector<DTYPE>& V) 
    { 
        return std::sqrt(nrm2(V));
    }

    inline STYPE nrm(const vector<CTYPE>& V) 
    { 
        return std::sqrt(nrm2(V));
    }

    inline DTYPE nrm(const vector<ZTYPE>& V) 
    { 
        return std::sqrt(nrm2(V));
    }
};

#endif // _MATRIXOP_NRM_HPP
