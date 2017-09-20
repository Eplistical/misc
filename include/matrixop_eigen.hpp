#ifndef _MATRIXOP_HPP
#define _MATRIXOP_HPP
/* module for matrix opeations
 * require C++11
 * written based on vector.hpp
 * using external lib: 
 * 	Eigen
 *
 * Gaohan
 */

#include <cmath>
#include <cassert>
#include "vector.hpp"
#include "Eigen/Eigenvalues"
#include "Eigen/Core"

namespace matrixop {
	using namespace Eigen;
	using namespace std;

    template<typename MatrixElementType>
        inline Matrix<MatrixElementType, Dynamic, Dynamic> VecToEigen(const vector<MatrixElementType>& Vec, int Nrow, int Ncol)
        {
            /* convert a vector to Nrow * Ncol Eigen Matrix (or vector)
             *
             *  param Vec: original vector
             *  param Nrow, Ncol: shape of desired matrix
             * */
            assert(Vec.size() >= Nrow * Ncol);
			Map< const Matrix<MatrixElementType, Dynamic, Dynamic> > rst(Vec.data(), Nrow, Ncol);
            return rst;
        }

    template<typename MatrixElementType, typename EigenMatType>
        inline vector<MatrixElementType> EigenToVec(const EigenMatType& EigenMat)
        {
            /* convert an Eigen Matrix to vector
             *
             *  param EigenMat: Eigen Matrix to convert
             * */
			return vector<MatrixElementType>(EigenMat.data(), EigenMat.data() + EigenMat.size());
        }

	template<typename MatrixElementType, typename EigenValType, typename EigenVecType>
		inline void hdiag(const vector<MatrixElementType>& MatrixToDiag, 
								vector<EigenValType>& EigenVal, 
								vector<EigenVecType>& EigenVec)
		{
			/* diag a symmetric matrix
			 *
			 * 	param MatrixToDiag: matrix to be diag, column-major
			 * 	param EignVal, EigenVac: vector to store results
			 * */ 
			int N = static_cast<int>(sqrt(MatrixToDiag.size()));
			SelfAdjointEigenSolver< Matrix<MatrixElementType, Dynamic, Dynamic> > 
                es(VecToEigen(MatrixToDiag, N, N));

			EigenVec = EigenToVec<EigenVecType>(es.eigenvectors());
			EigenVal = EigenToVec<EigenValType>(es.eigenvalues());
		}

	template<typename MatrixElementType>
		inline vector<MatrixElementType> _matmat(
				 const vector<MatrixElementType>& Mat1, 
				 const vector<MatrixElementType>& Mat2,
				 int M, int N, int K)
		{
			/*  matrix-matrix multiplication, 
			 *  should not be called by external functions
			 *
			 * 	param Mat1: matrix of M * N shape
			 * 	param Mat2: matrix of N * K shape
			 * 	param M, N, K: dimensions of matrices
			 *
			 * 	return a std::vector storing resulting M * K matrix
			 * */ 
            Matrix<MatrixElementType, Dynamic, Dynamic> rst = VecToEigen(Mat1, M, N) * VecToEigen(Mat2, N, K);
            return EigenToVec<MatrixElementType>(rst);
		}

	template<typename MatrixElementType>
		inline vector<MatrixElementType> matmat( 
				const vector<MatrixElementType>& Mat1, 
				const vector<MatrixElementType>& Mat2,
				int N)
		{
			/*  matrix-matrix multiplication, 
			 *
			 * 	param Mat1: matrix with N cols
			 * 	param Mat2: matrix with N rows
			 * 	param N:	col number for Mat1 
			 *
			 * 	return a std::vector storing resulting M * K matrix
			 * */ 
			int M = static_cast<int>(Mat1.size() / N);
			int K = static_cast<int>(Mat2.size() / N);
			return _matmat(Mat1, Mat2, M, N, K);
		}

	template<typename MatrixElementType>
		inline vector<MatrixElementType> matvec( 
				const vector<MatrixElementType>& Mat, 
				const vector<MatrixElementType>& Vec)
		{
			/*  matrix-matrix multiplication, 
			 *
			 * 	param Mat: matrix with M * N cols
			 * 	param Vec: vector with N elements
			 *
			 * 	return a std::vector with M elements
			 * */ 
			int N = static_cast<int>(Vec.size());
			int M = static_cast<int>(Mat.size() / N);
			return _matmat(Mat, Vec, M, N, 1);
		}

    template<typename MatrixElementType>
        inline vector<MatrixElementType> adjoint(const vector<MatrixElementType>& Mat, int Nrow, int Ncol)
        {
            Matrix<MatrixElementType, Dynamic, Dynamic> rst = VecToEigen(Mat, Nrow, Ncol);
            rst. adjointInPlace();
            return EigenToVec<MatrixElementType>(rst);
        }
};

#endif // _MATRIXOP_HPP
