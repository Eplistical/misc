#ifndef _STATS_HPP
#define _STATS_HPP
/* module for statistical calculations
 * require C++11
 * written based on <vector>
 *
 * Gaohan
 */
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <type_traits>
#include <stdexcept>
#include "types.hpp"
#include "crasher.hpp"


namespace misc {

    namespace stats {

        template <typename T>
        DOUBLE_T mean(const std::vector<T>& v)
        {
            /*
             * calc sample mean value of the vector v
             *  \sum_{i=0}^{N-1} v[i] / N
             */
            misc::crasher::confirm(v.size() > 0, "misc::stats::mean: vector size must be positive.");
            return std::accumulate(v.begin(), v.end(), static_cast<T>(0)) * 1.0 / v.size();
        }

        template <typename T>
        DOUBLE_T moment(const std::vector<T>& v, const int n)
        {
            /*
             * calc n^th central moment of the vector v
             *  \sum_{i=0}^{N-1} (v[i] - mu)^n / N
             */
            misc::crasher::confirm(v.size() > 0, "misc::stats::moments: vector size must be positive.");
            const DOUBLE_T mu = mean(v);
            return std::accumulate(v.begin(), v.end(), static_cast<T>(0), 
                                    [mu, n](const T& x, const T& y){ return x + std::pow(y - mu, n); }) * 1.0 / v.size();
        }

        template <typename T>
        DOUBLE_T moment_normalized(const std::vector<T>& v, const int n)
        {
            /*
             * calc normalized n^th central moment of the vector v
             *  moment(v, n) / moment(v, 2)**(n/2)
             */
            return moment(v, n) / std::pow(moment(v, 2), 0.5 * n);
        }

        template <typename T>
        DOUBLE_T var(const std::vector<T>& v)
        {
            /*
             * calc sample variance of the vector v
             *  \sum_{i=0}^{N-1} (v[i] - mu)^2 / (N-1)
             */
            misc::crasher::confirm(v.size() > 1, "misc::stats::var: vector size must > 1.");
            return moment(v, 2) * v.size() / (v.size() - 1);
        }

        template <typename T>
        DOUBLE_T skew(const std::vector<T>& v, const BOOL_T bias = true)
        {
            /*
             * calc skewness of the vector v
             *  biased: m3 / m2**1.5
             *  unbiased: m3 / m2**1.5 * sqrt(N*(N-1)) / (N-2)
             */
            const DOUBLE_T m2 = moment(v, 2);
            misc::crasher::confirm(m2 > 0.0, "misc::stats::skew: data 2nd moment must > 0.0.");
            const DOUBLE_T m3 = moment(v, 3);

            DOUBLE_T rst = m3 / std::pow(m2, 1.5);
            if (not bias) {
                misc::crasher::confirm(v.size() > 2, "misc::stats::skew: vector size must > 2.");
                const SIZE_T N = v.size();
                rst *= std::sqrt(N * (N - 1)) / (N - 2);
            }
            return rst;
        }

        template <typename T>
        DOUBLE_T kurtosis(const std::vector<T>& v, const BOOL_T bias = true, const BOOL_T fisher = true)
        {
            /*
             * calc kurtosis of the vector v
             *  biased: m4 / m2**2 - 3 
             *  unbiased: 1/(N-2)/(N-3) * ((N**2-1) * m4/m2**2 - 3(N-1)**2) - 3
             */
            const DOUBLE_T m2 = moment(v, 2);
            misc::crasher::confirm(m2 > 0.0, "misc::stats::kurtosis: data 2nd moment must > 0.0.");
            const DOUBLE_T m4 = moment(v, 4);

            DOUBLE_T rst = m4 / std::pow(m2, 2);
            if (not bias) {
                misc::crasher::confirm(v.size() > 3, "misc::stats::kurtosis: vector size must > 3.");
                const SIZE_T N = v.size();
                rst = 1.0 * (N - 1) / (N - 2) / (N - 3) * ((N + 1) * rst - 3.0 * (N - 1)) + 3.0;
            }
            if (fisher) {
                rst -= 3.0;
            }
            return rst;
        }

    };

};


#endif
