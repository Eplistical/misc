#ifndef _TIMER_HPP
#define _TIMER_HPP
/* module for timer 
 * require C++11
 * written based on <chrono> and <ctime>
 *
 * Gaohan
 */
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <unordered_map>
#include "types.hpp"

namespace timer {
    using namespace std;
	using namespace std::chrono;
	using TicTimeType = unordered_map<INT_T, time_point<system_clock> >;

	static TicTimeType tic_time;

	inline void tic(INT_T index = 0) noexcept
    {
		tic_time[index] = system_clock::now();
	}

	inline string toc(INT_T index = 0) noexcept
    {
		if (tic_time.find(index) == tic_time.end()) {
			return string("timer::toc: error!, index not found");
		}
		duration<double> elapsed = system_clock::now() - tic_time[index];
		ostringstream buf;
		buf << "Time elapsed: " << elapsed.count() << " s" ;
		return buf.str();
	}

    inline double elapsed(INT_T index = 0) noexcept 
    {
		duration<double> rst = system_clock::now() - tic_time[index];
        return rst.count();
    }

	inline string now() noexcept
    {
		const time_t _now = system_clock::to_time_t(system_clock::now());
		ostringstream buf;
		buf << "now: " << ctime(&_now);
		return buf.str();
	}
};
#endif
