#ifndef _VECTOR_MKL_HPP
#define _VECTOR_MKL_HPP
/* module for vector operations
 *
 *  writtern based on intel MKL
 *
 *  Gaohan
 */
#ifndef MKL_Complex16
#define MKL_Complex16 std::complex<double>
#endif

#include <vector>
#include <complex>
#include "mkl.h"

using namespace std;

inline vector<double> operator+(const vector<double>& v1, 
        const vector<double>& v2)
{
    int const N(v1.size());
    vector<double> rst(N);
    vdAdd(N, &v1[0], &v2[0], &rst[0]);
    return rst;
}



#endif
