#include "misc/ioer.hpp"
#include <complex>
#include "misc/vector.hpp"
#include "matvec.hpp"
#include "matmat.hpp"
#include "matCmat.hpp"
#include "hdiag.hpp"

using namespace std;
using T0 = float;
//using T = complex<T0>;
using T = T0;

int main() {
    vector<T> A {1,3,5,3,6,9,5,9,7};
    vector<T> B {1,2,3,4,5,6};
    vector<T> V {4,8,2};

    ioer::info(A);
    ioer::info(B);
    ioer::info(V);
    ioer::info(matrixop::matvec(A, V));
    ioer::info(matrixop::matmat(A, B, 3));
    ioer::info(matrixop::matCmat(B, A, 3));

    vector<T> evt;
    vector<T0> eva;
    matrixop::hdiag(A, eva, evt);

    ioer::info(eva);
    ioer::info(evt);

    return 0;
}
