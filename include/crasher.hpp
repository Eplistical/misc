#ifndef _CRASHER_HPP
#define _CRASHER_HPP
/* module for crashes
 *
 * Gaohan
 */
#include <exception>
#include <string>
#include "types.hpp"

namespace crasher {
    using std::string;

    template <typename ExceptType = std::runtime_error>
        inline crash(bool condition, const string& info) 
        {
            if (condition) {
                throw(ExceptType(info));
            }
        }

};


#endif // _CRASHER_HPP
