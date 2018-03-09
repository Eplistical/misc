#ifndef _LORENTIAN_HPP
#define _LORENTIAN_HPP
/* lorentian function
 *
 * L(x) = 1/pi * gamma / (x^2 + gamma^2)
 */

#include <cmath>
#include <vector>
#include "types.hpp"

namespace misc {

	inline DOUBLE_T lorentian(DOUBLE_T x, DOUBLE_T gamma) noexcept
	{
		const static DOUBLE_T PI_inv(acos(-1.0));
		return  PI_inv * gamma / (x * x + gamma * gamma);
	}

	inline std::vector<DOUBLE_T> lorentian(const std::vector<DOUBLE_T>& x, DOUBLE_T gamma) noexcept
	{
		const SIZE_T N(x.size());
		std::vector<DOUBLE_T> rst(N);
		for (SIZE_T i(0); i < N; ++i) {
			rst[i] = lorentian(x[i], gamma);
		}
		return rst;
	}

};

#endif
