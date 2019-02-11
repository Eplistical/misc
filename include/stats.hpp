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
        DOUBLE_T moment(const std::vector<T>& v, const INT_T n)
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
        DOUBLE_T moment_normalized(const std::vector<T>& v, const INT_T n)
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

        template <typename T1, typename T2>
        DOUBLE_T percentile(const std::vector<T1>& v, const T2& raw_idx) {
            /*
             * calc percentiles of the vector v, scalar index form
             *  raw_idx: the percentile, [0,100]
             */
            const SIZE_T N = v.size();
            misc::crasher::confirm(N > 0, "misc::stats::percentile: vector size must > 0.");
            misc::crasher::confirm(raw_idx >= 0.0 and raw_idx <= 100.0, "misc::stats::percentile: indices must be in [0, 100]");

            if (N == 1) {
                return v[0];
            }

            const DOUBLE_T q = raw_idx / 100.0 * (N - 1);

            // sort v
            std::vector<T1> v_sorted(v);
            std::sort(v_sorted.begin(), v_sorted.end());

            // calculate rst
            DOUBLE_T rst;
            const INT_T idx0 = static_cast<INT_T>(q);
            if (idx0 == N - 1) {
                rst = v_sorted[idx0];
            }
            else {
                rst = v_sorted[idx0] + (v_sorted[idx0 + 1] - v_sorted[idx0]) * (q - idx0); 
            }

            return rst;
        }

        template <typename T1, typename T2>
        std::vector<DOUBLE_T> percentile(const std::vector<T1>& v, const std::vector<T2>& raw_idx) {
            /*
             * calc percentiles of the vector v, vector indices form
             *  raw_idx: percentile q's, each element is in [0, 100]
             */
            const SIZE_T N = v.size();
            const SIZE_T Nidx = raw_idx.size();

            misc::crasher::confirm(N > 1, "misc::stats::percentile: vector size must > 1.");
            for (SIZE_T i(0); i < Nidx; ++i) {
                misc::crasher::confirm(raw_idx[i] >= 0.0 and raw_idx[i] <= 100.0, 
                                        "misc::stats::percentile: indices must be in [0, 100]");
            }

            if (N == 1) {
                return std::vector<double>(Nidx, v[0]);
            }

            std::vector<DOUBLE_T> q(Nidx);

            // convert indices to q
            for (SIZE_T i(0); i < Nidx; ++i) {
                q[i] = (raw_idx[i] / 100.0 * (N - 1));
            }

            // sort v
            std::vector<T1> v_sorted(v);
            std::sort(v_sorted.begin(), v_sorted.end());

            // calculate rst
            std::vector<DOUBLE_T> rst(Nidx);
            for (SIZE_T i(0); i < Nidx; ++i) {
                const INT_T idx0 = static_cast<INT_T>(q[i]);
                if (idx0 == N - 1) {
                    rst[i] = v_sorted[idx0];
                }
                else {
                    rst[i] = v_sorted[idx0] + (v_sorted[idx0 + 1] - v_sorted[idx0]) * (q[i] - idx0);
                }
            }

            return rst;
        }

    };

};


#endif
