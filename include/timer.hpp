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
#include <sstream>
#include <unordered_map>
#include "types.hpp"

namespace timer {
    using namespace std;
	using namespace std::chrono;
	using TicTimeType = unordered_map<INT_T, time_point<system_clock> >;

	static TicTimeType tic_time;

	inline VOID_T tic(INT_T index = 0) noexcept
    {
		tic_time[index] = system_clock::now();
	}

	inline STRING_T toc(INT_T index = 0) noexcept
    {
		if (tic_time.find(index) == tic_time.end()) {
			return STRING_T("timer::toc: error!, index not found");
		}
		duration<DOUBLE_T> elapsed = system_clock::now() - tic_time[index];
		ostringstream buf;
		buf << "Time elapsed: " << elapsed.count() << " s" ;
		return buf.str();
	}

    inline DOUBLE_T elapsed(INT_T index = 0) noexcept 
    {
		duration<DOUBLE_T> rst = system_clock::now() - tic_time[index];
        return rst.count();
    }

	inline STRING_T now() noexcept
    {
		const time_t _now = system_clock::to_time_t(system_clock::now());
		ostringstream buf;
		buf << "now: " << ctime(&_now);
		return buf.str();
	}
};
#endif
