#ifndef _SGN_HPP
#define _SGN_HPP
// sgn function

#include <cmath>

namespace misc {

	template<typename T>
	inline int sgn(T x)
	{
		if (x == 0) return 0;
		else return x > 0 ? 1 : -1;
	}

};

#endif
