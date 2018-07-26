#ifndef _MATRIXOP_LAPACK_HPP
#define _MATRIXOP_LAPACK_HPP

#include <cmath>
#include <complex>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "matrixop_lapack_base.hpp"

namespace matrixop {
	using std::complex;
	using std::vector;
	using std::conj;
	using std::move;
	using std::swap;


	// --- helpers --- //


	template <typename T>
		bool is_identity(const vector<T>& Mat, int N, double threash = 1e-10) 
		{
			/*
			 * check if a matrix is idenity
			 */
			for (int i(0); i < N; ++i) {
				for (int j(0); j < N; ++j) {
					if ((i == j and std::abs(Mat[i + j * N] - 1.0) > threash) or
							(i != j and std::abs(Mat[i + j * N]) > threash)) 
						return false;
				}
			}
			return true;
		}

	// --- multiplication for matrix / vectors --- //

	inline vector<double> matvec(
			const vector<double>& Mat,
			const vector<double>& Vec,
			int N, double alpha = 1.0)
	{
		/*  matrix-vector multiplication, 
		 *
		 * 	param Mat:  matrix with N cols
		 * 	param Vec:  matrix with N elements
		 *
		 */

		double beta(0.0);
		int M = static_cast<int>(Mat.size() / N);
		vector<double> rst(N);

		dgemv_("N", &M, &N, &alpha, 
				&Mat[0], &M, &Vec[0], &ONE_i,
				&beta, &rst[0], &ONE_i);

		return rst;
	}

	inline vector< complex<double> > matvec(
			const vector< complex<double> >& Mat,
			const vector< complex<double> >& Vec,
			int N, complex<double> alpha = 1.0)
	{
		/*  matrix-vector multiplication, 
		 *
		 * 	param Mat:  matrix with N cols
		 * 	param Vec:  matrix with N elements
		 *
		 */

		complex<double> beta(0.0, 0.0);
		int M = static_cast<int>(Mat.size() / N);
		vector< complex<double> > rst(N);

		zgemv_("N", &M, &N, &alpha, 
				&Mat[0], &M, &Vec[0], &ONE_i, 
				&beta, &rst[0], &ONE_i);

		return rst;
	}

	inline vector<double> matmat(
			const vector<double>& Mat1, 
			const vector<double>& Mat2,
			int K, double alpha = 1.0)
	{
		/*  matrix-matrix multiplication, 
		 *
		 * 	param Mat1: M * K matrix
		 * 	param Mat2: K * N matrix
		 *
		 */
		double beta(0.0);
		int M = static_cast<int>(Mat1.size() / K);
		int N = static_cast<int>(Mat2.size() / K);
		vector<double> rst(M * N);

		dgemm_("N", "N", &M, &N, &K, &alpha, 
				&Mat1[0], &M, &Mat2[0], &K, 
				&beta, &rst[0], &M);

		return rst;
	}

	inline vector< complex<double> > matmat(
			const vector< complex<double> >& Mat1, 
			const vector< complex<double> >& Mat2,
			int K, complex<double> alpha = 1.0)
	{
		/*  matrix-matrix multiplication, 
		 *
		 * 	param Mat1: matrix with K cols
		 * 	param Mat2: matrix with K rows
		 *
		 */
		complex<double> beta(0.0, 0.0);
		int M = static_cast<int>(Mat1.size() / K);
		int N = static_cast<int>(Mat2.size() / K);
		vector< complex<double> > rst(M * N);

		zgemm_("N", "N", &M, &N, &K, &alpha, 
				&Mat1[0], &M, &Mat2[0], &K, 
				&beta, &rst[0], &M);

		return rst;
	}

	inline vector<double> matCmat(
			const vector<double>& Mat1, 
			const vector<double>& Mat2,
			int K, double alpha = 1.0)
	{
		/*  matrix-matrix multiplication, 
		 *  asjoint(Mat1) * Mat2
		 *
		 * 	param Mat1: K * M matrix
		 * 	param Mat2: K * N matrix
		 *
		 */
		double beta(0.0);
		int M = static_cast<int>(Mat1.size() / K);
		int N = static_cast<int>(Mat2.size() / K);
		vector<double> rst(M * N);

		dgemm_("C", "N", &M, &N, &K, &alpha, 
				&Mat1[0], &K, &Mat2[0], &K, 
				&beta, &rst[0], &M);

		return rst;
	}


