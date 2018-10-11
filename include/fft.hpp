#ifndef _FFT_HPP
#define _FFT_HPP
/* fast Fourier transform functions
 *
 * fft:  Yk = \sum_j^{N-1} Xj * exp(-1i * 2 * pi / N * j * k)
 * ifft: Yk = \sum_j^{N-1} Xj * exp(1i * 2 * pi / N * j * k)
 *
 */

#include <cmath>
#include <vector>
#include <complex>
#include <algorithm>
#include "crasher.hpp"
#include "fftw3.h"
#include "types.hpp"

namespace misc {

    // -- FFTW wrappers -- //

    VOID_T _fft(const COMPLEX_T* in, COMPLEX_T* out, const int rank, const INT_T* N) {
        /* fast fourier transform
         *
         *  param     in: complex input pointer
         *  param    out: complex output pointer
         *  param   rank: dimension of fft
         *  param      N: length of array on each dimension
         *
         */
        fftw_plan my_plan;
        COMPLEX_T* in_cast(const_cast<COMPLEX_T*>(in));

        my_plan = fftw_plan_dft(    rank, N, 
                                    reinterpret_cast<fftw_complex*>(in_cast), 
                                    reinterpret_cast<fftw_complex*>(out), 
                                    FFTW_FORWARD, FFTW_ESTIMATE
                                    );

        fftw_execute(my_plan);
        fftw_destroy_plan(my_plan);
    }

    VOID_T _fft(const DOUBLE_T* in, COMPLEX_T* out, const INT_T rank, const INT_T* N) {
        /* fast fourier transform, r2c
         *
         *  param     in: double input pointer
         *  param    out: complex output pointer
         *  param   rank: dimension of fft
         *  param      N: length of array on each dimension
         *
         */
        fftw_plan my_plan;
        DOUBLE_T* in_cast(const_cast<DOUBLE_T*>(in));
        my_plan = fftw_plan_dft_r2c(    rank, N, 
                                        in_cast,
                                        reinterpret_cast<fftw_complex*>(out), 
                                        FFTW_ESTIMATE
                                        );
        fftw_execute(my_plan);
        fftw_destroy_plan(my_plan);
    }

    VOID_T _ifft(const COMPLEX_T* in, COMPLEX_T* out, const INT_T rank, const INT_T* N) {
        /* inverse fast fourier transform
         *
         *  param     in: complex input pointer
         *  param    out: complex output pointer
         *  param   rank: dimension of fft
         *  param      N: length of array on each dimension
         *
         */
        fftw_plan my_plan;
        COMPLEX_T* in_cast(const_cast<COMPLEX_T*>(in));
        my_plan = fftw_plan_dft(    rank, N, 
                                    reinterpret_cast<fftw_complex*>(in_cast), 
                                    reinterpret_cast<fftw_complex*>(out), 
                                    FFTW_BACKWARD, FFTW_ESTIMATE
                                    );
        fftw_execute(my_plan);
        fftw_destroy_plan(my_plan);
    }

    VOID_T _ifft(const COMPLEX_T* in, DOUBLE_T* out, const INT_T rank, const INT_T* N) {
        /* inverse fast fourier transform, c2r
         *
         *  param     in: complex input pointer
         *  param    out: double output pointer
         *  param   rank: dimension of fft
         *  param      N: length of array on each dimension
         *
         */
        fftw_plan my_plan;
        COMPLEX_T* in_cast(const_cast<COMPLEX_T*>(in));
        my_plan = fftw_plan_dft_c2r(    rank, N, 
                                        reinterpret_cast<fftw_complex*>(in_cast), 
                                        out,
                                        FFTW_ESTIMATE
                                        );
        fftw_execute(my_plan);
        fftw_destroy_plan(my_plan);
    }

    // -- interfaces -- //
    
