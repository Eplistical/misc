#ifndef _MATRIXOP_IO_HPP
#define _MATRIXOP_IO_HPP

/*
 * matrix I/O operations
 */

#include <cmath>
#include <complex>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <string>
#include "ioer.hpp"

namespace matrixop {
    using std::vector;
    using std::string;

    template <typename T>
        void showmat(const string& tag, const T* Mat, int M, int N, ioer::output_t& out = ioer::STDOUT) 
        {
            /*
             * output an M*N matrix Mat named tag
             */
            out.info("# ", tag);
            out.info("# size: ", M, " * ", N);
            for (int i(0); i < M; ++i) {
                for (int j(0); j < N; ++j) {
                    out.info_nonewline(Mat[i + j * M], " ");
                }
                out.newline();
            }
        }

    template <typename T>
        void showmat(const string& tag, const vector<T>& Mat, int M, int N = -1, ioer::output_t& out = ioer::STDOUT) 
        {
            /*
             * output an M*N matrix Mat named tag
             *  if N = -1, then use N = Mat.size() / M
             */
            if (N == -1)
                N = Mat.size() / M;

            out.info("# ", tag);
            out.info("# size: ", M, " * ", N);
            for (int i(0); i < M; ++i) {
                for (int j(0); j < N; ++j) {
                    out.info_nonewline(Mat[i + j * M], " ");
                }
                out.newline();
            }
        }

    template <typename T>
        void showvec(const string& tag, const vector<T>& Vec, int M = -1, ioer::output_t& out = ioer::STDOUT) 
        {
            /*
             * output a vector named tag with size M 
             *  if M = -1, use M = Vec.size()
             */
            if (M == -1) {
                M = Vec.size();
            }

            out.info("# ", tag);
            out.info("# size: ", M);
            for (int i(0); i < M; ++i) {
                out.info_nonewline(Vec[i], " ");
            }
            out.newline();
        }

    template <typename T>
        void showvec(const string& tag, const T* Vec, int M, ioer::output_t& out = ioer::STDOUT) 
        {
            /*
             * output a vector named tag with size M 
             */
            out.info("# ", tag);
            out.info("# size: ", M);
            for (int i(0); i < M; ++i) {
                out.info_nonewline(Vec[i], " ");
            }
            out.newline();
        }
}

#endif
