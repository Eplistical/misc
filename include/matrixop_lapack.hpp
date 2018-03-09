#ifndef _MATRIXOP_LAPACK_HPP
#define _MATRIXOP_LAPACK_HPP

#include <cmath>
#include <complex>
#include <vector>
#include <algorithm>

namespace matrixop {
    using std::complex;
    using std::vector;
    using std::conj;
    using std::move;
    using std::swap;

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
        const double* A_ptr = Mat.data();
        const double* X_ptr = Vec.data();

        int M = static_cast<int>(Mat.size() / N);

        vector<double> rst(N);
        double* Y_ptr = rst.data();
        int lda(M), incx(1), incy(1);

        dgemv("N", &M, &N, &alpha, A_ptr, &lda, 
                X_ptr, &incx, &beta, Y_ptr, &incy);

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
        const complex<double>* A_ptr = Mat.data();
        const complex<double>* X_ptr = Vec.data();

        int M = static_cast<int>(Mat.size() / N);

        vector< complex<double> > rst(N);
        complex<double>* Y_ptr = rst.data();
        int lda(M), incx(1), incy(1);

        zgemv("N", &M, &N, &alpha, A_ptr, &lda, 
                X_ptr, &incx, &beta, Y_ptr, &incy);

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
        int lda(M), ldb(K), ldc(M);

        dgemm("N", "N", &M, &N, &K, &alpha, 
                &Mat1[0], &lda, &Mat2[0], &ldb, 
                &beta, &rst[0], &ldc);

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
        const complex<double>* A_ptr = Mat1.data();
        const complex<double>* B_ptr = Mat2.data();

        int M = static_cast<int>(Mat1.size() / K);
        int N = static_cast<int>(Mat2.size() / K);

        vector< complex<double> > rst(M * N);
        complex<double>* C_ptr = rst.data();
        int lda(M), ldb(K), ldc(M);

        zgemm("N", "N", &M, &N, &K, &alpha, 
                A_ptr, &lda, B_ptr, &ldb, &beta, C_ptr, &ldc);

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
        int lda(M), ldb(K), ldc(M);

        dgemm("C", "N", &M, &N, &K, &alpha, 
                &Mat1[0], &lda, &Mat2[0], &ldb, 
                &beta, &rst[0], &ldc);

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
        const complex<double>* A_ptr = Mat1.data();
        const complex<double>* B_ptr = Mat2.data();

        int M = static_cast<int>(Mat1.size() / K);
        int N = static_cast<int>(Mat2.size() / K);

        vector< complex<double> > rst(M * N);
        complex<double>* C_ptr = rst.data();
        int lda(M), ldb(K), ldc(M);

        zgemm("C", "N", &M, &N, &K, &alpha, 
                A_ptr, &lda, B_ptr, &ldb, &beta, C_ptr, &ldc);

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

        const int N = static_cast<int>(sqrt(Mat.size()));
        vector<double> evt_(Mat);

        int lwork(-1), liwork(-1), info(-1);
        vector<double> work(1);
        vector<int> iwork(1);
        eva.resize(N);

        dsyevd(jobz, "L", &N, &evt_[0], &N, &eva[0], 
                &work[0], &lwork, &iwork[0], &liwork, &info);

        lwork = work[0];
        liwork = iwork[0];
        work.resize(lwork);
        iwork.resize(liwork);

        dsyevd(jobz, "L", &N, &evt_[0], &N, &eva[0], 
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

        const int N = static_cast<int>(sqrt(Mat.size()));
        vector< complex<double> > evt_(Mat);
        int lwork(-1), liwork(-1), lrwork(-1), info(-1);
        vector< complex<double> > work(1);
        vector<double> rwork(1);
        vector<int> iwork(1);
        eva.resize(N);

        zheevd(jobz, "L", &N, &evt_[0], &N, &eva[0], 
                &work[0], &lwork, &rwork[0], &lrwork, 
                &iwork[0], &liwork, &info);

        lwork = work[0].real();
        liwork = iwork[0];
        lrwork = rwork[0];
        work.resize(lwork);
        iwork.resize(liwork);
        rwork.resize(lrwork);

        zheevd(jobz, "L", &N, &evt_[0], &N, &eva[0], 
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
        const int N(nums.size());
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
        const int N = static_cast<int>(sqrt(Mat.size()));
        vector<double> A(Mat);
        vector<int> ipiv(N);
        int info(0);

        dgetrf(&N, &N, &A[0], &N, &ipiv[0], &info);

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
        const int N = static_cast<int>(sqrt(Mat.size()));
        vector< complex<double> > A(Mat);
        vector<int> ipiv(N);
        int info(0);

        zgetrf(&N, &N, &A[0], &N, &ipiv[0], &info);

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
        int inc(1);
        int N(len = -1 ? v1.size() : len);
        return ddot(&N, &v1[begin], &inc, &v2[begin], &inc);
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
        int inc(1);
        int N(len = -1 ? v1.size() : len);
        complex<double> rst;
        zdotc(&rst, &N, &v1[begin], &inc, &v2[begin], &inc);
        return rst;
    }

};

#endif
