#ifndef _CRASHER_HPP
#define _CRASHER_HPP
/* module for crashes
 *
 * Gaohan
 */
#include <exception>
#include <string>
#include "types.hpp"

namespace misc{

    namespace crasher {

        template <typename ExceptType = std::runtime_error>
            inline void crash(BOOL_T condition, const STRING_T& info) 
            {
                if (condition) {
                    throw(ExceptType(info));
                }
            }

        template <typename ExceptType = std::runtime_error>
            inline void confirm(BOOL_T condition, const STRING_T& info) 
            {
                crash<ExceptType>((not condition), info);
            }
    };

};


#endif // _CRASHER_HPP