	inline vector< complex<double> > matCmat(
			const vector< complex<double> >& Mat1, 
			const vector< complex<double> >& Mat2,
			int K, complex<double> alpha = 1.0)
	{
		/*  matrix-matrix multiplication, 
		 *  asjoint(Mat1) * Mat2
		 *
		 * 	param Mat1: K * M matrix
		 * 	param Mat2: K * N matrix
		 *
		 */
		complex<double> beta(0.0, 0.0);
		int M = static_cast<int>(Mat1.size() / K);
		int N = static_cast<int>(Mat2.size() / K);
		vector< complex<double> > rst(M * N);

		zgemm_("C", "N", &M, &N, &K, &alpha, 
				&Mat1[0], &K, &Mat2[0], &K, 
				&beta, &rst[0], &M);

		return rst;
	}


	// --- calculate eigenvalues and/or eigenvectors --- //


	inline void hdiag_(const vector<double>& Mat, 
			vector<double>& eva, vector<double>& evt,
			const char* jobz)
	{
		/*  calc eva and/or evt for Mat, double version 
		 *
		 * 	param Mat:  N * N matrix
		 * 	param eva, evt: results
		 * 	param jobz: "N" or "V"
		 *
		 */

		int N = static_cast<int>(sqrt(Mat.size()));
		vector<double> evt_(Mat);

		int lwork(-1), liwork(-1), info(-1);
		vector<double> work(1);
		vector<int> iwork(1);
		eva.resize(N);

		dsyevd_(jobz, "L", &N, &evt_[0], &N, &eva[0], 
				&work[0], &lwork, &iwork[0], &liwork, &info);

		lwork = work[0];
		liwork = iwork[0];
		work.resize(lwork);
		iwork.resize(liwork);

		dsyevd_(jobz, "L", &N, &evt_[0], &N, &eva[0], 
				&work[0], &lwork, &iwork[0], &liwork, &info);

		evt = move(evt_);
	}


	inline void hdiag_(const vector< complex<double> >& Mat, 
			vector<double>& eva, vector< complex<double> >& evt,
			const char* jobz)
	{
		/*  calc eva and/or evt for Mat, complex<double> version 
		 *
		 * 	param Mat:  N * N matrix
		 * 	param eva, evt: results
		 * 	param jobz: "N" or "V"
		 *
		 */

		int N = static_cast<int>(sqrt(Mat.size()));
		vector< complex<double> > evt_(Mat);
		int lwork(-1), liwork(-1), lrwork(-1), info(-1);
		vector< complex<double> > work(1);
		vector<double> rwork(1);
		vector<int> iwork(1);
		eva.resize(N);

		zheevd_(jobz, "L", &N, &evt_[0], &N, &eva[0], 
				&work[0], &lwork, &rwork[0], &lrwork, 
				&iwork[0], &liwork, &info);

		lwork = work[0].real();
		liwork = iwork[0];
		lrwork = rwork[0];
		work.resize(lwork);
		iwork.resize(liwork);
		rwork.resize(lrwork);

		zheevd_(jobz, "L", &N, &evt_[0], &N, &eva[0], 
				&work[0], &lwork, &rwork[0], &lrwork, 
				&iwork[0], &liwork, &info);

		evt = move(evt_);
	}


	inline void hdiag(const vector<double>& Mat, 
			vector<double>& eva, vector<double>& evt)
	{
		/* calculate eva & evt for Mat
		*/
		hdiag_(Mat, eva, evt, "V");
	}


	inline void hdiag(const vector<double>& Mat, 
			vector<double>& eva)
	{
		/* calculate eva for Mat
		*/
		vector<double> evt;
		hdiag_(Mat, eva, evt, "N");
	}


	inline void hdiag(const vector< complex<double> >& Mat, 
			vector<double>& eva, vector< complex<double> >& evt)
	{
		/* calculate eva & evt for Mat
		*/
		hdiag_(Mat, eva, evt, "V");
	}


	inline void hdiag(const vector< complex<double> >& Mat, 
			vector<double>& eva)
	{
		/* calculate eva for Mat
		*/
		vector< complex<double> > evt;
		hdiag_(Mat, eva, evt, "N");
	}


	// -- adjoint / transpose -- //


	template <typename MatrixElementType> 
		inline vector<MatrixElementType> transpose(const vector<MatrixElementType>& Mat, int M, int N)
		{
			/* calculate the transpose matrix for Mat
			 *
			 *  param Mat: M * N matrix
			 */
			vector<MatrixElementType> rst(M * N);
			for (int r(0); r < M; ++r) {
				for (int c(0); c < N; ++c) {
					rst[c + r * N] = Mat[r + c * M];
				}
			}
			return rst;
		}


