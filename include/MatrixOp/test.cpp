#include "misc/ioer.hpp"
#include "misc/vector.hpp"
#include "matrixop_config.hpp"
#include "matmat.hpp"
#include "matCmat.hpp"
#include "eig.hpp"
#include "scal.hpp"
#include "nrm.hpp"
#include "dot.hpp"
#include "inverse.hpp"
#include "solve.hpp"
using namespace std;

using T = double;
using T2 = double;

int main(int argc, char** argv) {
    vector<T> A{ 1,2,3,2,4,5,3,5,8 };
    vector<T> evt;
    vector<T2> eva;

    matrixop::hdiag(A, eva, evt);

    ioer::info("A ", A);
    ioer::info("eva ", eva);
    ioer::info("evt ", evt);

    matrixop::hdiag(A, eva);

    ioer::info("A ", A);
    ioer::info("eva ", eva);

    matrixop::hdiag_inplace(A, eva);

    ioer::info("A ", A);
    ioer::info("eva ", eva);

    matrixop::scal_inplace(A, T(2.5));
    ioer::info("A ", A);

    ioer::info(matrixop::scal(A, T(0.4)));
    ioer::info(matrixop::nrm2(A));
    ioer::info(matrixop::nrm(A));
    ioer::info(matrixop::dot(A, A));
    ioer::info(matrixop::dotc(A, A));

    auto invA = matrixop::inv(A);
    ioer::info("invA ", invA);
    ioer::info("A * invA ", matrixop::matmat(A, invA, sqrt(A.size())));

    vector<T> b{3,4,5};
    ioer::info("A ", A);
    ioer::info("b = ", b);
    ioer::info("solve AX=b, X = ", matrixop::solve(A, b));

    matrixop::solve_inplace(A, b);
    ioer::info("solve inplace AX=b, X = ", b);

    return 0;
}
