#include <limits>
#include <cstddef>
#include <string>
#include <complex>
#include <deque>
#include <forward_list>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include "ioer.hpp"

using namespace std;
using namespace ioer;

int main(int argc, char** argv){
    output_t STDOUT;
    output_t F1("1.txt", ios::out);
    output_t F2("2.txt", ios::out);

    char _a87deb01c5f539e6bda34829c8ef2368 = numeric_limits<char>::max();
    int _fa7153f7ed1cb6c0fcf2ffb2fac21748 = numeric_limits<int>::max();
    float _546ade640b6edfbc8a086ef31347e768 = numeric_limits<float>::max();
    uint64_t _d667826d9ab05c9e36a7ec04b54f6ad9 = numeric_limits<uint64_t>::max();
    double _e8cd7da078a86726031ad64f35f5a6c0 = numeric_limits<double>::max();
    long _0f5264038205edfb1ac05fbb0e8c5e94 = numeric_limits<long>::max();
    vector<char> _b771f7d8b93a2c7077b637dccc6f8272 = {numeric_limits<char>::max(), numeric_limits<char>::min(), (numeric_limits<char>::max(), numeric_limits<char>::min()) / 2};
    forward_list<int> _902f3601f9bf7f377bf82ca305e59a95 = {numeric_limits<int>::max(), numeric_limits<int>::min(), (numeric_limits<int>::max(), numeric_limits<int>::min()) / 2};
    list<float> _8d1b7454f5852530464ac1e0fdb0076f = {numeric_limits<float>::max(), numeric_limits<float>::min(), (numeric_limits<float>::max(), numeric_limits<float>::min()) / 2};
    deque<uint64_t> _c751c100523c548a292fdc810d3c7d8b = {numeric_limits<uint64_t>::max(), numeric_limits<uint64_t>::min(), (numeric_limits<uint64_t>::max(), numeric_limits<uint64_t>::min()) / 2};
    vector<double> _b88ecf5a14345bea7f1d922583fc4407 = {numeric_limits<double>::max(), numeric_limits<double>::min(), (numeric_limits<double>::max(), numeric_limits<double>::min()) / 2};
    string _str = "string";
    complex<double> _cplx(1.0, 4.0);


    STDOUT.info(
    _a87deb01c5f539e6bda34829c8ef2368,
    _fa7153f7ed1cb6c0fcf2ffb2fac21748,
    _546ade640b6edfbc8a086ef31347e768,
    _d667826d9ab05c9e36a7ec04b54f6ad9,
    _e8cd7da078a86726031ad64f35f5a6c0,
    _0f5264038205edfb1ac05fbb0e8c5e94,
    _a87deb01c5f539e6bda34829c8ef2368,
    _fa7153f7ed1cb6c0fcf2ffb2fac21748,
    _546ade640b6edfbc8a086ef31347e768,
    _d667826d9ab05c9e36a7ec04b54f6ad9,
    _e8cd7da078a86726031ad64f35f5a6c0,
    _str,
    _cplx,
	"abcdefg"
    );

    F1.info(
    _a87deb01c5f539e6bda34829c8ef2368,
    _fa7153f7ed1cb6c0fcf2ffb2fac21748,
    _546ade640b6edfbc8a086ef31347e768,
    _d667826d9ab05c9e36a7ec04b54f6ad9,
    _e8cd7da078a86726031ad64f35f5a6c0,
    _0f5264038205edfb1ac05fbb0e8c5e94,
    _a87deb01c5f539e6bda34829c8ef2368,
    _fa7153f7ed1cb6c0fcf2ffb2fac21748,
    _546ade640b6edfbc8a086ef31347e768,
    _d667826d9ab05c9e36a7ec04b54f6ad9,
    _e8cd7da078a86726031ad64f35f5a6c0,
    _str,
    _cplx,
	"abcdefg"
    );

    F2.tabout(
    _a87deb01c5f539e6bda34829c8ef2368,
    _fa7153f7ed1cb6c0fcf2ffb2fac21748,
    _546ade640b6edfbc8a086ef31347e768,
    _d667826d9ab05c9e36a7ec04b54f6ad9,
    _e8cd7da078a86726031ad64f35f5a6c0,
    _0f5264038205edfb1ac05fbb0e8c5e94,
    _a87deb01c5f539e6bda34829c8ef2368,
    _fa7153f7ed1cb6c0fcf2ffb2fac21748,
    _546ade640b6edfbc8a086ef31347e768,
    _d667826d9ab05c9e36a7ec04b54f6ad9,
    _e8cd7da078a86726031ad64f35f5a6c0,
    _str,
    _cplx,
	"abcdefg"
    );

    F2.close();
    return 0;
}

