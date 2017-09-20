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

namespace randomer {
    using namespace std;

	static random_device rd;
	static mt19937 rng(rd());

	inline double rand(double lb = 0.0, double ub = 1.0) noexcept 
    {
		uniform_real_distribution<> dis(lb, ub);
		return dis(rng);
	}

	inline vector<double> vrand(int N, double lb = 0.0, double ub = 1.0) noexcept 
    {
		uniform_real_distribution<> dis(lb, ub);
		vector<double> rst(N);
		for(int j = 0; j < N; ++j)
			rst[j] = dis(rng);
		return rst;
	}

	inline double normal(double mu = 0.0, double sigma = 1.0) noexcept 
    {
		normal_distribution<double> dis(mu, sigma);
		return dis(rng);
	}

	inline vector<double> vnormal(int N, double mu = 0.0, double sigma = 1.0) noexcept 
    {
		normal_distribution<double> dis(mu, sigma);
		vector<double> rst(N);
		for(int j = 0; j < N; ++j)
			rst[j] = dis(rng);
		return rst;
	}

	inline int discrete(const vector<double>& prob) noexcept 
    {
		discrete_distribution<int> dis(prob.begin(), prob.end());
		int rst = dis(rng);
		return rst;
	}
};
#endif
