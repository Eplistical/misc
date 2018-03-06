#ifndef _RANDOMER_HPP
#define _RANDOMER_HPP
/* module for random
 * require C++11
 * written based on <random> and <vector>
 * using external lib: 
 * 	boost/type_traits.hpp
 * 	boost/spirit/home/support/container.hpp
 *
 * Gaohan
 */
#include <cmath>
#include <random>
#include <vector>

#include <boost/type_traits.hpp>
#include <boost/spirit/home/support/container.hpp>

namespace randomer {
	static std::random_device ran_dev;
	static std::mt19937 gen(ran_dev());

	inline double rand(double lb = 0.0, double ub = 1.0) noexcept {
		std::uniform_real_distribution<> dis(lb, ub);
		return dis(gen);
	}

	inline std::vector<double> vrand(int N, double lb = 0.0, double ub = 1.0) noexcept {
		std::uniform_real_distribution<> dis(lb, ub);
		std::vector<double> rst(N);
		for(int j = 0; j < N; ++j)
			rst[j] = dis(gen);
		return rst;
	}

	inline double normal(double mu = 0.0, double sigma = 1.0) noexcept {
		std::normal_distribution<double> dis(mu, sigma);
		return dis(gen);
	}

	inline std::vector<double> vnormal(int N, double mu = 0.0, double sigma = 1.0) noexcept {
		std::normal_distribution<double> dis(mu, sigma);
		std::vector<double> rst(N);
		for(int j = 0; j < N; ++j)
			rst[j] = dis(gen);
		return rst;
	}

	inline int discrete(const std::vector<double>& prob) noexcept {
		std::discrete_distribution<int> dis(prob.begin(), prob.end());
		return dis(gen);
	}

    inline int choice(int N) noexcept {
        // pick one number from 0 to N-1
        std::uniform_int_distribution<> dis(0, N - 1);
        return dis(gen);
    }

    template <typename ElementType>
        inline ElementType choice(const std::vector<ElementType>& v) noexcept {
            // pick one element from vector v
            return v[choice(v.size())];
        }
};
#endif
