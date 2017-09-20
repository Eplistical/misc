#ifndef _RANDOMER_HPP
#define _RANDOMER_HPP
/* module for random
 * require C++11
 * written based on <random> and <vector>
 *
 * Gaohan
 */
#include <cmath>
#include <random>
#include <vector>
#include "type_traiter.hpp"
#include "types.hpp"

namespace randomer {
    using namespace std;

	static random_device rd;
	static mt19937 rng(rd());

	inline DOUBLE_T rand(DOUBLE_T lb = 0.0, DOUBLE_T ub = 1.0) noexcept 
    {
		uniform_real_distribution<> dis(lb, ub);
		return dis(rng);
	}

	inline vector<DOUBLE_T> vrand(INT_T N, DOUBLE_T lb = 0.0, DOUBLE_T ub = 1.0) noexcept 
    {
		uniform_real_distribution<> dis(lb, ub);
		vector<DOUBLE_T> rst(N);
		for(INT_T j = 0; j < N; ++j)
			rst[j] = dis(rng);
		return rst;
	}

	inline DOUBLE_T normal(DOUBLE_T mu = 0.0, DOUBLE_T sigma = 1.0) noexcept 
    {
		normal_distribution<DOUBLE_T> dis(mu, sigma);
		return dis(rng);
	}

	inline vector<DOUBLE_T> vnormal(INT_T N, DOUBLE_T mu = 0.0, DOUBLE_T sigma = 1.0) noexcept 
    {
		normal_distribution<DOUBLE_T> dis(mu, sigma);
		vector<DOUBLE_T> rst(N);
		for(INT_T j = 0; j < N; ++j)
			rst[j] = dis(rng);
		return rst;
	}

	inline INT_T discrete(const vector<DOUBLE_T>& prob) noexcept 
    {
		discrete_distribution<INT_T> dis(prob.begin(), prob.end());
		INT_T rst = dis(rng);
		return rst;
	}
};
#endif