	inline vector<double> adjoint(const vector<double>& Mat, int M, int N)
	{
		return transpose(Mat, M, N);
	}


	inline vector< complex<double> > adjoint(const vector< complex<double> >& Mat, int M, int N)
	{
		/* calculate the adjoint matrix for Mat
		 *
		 *  param Mat: M * N matrix
		 */
		vector< complex<double> > rst(M * N);
		for (int r(0); r < M; ++r) {
			for (int c(0); c < N; ++c) {
				rst[c + r * N] = conj(Mat[r + c * M]);
			}
		}
		return rst;
	}


	// --- determinant --- //


	inline int per_sign(const vector<int>& nums)
	{
		int N(nums.size());
		vector<bool> visited(N, false);
		int rst(1), next(0), L(0);
		for (int k(1); k <= N; ++k) {
			if (!visited[k - 1]) {
				next = k;
				L = 0;
				while (!visited[next - 1]) {
					++L;
					visited[next - 1] = true;
					next = nums[next - 1]; 
				}
				if (L % 2 == 0) {
					rst *= -1; 
				}
			}
		}   
		return rst;
	}


	inline double det(const vector<double>& Mat)
	{
		/* calculate determinan of the matrix
		 *
		 *  param Mat: N * N matrix
		 */
		int N = static_cast<int>(sqrt(Mat.size()));
		vector<double> A(Mat);
		vector<int> ipiv(N);
		int info(0);

		dgetrf_(&N, &N, &A[0], &N, &ipiv[0], &info);

		vector<int> per(N);
		for (int i(1); i <= N; ++i) {
			per[i - 1] = i;
		}

		for (int i(1); i <= N; ++i) {
			swap(per[i - 1], per[ipiv[i - 1] - 1]);
		}

		double rst( per_sign(per) );
		for (int i(0); i < N; ++i) {
			rst *= A[i + i * N];
		}
		return rst;
	}


	inline complex<double> det(const vector< complex<double> >& Mat)
	{
		/* calculate determinan of the matrix
		 *
		 *  param Mat: N * N matrix
		 */
		int N = static_cast<int>(sqrt(Mat.size()));
		vector< complex<double> > A(Mat);
		vector<int> ipiv(N);
		int info(0);

		zgetrf_(&N, &N, &A[0], &N, &ipiv[0], &info);

		vector<int> per(N);
		for (int i(0); i < N; ++i) {
			per[i] = i + 1;
		}

		for (int i(0); i < N; ++i) {
			swap(per[i], per[ipiv[i] - 1]);
		}

		complex<double> rst(per_sign(per), 0.0);
		for (int i(0); i < N; ++i) {
			rst *= A[i + i * N];
		}
		return rst;
	}


	// --- innerproduct --- //


	inline double innerproduct(const vector<double>& v1, 
			const vector<double>& v2, 
			int begin = 0, int len = -1)
	{
		/* calculate innerproduct of two vectors:
		 * v1[begin:begin + len] and v2[begin:begin + len]
		 *
		 *  param v1, v2: vectors
		 *  param begin: begin position
		 *  param len: length of the vector of interest, if -1 then v1.size()
		 */
		int N((len == -1) ? v1.size() : len);
		return ddot_(&N, &v1[begin], &ONE_i, &v2[begin], &ONE_i);
	}


	inline complex<double> innerproduct(const vector< complex<double> >& v1, 
			const vector< complex<double> >& v2, 
			int begin = 0, int len = -1)
	{
		/* calculate innerproduct of two vectors:
		 * v1[begin:begin + len] and v2[begin:begin + len]
		 *
		 *  param v1, v2: vectors
		 *  param begin: begin position
		 *  param len: length of the vector of interest, if -1 then v1.size()
		 */
		int N((len == -1) ? v1.size() : len);
		complex<double> rst;
		return zdotc_(&N, &v1[begin], &ONE_i, &v2[begin], &ONE_i);
	}


    // --- inverse --- //


    inline void inv(vector<double>& Mat) 
    {
        // inplace inverse
        const int N(static_cast<int>(sqrt(Mat.size())));
        vector<int> ipiv(N);
        int info(0);

        dgetrf_(&N, &N, &Mat[0], &N, &ipiv[0], &info);

        vector<double> work(1);
        int lwork(-1);
        dgetri_(&N, &Mat[0], &N, &ipiv[0], &work[0], &lwork, &info);

        lwork = work[0];
        work.resize(lwork);
        dgetri_(&N, &Mat[0], &N, &ipiv[0], &work[0], &lwork, &info);
    }

