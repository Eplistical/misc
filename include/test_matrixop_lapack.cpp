#include <cassert>
#include <cmath>
#include "ioer.hpp"
#include "vector.hpp"
#include "matrixop_lapack.hpp"
#include "matrixop_lapack.hpp"

using namespace std;

template <typename T> 
bool close_enough(const T& rst, const T& exact) {
    T err = rst - exact;
    double abs_err = sqrt(norm(err));
    double rel_err = abs_err / sqrt(norm(exact));
    return (rel_err < 1e-10 and abs_err < 1e-10);
}


int main(int argc, char** argv) {

    vector<double> eye { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

    vector<double> Ms { 1, 2, 3, 2, 5, 4, 3, 4, 7 };

    vector<double> M2 { 1, 2, 0, 7, 3, 9 };

    vector<double> v { 2.3, 5.3, 1.6 };

    // helpers
    assert(matrixop::is_identity(Ms, 3) == false);
    assert(matrixop::is_identity(eye, 3) == true);


    // multiplications
    vector<double> Msv = matrixop::matvec(Ms, v, 3);
    assert(close_enough(Msv, vector<double> {17.7, 37.5, 39.3}));

    vector<double> MsM2 = matrixop::matmat(Ms, M2, 3);
    assert(close_enough(MsM2, vector<double> {5,12,11,40,65,96}));

    vector<double> M2CMs = matrixop::matCmat(M2, Ms, 3);
    assert(close_enough(M2CMs, vector<double> {5,40,12,65,11,96}));


    // mlog
    vector<double> Mmlog {0.8, 0.6, -0.6, 0.8};
    ioer::info(Mmlog);
    ioer::info(matrixop::mlog(Mmlog, 2));



    return 0;
}

