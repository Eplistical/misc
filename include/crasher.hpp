#ifndef _CRASHER_HPP
#define _CRASHER_HPP
/* module for crashes
 *
 * Gaohan
 */
#include <exception>
#include <string>
#include "types.hpp"
#include "ioer.hpp"

namespace misc{

    namespace crasher {

        template <typename ExceptType = std::runtime_error>
            inline void crash(BOOL_T condition, const STRING_T& info, ioer::output_t& out = ioer::STDOUT) 
            {
                if (condition) {
                    throw(ExceptType(info));
                }
            }

        template <typename ExceptType = std::runtime_error>
            inline void assert(BOOL_T condition, const STRING_T& info, ioer::output_t& out = ioer::STDOUT) 
            {
                crash<ExceptType>((not condition), info, out);
            }
    };

};


#endif // _CRASHER_HPP
