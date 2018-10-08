#ifndef _MATRIXOP_HDIAG_HPP
#define _MATRIXOP_HDIAG_HPP

/*  
 *  matrixop::hdiag(A, eva, [evt])
 *
 *  function for diaganalizing a Hermitian matrix A
 *
 *
 * 	param   A:  Hermitian matrix A (N*N)
 *
 * 	param eva:  result eigenvalues
 * 	param evt:  result eigenvectors
 *
 * the function detect the lower triangle of the matrix
 *
 ****************************************
 *
 *  matrixop::hdiag_inplace(A, eva)
 *
 *  function for inplace diaganalizing a Hermitian matrix A
 *
 *
 * 	param   A:  Hermitian matrix A (N*N)
 * 	            on exit, A is result eigenvectors
 *
 * 	param eva:  result eigenvalues
 *
 * the function detect the lower triangle of the matrix
 *
 */


#include <vector>
#include <cmath>
#include <algorithm>
#include "matrixop_config.hpp"

namespace matrixop {
	using std::sqrt;
	using std::copy;
	using std::vector;

    // single
	VOID _hdiag(STYPE* A, STYPE* eva, CNST_ITYPE N, CNST_CHAR jobz)
	{
		MATRIXOP_STATIC vector<STYPE> work;
		MATRIXOP_STATIC vector<ITYPE> iwork;

		ITYPE lwork(-1), liwork(-1), info(-1);
        work.resize(1);
        iwork.resize(1);

		SSYEVD(&jobz, &CHARL, &N, A, &N, eva, 
				&work[0], &lwork, &iwork[0], &liwork, &info);

		lwork = static_cast<ITYPE>(work[0]);
		liwork = iwork[0];
		work.resize(lwork);
		iwork.resize(liwork);

		SSYEVD(&jobz, &CHARL, &N, A, &N, eva, 
				&work[0], &lwork, &iwork[0], &liwork, &info);
	}

    // double
	VOID _hdiag(DTYPE* A, DTYPE* eva, CNST_ITYPE N, CNST_CHAR jobz)
	{
		MATRIXOP_STATIC vector<DTYPE> work;
		MATRIXOP_STATIC vector<ITYPE> iwork;

		ITYPE lwork(-1), liwork(-1), info(-1);
        work.resize(1);
        iwork.resize(1);

		DSYEVD(&jobz, &CHARL, &N, A, &N, eva, 
				&work[0], &lwork, &iwork[0], &liwork, &info);

		lwork = static_cast<ITYPE>(work[0]);
		liwork = iwork[0];
		work.resize(lwork);
		iwork.resize(liwork);

		DSYEVD(&jobz, &CHARL, &N, A, &N, eva, 
				&work[0], &lwork, &iwork[0], &liwork, &info);
	}

    // complex
	VOID _hdiag(CTYPE* A, STYPE* eva, CNST_ITYPE N, CNST_CHAR jobz)
	{
		MATRIXOP_STATIC vector<CTYPE> work;
		MATRIXOP_STATIC vector<STYPE> rwork;
		MATRIXOP_STATIC vector<ITYPE> iwork;

		ITYPE lwork(-1), liwork(-1), lrwork(-1), info(-1);
        work.resize(1);
        rwork.resize(1);
        iwork.resize(1);

		CHEEVD(&jobz, &CHARL, &N, A, &N, eva, 
				&work[0], &lwork, &rwork[0], &lrwork, 
				&iwork[0], &liwork, &info);

		lwork = static_cast<ITYPE>(work[0].real());
		liwork = iwork[0];
		lrwork = rwork[0];
		work.resize(lwork);
		iwork.resize(liwork);
		rwork.resize(lrwork);

		CHEEVD(&jobz, &CHARL, &N, A, &N, eva, 
				&work[0], &lwork, &rwork[0], &lrwork, 
				&iwork[0], &liwork, &info);
	}

    // complex*16
	VOID _hdiag(ZTYPE* A, DTYPE* eva, CNST_ITYPE N, CNST_CHAR jobz)
	{
		MATRIXOP_STATIC vector<ZTYPE> work(1);
		MATRIXOP_STATIC vector<DTYPE> rwork(1);
		MATRIXOP_STATIC vector<ITYPE> iwork(1);

		ITYPE lwork(-1), liwork(-1), lrwork(-1), info(-1);
        work.resize(1);
        rwork.resize(1);
        iwork.resize(1);

		ZHEEVD(&jobz, &CHARL, &N, A, &N, eva, 
				&work[0], &lwork, &rwork[0], &lrwork, 
				&iwork[0], &liwork, &info);

		lwork = static_cast<ITYPE>(work[0].real());
		liwork = iwork[0];
		lrwork = rwork[0];
		work.resize(lwork);
		iwork.resize(liwork);
		rwork.resize(lrwork);

		ZHEEVD(&jobz, &CHARL, &N, A, &N, eva, 
				&work[0], &lwork, &rwork[0], &lrwork, 
				&iwork[0], &liwork, &info);
	}

    // interfaces
    template <typename T1, typename T2>
        VOID hdiag(const vector<T1>& A, vector<T2>& eva, vector<T1>& evt)
        {
            CNST_ITYPE N(static_cast<ITYPE>(sqrt(A.size())));
		    eva.resize(N);
            evt.resize(A.size());
            copy(A.begin(), A.end(), evt.begin());

            _hdiag(&evt[0], &eva[0], N, CHARV);
        }

    template <typename T1, typename T2>
        VOID hdiag(const vector<T1>& A, vector<T2>& eva)
        {
		    MATRIXOP_STATIC vector<T1> evt(1);

            CNST_ITYPE N(static_cast<ITYPE>(sqrt(A.size())));
		    eva.resize(N);
            evt.resize(A.size());
            copy(A.begin(), A.end(), evt.begin());

            _hdiag(&evt[0], &eva[0], N, CHARN);
        }

    template <typename T1, typename T2>
        VOID hdiag_inplace(vector<T1>& A, vector<T2>& eva)
        {
            CNST_ITYPE N(static_cast<ITYPE>(sqrt(A.size())));
		    eva.resize(N);
            _hdiag(&A[0], &eva[0], N, CHARV);
        }

};

#endif // _MATRIXOP_HDIAG_HPP
