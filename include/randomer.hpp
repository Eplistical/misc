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
#include <unordered_set>
#include <algorithm>
#include <bitset>
#include "types.hpp"

namespace randomer {
	static std::random_device ran_dev;
	static std::mt19937 gen(ran_dev());

	inline DOUBLE_T rand(DOUBLE_T lb = 0.0, DOUBLE_T ub = 1.0) noexcept {
		std::uniform_real_distribution<> dis(lb, ub);
		return dis(gen);
	}

	inline std::vector<DOUBLE_T> vrand(UINT_T N, DOUBLE_T lb = 0.0, DOUBLE_T ub = 1.0) noexcept {
		std::uniform_real_distribution<> dis(lb, ub);
		std::vector<DOUBLE_T> rst(N);
		for(UINT_T j = 0; j < N; ++j) {
			rst[j] = dis(gen);
		}
		return rst;
	}

	inline DOUBLE_T normal(DOUBLE_T mu = 0.0, DOUBLE_T sigma = 1.0) noexcept {
		std::normal_distribution<DOUBLE_T> dis(mu, sigma);
		return dis(gen);
	}

	inline std::vector<DOUBLE_T> vnormal(UINT_T N, DOUBLE_T mu = 0.0, DOUBLE_T sigma = 1.0) noexcept {
		std::normal_distribution<DOUBLE_T> dis(mu, sigma);
		std::vector<DOUBLE_T> rst(N);
		for(UINT_T j = 0; j < N; ++j) {
			rst[j] = dis(gen);
		}
		return rst;
	}

	inline INT_T discrete(const std::vector<DOUBLE_T>& prob) noexcept {
		// pick one number from 0 - N-1, according to probability prob
		std::discrete_distribution<> dis(prob.begin(), prob.end());
		return dis(gen);
	}

    inline INT_T choice(INT_T N) noexcept {
        // randomly pick one number from 0 to N-1
        std::uniform_int_distribution<> dis(0, N - 1);
        return dis(gen);
    }

    template <typename ElementType>
        inline ElementType choice(const std::vector<ElementType>& v) noexcept {
            // pick one element from vector v
            return v.at(choice(v.size()));
        }

	inline std::vector<INT_T> __choice_hash(INT_T N, INT_T m) noexcept {
		// randomly pick m numbers from 0 to N - 1, Hashset way
        std::uniform_int_distribution<> dis(0, N - 1);
		std::unordered_set<INT_T> record;
		if (2 * m <= N) {
			while (record.size() < m) {
				record.insert(dis(gen));
			}
			std::vector<INT_T> rst(record.begin(), record.end());
			std::sort(rst.begin(), rst.end());
			return rst;
		}
		else {
			m = N - m;
			while (record.size() < m) {
				record.insert(dis(gen));
			}
			m = N - m;
			std::vector<INT_T> rst(m);
			INT_T j(0);
			for (INT_T i(0); i < N; ++i) {
				if (record.find(i) == record.end()) {
					rst[j] = i;
					++j;
				}
			}
			return rst;
		}
	}

	inline std::vector<INT_T> __choice_bit(INT_T N, INT_T m) noexcept {
		// randomly pick m numbers from 0 to N - 1, Bitset way
        std::uniform_int_distribution<> dis(0, N - 1);
		constexpr INT_T BitSetMax(1000000);
		if (N <= BitSetMax) {
			std::bitset<BitSetMax> record;
			std::vector<INT_T> rst(m);

			UINT_T Npick( 2 * m <= N ? m : N - m );

			INT_T j(0);
			while (j < Npick) {
				INT_T tmp(dis(gen));
				if (!record.test(tmp)) {
					record.set(tmp);
					++j;
				}
			}

			j = 0;
			BOOL_T target_flag(2 * m <= N);
			for (INT_T i(0); i < N; ++i) {
				if (record.test(i) == target_flag) {
					rst[j] = i;
					++j;
				}
			}
			return rst;
		}
	}

	inline std::vector<INT_T> choice(INT_T N, INT_T m) noexcept {
		if (N > 1000000 or static_cast<DOUBLE_T>(N) / m > 1000.0) {
			return __choice_hash(N, m);
		}
		else {
			return __choice_bit(N, m);
		}
	}
	
};
#endif // _RANDOMER_HPP
