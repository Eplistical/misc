#include "misc/ioer.hpp"
#include "misc/vector.hpp"
#include "matrixop_config.hpp"
#include "matvec.hpp"
#include "matCvec.hpp"
#include "matmat.hpp"
#include "matCmat.hpp"
#include "matmatC.hpp"
#include "matCmatC.hpp"
#include "eig.hpp"
#include "scal.hpp"
#include "nrm.hpp"
#include "dot.hpp"
#include "inverse.hpp"
#include "solve.hpp"
#include "eye.hpp"
#include "zeros.hpp"
#include "logm.hpp"
#include "lowdin.hpp"
using namespace std;

using T = complex<double>;
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

    ioer::info("eye: ", matrixop::eye<double>(2,3));
    ioer::info("zero: ", matrixop::zeros<double>(2,3));

    A = invA;
    ioer::info("A = ", A);
    ioer::info("b = ", b);
    ioer::info("A * b = ", matrixop::matvec(A, b));
    ioer::info("A'* b = ", matrixop::matCvec(A, b));

    vector<T> C{ 1,8,3,0,4,1,2,5,3};
    ioer::info("C = ", C);
    ioer::info("A * C = ", matrixop::matmat(A, C, 3));
    ioer::info("A'* C = ", matrixop::matCmat(A, C, 3));
    ioer::info("A * C'= ", matrixop::matmatC(A, C, 3));
    ioer::info("A'* C'= ", matrixop::matCmatC(A, C, 3));

    ioer::info("logm:");
    A = vector<T> { 1.0, -2.0, 2.0, 3.0 };
    ioer::info("A = ", A);
    A = matrixop::lowdin(A, 2);
    ioer::info("oth A = ", A);
    A = matrixop::logmh(A);
    ioer::info("log(oth A) = ", A);

    return 0;
}
