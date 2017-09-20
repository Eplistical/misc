#ifndef _FERMI_HPP
#define _FERMI_HPP
/* fermi function
 *
 * f(x) = 1 / (1 + e**x) 
 */

#include <cmath>
#include <vector>
#include "types.hpp"

inline DOUBLE_T Fermi(DOUBLE_T x) noexcept
{
    return 1.0 / (1.0 + std::exp(x));
}

inline COMPLEX_T Fermi(const COMPLEX_T& z) noexcept
{
    return 1.0 / (1.0 + std::exp(x));
}

template <typename Type>
inline std::vector<Type> Fermi(const std::vector<Type>& x) noexcept
{
    const SIZE_T N(x.size());
    std::vector<Type> rst(N);
    for (SIZE_T i(0); i < N; ++i) {
        rst[i] = Fermi(x[i]);
    }
    return rst;
}

#endif
