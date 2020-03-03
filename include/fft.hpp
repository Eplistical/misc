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
#include "types.hpp"
#include "fftw3.h"

#ifdef MISC_FFT_ENABLE_THREAD
#include "omp.h"
#define _FFT_ENABLE_THREAD 1
#endif


namespace misc {

    // -- FFTW wrappers -- //

    VOID_T fft_setup() {
        static bool firsttime = true;
        if (firsttime) {
            firsttime = false;
#ifdef _FFT_ENABLE_THREAD 
            fftw_init_threads();
#endif
        }
#ifdef _FFT_ENABLE_THREAD 
        fftw_plan_with_nthreads(omp_get_max_threads());
#endif
    }

    VOID_T fft_cleanup() {
#ifdef _FFT_ENABLE_THREAD 
        fftw_cleanup_threads();
#else
        fftw_cleanup();
#endif
    }

    VOID_T _fft(const COMPLEX_T* in, COMPLEX_T* out, const int rank, const INT_T* N) {
        /* fast fourier transform
         *
         *  param     in: complex input pointer
         *  param    out: complex output pointer
         *  param   rank: dimension of fft
         *  param      N: length of array on each dimension
         *
         */
        fft_setup();
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

    VOID_T _ifft(const COMPLEX_T* in, COMPLEX_T* out, const INT_T rank, const INT_T* N) {
        /* inverse fast fourier transform
         *
         *  param     in: complex input pointer
         *  param    out: complex output pointer
         *  param   rank: dimension of fft
         *  param      N: length of array on each dimension
         *
         */
        fft_setup();
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

    template <typename T>
        VOID_T _fftshift(T* data, const INT_T rank, const INT_T* N) {
        /* swap data along each dimension
         *
         *  param   data: the data to swap
         *  param   rank: dimension of data
         *  param      N: length of array on each dimension
         *
         */

        }

    // -- interfaces -- //
    
    // 1d fft
    std::vector<COMPLEX_T> fft(const std::vector<COMPLEX_T>& in) {
        const INT_T N(in.size());
        crasher::confirm<> (in.size() >= N, "fft: insufficient data in the array!");

        std::vector<COMPLEX_T> out(N);
        _fft(&in[0], &out[0], 1, &N);
        return out;
    }

    // nd fft
    std::vector<COMPLEX_T> fftn(const std::vector<COMPLEX_T>& in, const std::vector<INT_T>& N) {
        const INT_T rank(N.size());
        SIZE_T Ntot(1);
        for (INT_T i(0); i < rank; ++i) {
            Ntot *= N[i];
        }
        crasher::confirm<> (in.size() >= Ntot, "fftn: insufficient data in the array!");

        std::vector<INT_T> Nrev(N);
        std::reverse(Nrev.begin(), Nrev.end());
        std::vector<COMPLEX_T> out(in.size());
        _fft(&in[0], &out[0], rank, &Nrev[0]);

        return out;
    }

    // 1d ifft
    std::vector<COMPLEX_T> ifft(const std::vector<COMPLEX_T>& in) {
        const INT_T N(in.size());
        crasher::confirm<> (in.size() >= N, "ifft: insufficient data in the array!");

        std::vector<COMPLEX_T> out(N);
        _ifft(&in[0], &out[0], 1, &N);
        // normalize
        out /= COMPLEX_T(static_cast<DOUBLE_T>(N), 0.0);
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

        std::vector<INT_T> Nrev(N);
        std::reverse(Nrev.begin(), Nrev.end());
        std::vector<COMPLEX_T> out(in.size());
        _ifft(&in[0], &out[0], rank, &Nrev[0]);
        // normalize
        out /= COMPLEX_T(static_cast<DOUBLE_T>(Ntot), 0.0);
        return out;
    }
};

#endif
