#ifndef _SPARSEMAT_HPP
#define _SPARSEMAT_HPP

#include <cmath>
#include <complex>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "misc/crasher.hpp"

namespace matrixop {

    template <typename EleType, typename IdxType>
        void mat2sp(const std::vector<EleType>& Mat, const size_t M, const size_t N,
                std::vector<EleType>& A, std::vector<IdxType>& IA, std::vector<IdxType>& JA, 
                const std::string& fmt = "C") 
        {
            /*
             * convert a dense matrix Mat to sparse matrix A, IA, JA
             * Mat is of shape M * N
             */
            misc::crasher::confirm<std::out_of_range>(fmt == "C" or fmt == "F", "mat2sp: fmt invalid, must be C or F!");
            misc::crasher::confirm<>(Mat.size() >= M * N, "mat2sp: invalid Mat size, M * N < Mat size!");

            int nonz(0);

            // determine vectors' size 
            for (size_t i(0), MN(M*N); i < MN; ++i) {
                if (Mat[i] != static_cast<EleType>(0)) 
                    nonz += 1; 
            }

            A.clear();
            A.reserve(nonz);
            JA.clear();
            JA.reserve(nonz);
            IA.clear();
            IA.reserve(M+1);

            // determine offset w/ fmt
            IdxType offset;
            if (fmt == "C") 
                offset = 0;
            else if (fmt == "F")
                offset = 1;

            // construct A, IA, JA
            IA.push_back(0 + offset);
            for (size_t i(0); i < M; ++i) {
                IA.push_back(IA[i]);

                for (size_t j(0); j < N; ++j) {
                    if (Mat[i + j * M] != static_cast<EleType>(0)) {
                        A.push_back(Mat[i + j * M]);
                        JA.push_back(j + offset);
                        IA[i+1] += 1;
                    }
                }
            }
        }

    template <typename EleType, typename IdxType>
        void sp2mat(const std::vector<EleType>& A, const std::vector<IdxType>& IA, const std::vector<IdxType>& JA, 
                std::vector<EleType>& Mat, const size_t M, const size_t N,
                const std::string& fmt = "C") 
        {
            /*
             * convert a sparse matrix A, IA, JA to dense matrix Mat 
             * Mat is of shape M * N
             */
            misc::crasher::confirm<std::out_of_range>(fmt == "C" or fmt == "F", "sp2mat: fmt invalid, must be C or F!");
            misc::crasher::confirm<>(IA.size() == M + 1, "sp2mat: invalid Mat size, M * N < Mat size!");
            misc::crasher::confirm<>(JA.size() == A.size(), "sp2mat: JA and A have different sizes!");
            Mat.assign(M * N, static_cast<EleType>(0));

            IdxType offset;
            if (fmt == "C") 
                offset = 0;
            else if (fmt == "F")
                offset = 1;

            int idx(0);
            for (int i(0); i < M; ++i) {
                int count(IA[i+1] - IA[i]);
                for (int j(0); j < count; ++j) {
                    Mat[i + (JA[idx] - offset) * M] = A[idx];
                    idx += 1;
                }
            }
        }
};

#endif