    // 1d fft
    template <typename T>
        std::vector<COMPLEX_T> fft(const std::vector<T>& in) {
            const INT_T N(in.size());
            crasher::confirm<> (in.size() >= N, "fft: insufficient data in the array!");

            std::vector<COMPLEX_T> out(N);
            _fft(&in[0], &out[0], 1, &N);
            return out;
        }

    // nd fft
    template <typename T>
        std::vector<COMPLEX_T> fftn(const std::vector<T>& in, const std::vector<INT_T>& N) {
            const INT_T rank(N.size());
            SIZE_T Ntot(1);
            for (INT_T i(0); i < rank; ++i) {
                Ntot *= N[i];
            }

            crasher::confirm<> (in.size() >= Ntot, "fftn: insufficient data in the array!");

            std::vector<COMPLEX_T> out(in.size());

            /*
            std::vector<INT_T> N_rev(N);
            std::reverse(N_rev.begin(), N_rev.end());
            _fft(&in[0], &out[0], rank, &N_rev[0]);
            */

            _fft(&in[0], &out[0], rank, &N[0]);

            return out;
        }

    // 1d ifft
    std::vector<COMPLEX_T> ifft(const std::vector<COMPLEX_T>& in) {
        const INT_T N(in.size());
        crasher::confirm<> (in.size() >= N, "ifft: insufficient data in the array!");

        std::vector<COMPLEX_T> out(N);
        _ifft(&in[0], &out[0], 1, &N);

        // normalize
        for (SIZE_T i(0); i < N; ++i) {
            out[i] /= static_cast<DOUBLE_T>(N);
        }

        return out;
    }

    std::vector<DOUBLE_T> irfft(const std::vector<COMPLEX_T>& in) {
        const INT_T N(in.size());
        crasher::confirm<> (in.size() >= N, "irfft: insufficient data in the array!");

        std::vector<DOUBLE_T> out(N);
        _ifft(&in[0], &out[0], 1, &N);

        // normalize
        for (SIZE_T i(0); i < N; ++i) {
            out[i] /= static_cast<DOUBLE_T>(N);
        }

        return out;
    }

    // nd ifft
    std::vector<COMPLEX_T> ifftn(const std::vector<COMPLEX_T>& in, const std::vector<INT_T>& N) {
        const INT_T rank(N.size());
        SIZE_T Ntot(1);
        for (INT_T i(0); i < rank; ++i) {
            Ntot *= N[i];
        }

        crasher::confirm<> (in.size() >= Ntot, "ifftn: insufficient data in the array!");

        std::vector<COMPLEX_T> out(in.size());

        /*
        std::vector<INT_T> N_rev(N);
        std::reverse(N_rev.begin(), N_rev.end());
        _ifft(&in[0], &out[0], rank, &N_rev[0]);
        */

        _fft(&in[0], &out[0], rank, &N[0]);

        // normalize
        for (SIZE_T i(0); i < Ntot; ++i) {
            out[i] /= static_cast<DOUBLE_T>(Ntot);
        }

        return out;
    }

    std::vector<DOUBLE_T> irfftn(const std::vector<COMPLEX_T>& in, const std::vector<INT_T>& N) {
        const INT_T rank(N.size());
        SIZE_T Ntot(1);
        for (INT_T i(0); i < rank; ++i) {
            Ntot *= N[i];
        }

        crasher::confirm<> (in.size() >= Ntot, "irfftn: insufficient data in the array!");

        std::vector<DOUBLE_T> out(in.size());

        /*
        std::vector<INT_T> N_rev(N);
        std::reverse(N_rev.begin(), N_rev.end());
        _ifft(&in[0], &out[0], rank, &N_rev[0]);
        */

        _ifft(&in[0], &out[0], rank, &N[0]);

        // normalize
        for (SIZE_T i(0); i < Ntot; ++i) {
            out[i] /= static_cast<DOUBLE_T>(Ntot);
        }

        return out;
    }
};

#endif
