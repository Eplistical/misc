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
#include "types.hpp"

namespace randomer {
	static std::random_device ran_dev;
	static std::mt19937 gen(ran_dev());

	inline DOUBLE_T rand(DOUBLE_T lb = 0.0, DOUBLE_T ub = 1.0) noexcept {
		std::uniform_real_distribution<> dis(lb, ub);
		return dis(gen);
	}

	inline std::vector<DOUBLE_T> vrand(INT_T N, DOUBLE_T lb = 0.0, DOUBLE_T ub = 1.0) noexcept {
		std::uniform_real_distribution<> dis(lb, ub);
		std::vector<DOUBLE_T> rst(N);
		for(INT_T j = 0; j < N; ++j) {
			rst[j] = dis(gen);
		}
		return rst;
	}

	inline DOUBLE_T normal(DOUBLE_T mu = 0.0, DOUBLE_T sigma = 1.0) noexcept {
		std::normal_distribution<DOUBLE_T> dis(mu, sigma);
		return dis(gen);
	}

	inline std::vector<DOUBLE_T> vnormal(INT_T N, DOUBLE_T mu = 0.0, DOUBLE_T sigma = 1.0) noexcept {
		std::normal_distribution<DOUBLE_T> dis(mu, sigma);
		std::vector<DOUBLE_T> rst(N);
		for(INT_T j = 0; j < N; ++j) {
			rst[j] = dis(gen);
		}
		return rst;
	}

	inline INT_T discrete(const std::vector<DOUBLE_T>& prob) noexcept {
		std::discrete_distribution<INT_T> dis(prob.begin(), prob.end());
		return dis(gen);
	}

    inline INT_T choice(INT_T N) noexcept {
        // pick one number from 0 to N-1
        std::uniform_int_distribution<> dis(0, N - 1);
        return dis(gen);
    }

    template <typename ElementType>
        inline ElementType choice(const std::vector<ElementType>& v) noexcept {
            // pick one element from vector v
            return v.at(choice(v.size()));
        }
};
#endif // _RANDOMER_HPP
