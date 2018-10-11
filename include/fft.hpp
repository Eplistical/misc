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
#include "fftw3.h"
#include "types.hpp"

namespace misc {

    // -- FFTW wrappers -- //

    VOID_T _fft_1d(const COMPLEX_T* in, COMPLEX_T* out, const INT_T N) {
        /* 1d fast fourier transform
         *
         *  param     in: complex input pointer
         *  param    out: complex output pointer
         *  param      N: length of array
         *
         */
        fftw_plan my_plan;
        COMPLEX_T* in_cast(const_cast<COMPLEX_T*>(in));
        my_plan = fftw_plan_dft_1d( N, 
                                    reinterpret_cast<fftw_complex*>(in_cast), 
                                    reinterpret_cast<fftw_complex*>(out), 
                                    FFTW_FORWARD, FFTW_ESTIMATE
                                    );
        fftw_execute(my_plan);
        fftw_destroy_plan(my_plan);
    }

    VOID_T _fft_1d(const DOUBLE_T* in, COMPLEX_T* out, const INT_T N) {
        /* 1d fast fourier transform, r2c
         *
         *  param     in: double input pointer
         *  param    out: complex output pointer
         *  param      N: length of array
         *
         */
        fftw_plan my_plan;
        DOUBLE_T* in_cast(const_cast<DOUBLE_T*>(in));
        my_plan = fftw_plan_dft_r2c_1d( N, 
                                        in_cast,
                                        reinterpret_cast<fftw_complex*>(out), 
                                        FFTW_ESTIMATE
                                        );
        fftw_execute(my_plan);
        fftw_destroy_plan(my_plan);
    }

    VOID_T _ifft_1d(const COMPLEX_T* in, COMPLEX_T* out, const INT_T N) {
        /* 1d inverse fast fourier transform
         *
         *  param     in: complex input pointer
         *  param    out: complex output pointer
         *  param      N: length of array
         *
         */
        fftw_plan my_plan;
        COMPLEX_T* in_cast(const_cast<COMPLEX_T*>(in));
        my_plan = fftw_plan_dft_1d( N, 
                                    reinterpret_cast<fftw_complex*>(in_cast), 
                                    reinterpret_cast<fftw_complex*>(out), 
                                    FFTW_BACKWARD, FFTW_ESTIMATE
                                    );
        fftw_execute(my_plan);
        fftw_destroy_plan(my_plan);
    }


    VOID_T _ifft_1d(const COMPLEX_T* in, DOUBLE_T* out, const INT_T N) {
        /* 1d inverse fast fourier transform, c2r
         *
         *  param     in: complex input pointer
         *  param    out: double output pointer
         *  param      N: length of array
         *
         */
        fftw_plan my_plan;
        COMPLEX_T* in_cast(const_cast<COMPLEX_T*>(in));
        my_plan = fftw_plan_dft_c2r_1d( N, 
                                        reinterpret_cast<fftw_complex*>(in_cast), 
                                        out,
                                        FFTW_ESTIMATE
                                        );
        fftw_execute(my_plan);
        // normalize
        for (INT_T i(0); i < N; ++i) {
            out[i] /= static_cast<DOUBLE_T>(N);
        }
        fftw_destroy_plan(my_plan);
    }

    // -- interfaces -- //
    
    // fft
    template <typename T>
        std::vector<COMPLEX_T> fft(const std::vector<T>& in) {
            const INT_T N(in.size());
            std::vector<COMPLEX_T> out(N);
            _fft_1d(&in[0], &out[0], N);
            return out;
        }

    // ifft
    std::vector<COMPLEX_T> ifft(const std::vector<COMPLEX_T>& in) {
        const INT_T N(in.size());
        std::vector<COMPLEX_T> out(N);
        _ifft_1d(&in[0], &out[0], N);
        return out;
    }

    std::vector<DOUBLE_T> irfft(const std::vector<COMPLEX_T>& in) {
        const INT_T N(in.size());
        std::vector<DOUBLE_T> out(N);
        _ifft_1d(&in[0], &out[0], N);
        return out;
    }

};

#endif