    inline void inv(vector< complex<double> >& Mat) 
    {
        // inplace inverse
        const int N(static_cast<int>(sqrt(Mat.size())));
        vector<int> ipiv(N);
        int info(0);

        zgetrf_(&N, &N, &Mat[0], &N, &ipiv[0], &info);

        vector< complex<double> > work(1);
        int lwork(-1);
        zgetri_(&N, &Mat[0], &N, &ipiv[0], &work[0], &lwork, &info);

        lwork = work[0].real();
        work.resize(lwork);
        zgetri_(&N, &Mat[0], &N, &ipiv[0], &work[0], &lwork, &info);
    }


	// --- more advanced functions --- //


	template<typename T>
		inline vector<double> mpower(const vector<double>& Mat, T p, int N)
		{
			/*
			 * calculate matrix power Mat^p
			 *
			 * - Mat must be symmetric
			 */
			static vector<double> eva;
			static vector<double> evamat;
			static vector<double> evt;
			hdiag(Mat, eva, evt);
			// construct evamat
			evamat.resize(N * N);
			for (int i(0); i < N; ++i) {
				for (int j(0); j < N; ++j) {
					if (i == j) {
						if (p < 1.0 and eva[i] < 0.0) {
        					throw std::runtime_error("matrixop::mpower : negative eigenvalues encountered while p < 1.0");
						}
						evamat[i + j * N] = std::pow(eva[i], p);
					}
					else {
						evamat[i + j * N] = 0.0;
					}
				}
			}
			return matmat(evt, matmat(evamat, adjoint(evt, N, N), N), N);
		}


	// --- orthoginalization --- //


	inline vector<double> lowdin_orthogonalize(const vector<double>& Mat, int N) 
	{
		/*
		 * orthogonalize matrix with Lowdin algorithm
		 *
		 * U => U * (U^T * U)^(-1/2)
		 */
		vector<double> MM(matCmat(Mat, Mat, N));
		if (is_identity(MM, N)) {
			return Mat;
		}
		else {
			return matmat(Mat, mpower(MM, -0.5, N), N);
		}
	}


	// --- matrix log --- //


	inline vector<double> mlog(const vector<double>& Mat, int N) 
	{
		/* 
		 * calculate log(Mat)
		 * 
		 * - Mat must be orthogonal
		 * - All diagonal elements M[k,k] must be positive
		 */
		// check orthogonality
		if (not is_identity(matCmat(Mat, Mat, N), N)) 
        	throw std::runtime_error("matrixop::mlog : input matrix is not orthogonal!");
		// check positive elements
		for (int i(0); i < N; ++i) {
			if (Mat[i + i * N] <= 0.0)
        		throw std::runtime_error("matrixop::mlog : non-positive diagonal elements found!");
		}
		// convert double to complex
		static vector< complex<double> > A;
		A.resize(N * N);
		for (int i(0); i < A.size(); ++i) {
			A[i] = Mat[i];
		}
		// Schur decomposition A = Q * T * Q'
		static vector< complex<double> > w;
		static vector< complex<double> > work;
		static vector< complex<double> > vs;
		static vector<double> rwork;
		static bool bwork[1];
		int lwork, sdim, info;
		w.resize(N);
		vs.resize(N * N);
		rwork.resize(N);

		lwork = -1;
		work.resize(1);
		zgees_("V", "N", f08pnf_, &N, &A[0], &N, &sdim, 
				&w[0], &vs[0], &N, &work[0], &lwork, &rwork[0], &bwork[0], &info);

		lwork = static_cast<int>(work[0].real());
		work.resize(lwork);
		zgees_("V", "N", f08pnf_, &N, &A[0], &N, &sdim, 
				&w[0], &vs[0], &N, &work[0], &lwork, &rwork[0], &bwork[0], &info);
		// construct diagonal unitary matrix logD (stored in A)
		for (int i(0); i < N; ++i) {
			for (int j(0); j < N; ++j) {
				if (i == j) A[i + j * N] = std::log(A[i + j * N] / std::abs(A[i + j * N]));
				else A[i + j * N] = 0.0;
			}
		}
		// get Q * log(D) * Q'
		A = matmat(vs, matmat(A, adjoint(vs, N, N), N), N);
		// convert to double
		vector<double>rst(N * N);
		for (int i; i < rst.size(); ++i) {
			rst[i] = A[i].real();
		}
		return rst;
	}
};

#endif
