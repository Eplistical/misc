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
 */


#include <vector>
#include <cmath>
#include "matrixop_config.hpp"

namespace matrixop {
	using std::sqrt;
	using std::vector;

    // single
	VOID _hdiag(const vector<STYPE>& A, vector<STYPE>& eva, vector<STYPE>& evt, CNST_CHAR jobz)
	{
		MATRIXOP_STATIC vector<STYPE> work;
		MATRIXOP_STATIC vector<ITYPE> iwork;

		CNST_ITYPE N(static_cast<ITYPE>(sqrt(A.size())));
		ITYPE lwork(-1), liwork(-1), info(-1);
        work.resize(1);
        iwork.resize(1);

		eva.resize(N);

        if (jobz == CHARN) {
            evt.resize(1);
        }
        else {
            ITYPE N2(A.size());
            evt.resize(N2);
            SCOPY(&N2, &A[0], &ONEI, &evt[0], &ONEI);
        }

		SSYEVD(&jobz, &CHARL, &N, &evt[0], &N, &eva[0], 
				&work[0], &lwork, &iwork[0], &liwork, &info);

		lwork = static_cast<ITYPE>(work[0]);
		liwork = iwork[0];
		work.resize(lwork);
		iwork.resize(liwork);

		SSYEVD(&jobz, &CHARL, &N, &evt[0], &N, &eva[0], 
				&work[0], &lwork, &iwork[0], &liwork, &info);
	}

    // double
	VOID _hdiag(const vector<DTYPE>& A, vector<DTYPE>& eva, vector<DTYPE>& evt, CNST_CHAR jobz)
	{
		MATRIXOP_STATIC vector<DTYPE> work;
		MATRIXOP_STATIC vector<ITYPE> iwork;

		CNST_ITYPE N(static_cast<ITYPE>(sqrt(A.size())));
		ITYPE lwork(-1), liwork(-1), info(-1);
        work.resize(1);
        iwork.resize(1);

		eva.resize(N);

        if (jobz == CHARN) {
            evt.resize(1);
        }
        else {
            ITYPE N2(A.size());
            evt.resize(N2);
            DCOPY(&N2, &A[0], &ONEI, &evt[0], &ONEI);
        }

		DSYEVD(&jobz, &CHARL, &N, &evt[0], &N, &eva[0], 
				&work[0], &lwork, &iwork[0], &liwork, &info);

		lwork = static_cast<ITYPE>(work[0]);
		liwork = iwork[0];
		work.resize(lwork);
		iwork.resize(liwork);

        ioer::tabout(jobz, CHARL, N);
		DSYEVD(&jobz, &CHARL, &N, &evt[0], &N, &eva[0], 
				&work[0], &lwork, &iwork[0], &liwork, &info);

	}

    // complex
    VOID _hdiag(const vector<CTYPE>& A, vector<STYPE>& eva, vector<CTYPE>& evt, CNST_CHAR jobz)
	{
		MATRIXOP_STATIC vector<CTYPE> work;
		MATRIXOP_STATIC vector<STYPE> rwork;
		MATRIXOP_STATIC vector<ITYPE> iwork;

		CNST_ITYPE N(static_cast<ITYPE>(sqrt(A.size())));
		ITYPE lwork(-1), liwork(-1), lrwork(-1), info(-1);
        work.resize(1);
        rwork.resize(1);
        iwork.resize(1);

		eva.resize(N);

        if (jobz == CHARN) {
            evt.resize(1);
        }
        else {
            ITYPE N2(A.size());
            evt.resize(N2);
            CCOPY(&N2, &A[0], &ONEI, &evt[0], &ONEI);
        }

		CHEEVD(&jobz, &CHARL, &N, &evt[0], &N, &eva[0], 
				&work[0], &lwork, &rwork[0], &lrwork, 
				&iwork[0], &liwork, &info);

		lwork = static_cast<ITYPE>(work[0].real());
		liwork = iwork[0];
		lrwork = rwork[0];
		work.resize(lwork);
		iwork.resize(liwork);
		rwork.resize(lrwork);

		CHEEVD(&jobz, &CHARL, &N, &evt[0], &N, &eva[0], 
				&work[0], &lwork, &rwork[0], &lrwork, 
				&iwork[0], &liwork, &info);
	}

    // complex*16
    VOID _hdiag(const vector<ZTYPE>& A, vector<DTYPE>& eva, vector<ZTYPE>& evt, CNST_CHAR jobz)
	{
		MATRIXOP_STATIC vector<ZTYPE> work(1);
		MATRIXOP_STATIC vector<DTYPE> rwork(1);
		MATRIXOP_STATIC vector<ITYPE> iwork(1);

		CNST_ITYPE N(static_cast<ITYPE>(sqrt(A.size())));
		ITYPE lwork(-1), liwork(-1), lrwork(-1), info(-1);
        work.resize(1);
        rwork.resize(1);
        iwork.resize(1);

		eva.resize(N);

        if (jobz == CHARN) {
            evt.resize(1);
        }
        else {
            ITYPE N2(A.size());
            evt.resize(N2);
            ZCOPY(&N2, &A[0], &ONEI, &evt[0], &ONEI);
        }

		ZHEEVD(&jobz, &CHARL, &N, &evt[0], &N, &eva[0], 
				&work[0], &lwork, &rwork[0], &lrwork, 
				&iwork[0], &liwork, &info);

		lwork = static_cast<ITYPE>(work[0].real());
		liwork = iwork[0];
		lrwork = rwork[0];
		work.resize(lwork);
		iwork.resize(liwork);
		rwork.resize(lrwork);

		ZHEEVD(&jobz, &CHARL, &N, &evt[0], &N, &eva[0], 
				&work[0], &lwork, &rwork[0], &lrwork, 
				&iwork[0], &liwork, &info);
	}

    // interfaces
    template <typename MatType, typename EvaType>
        VOID hdiag(const MatType& A, EvaType& eva, MatType& evt)
        {
            _hdiag(A, eva, evt, CHARV);
        }

    template <typename MatType, typename EvaType>
        VOID hdiag(const MatType& A, EvaType& eva)
        {
		    MATRIXOP_STATIC MatType evt;

            _hdiag(A, eva, evt, CHARN);
        }

};

#endif // _MATRIXOP_HDIAG_HPP
