#ifndef _MATRIXOP_LAPACK_BASE_HPP
#define _MATRIXOP_LAPACK_BASE_HPP

#include <cmath>
#include <complex>
#include <vector>
#include <algorithm>


namespace matrixop {
	using std::complex;
	using std::vector;
	using std::conj;

	extern "C" {
		extern void dgemv_(const char*, const int*, const int*, const double*, const double*, const int*, const double*, const int*, const double*, double*, const int*);
		extern void zgemv_(const char*, const int*, const int*, const complex<double>*, const complex<double>*, const int*, const complex<double>*, const int*, const complex<double>*, complex<double>*, const int*);

		extern void dgemm_(const char*, const char*, const int*, const int*, const int*, const double*, const double*, const int*, const double*, const int*, const double*, double*, const int*);
		extern void zgemm_(const char*, const char*, const int*, const int*, const int*, const complex<double>*, const complex<double>*, const int*, const complex<double>*, const int*, const complex<double>*, complex<double>*, const int*);

		extern void dsyevd_(const char*, const char*, const int*, double*, const int*, double*, double*, const int*, int*, const int*, int*);
		extern void zheevd_(const char*, const char*, const int*, complex<double>*, const int*, double*, complex<double>*, const int*, double*, const int*, int*, const int*, int*);

		extern void dgetrf_(const int*, const int*, double*, const int*, int*, int*);
		extern void zgetrf_(const int*, const int*, complex<double>*, const int*, int*, int*);

		extern double ddot_(int*, const double*, const int*, const double*, const int*);
		extern complex<double> zdotc_(int*, const complex<double>*, const int*, const complex<double>*, const int*);

		extern void zgees_(const char*, const char*, bool (const complex<double>*), const int*, complex<double>*, const int*, int*, complex<double>*, complex<double>*, const int*, complex<double>*, const int*, double*, bool*, int* );
		bool f08pnf_(const complex<double>* p) { return true; }
	};

	static int ONE_i(1);
	static double ONE_d(1.0);
	static complex<double> ONE_z(1.0, 0.0);

	static int ZERO_i(0);
	static double ZERO_d(0.0);
	static complex<double> ZERO_z(0.0, 0.0);

	static complex<double> I_z(0.0, 1.0);
};

#endif // _MATRIXOP_LAPACK_BASE
