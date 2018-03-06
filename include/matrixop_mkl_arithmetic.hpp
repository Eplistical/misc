#ifndef _MATRIXOP_MKL_ARITHMETIC_HPP
#define _MATRIXOP_MKL_ARITHMETIC_HPP

#ifndef MKL_Complex16
#define MKL_Complex16 std::complex<double>
#endif

#include <cmath>
#include <complex>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <unordered_map>
#include <type_traits>
#include "mkl.h"

namespace matrixop {
    using std::complex;
    using std::vector;
    using std::conj;
    using std::move;
    using std::swap;
    using std::string;
    using std::unordered_map;
    using std::is_same;
    using std::enable_if;

    using SearchDictType = unordered_map<const char*, const void*>;

    const static int ONE_i(1);
    const static double ONE_d(1.0);
    const static complex<double> ONE_z(1.0, 0.0);

    const static int ZERO_i(0);
    const static double ZERO_d(0.0);
    const static complex<double> ZERO_z(0.0, 0.0);

    const static complex<double> I_z(0.0, 1.0);

    // --- constants --- //

    const static SearchDictType one__
    { 
        { typeid(int).name(), reinterpret_cast<const void*>(&ONE_i) },
        { typeid(double).name(), reinterpret_cast<const void*>(&ONE_d) },
        { typeid(complex<double>).name(), reinterpret_cast<const void*>(&ONE_z) }
    };

    const static SearchDictType zero__
    { 
        { typeid(int).name(), reinterpret_cast<const void*>(&ZERO_i) },
        { typeid(double).name(), reinterpret_cast<const void*>(&ZERO_d) },
        { typeid(complex<double>).name(), reinterpret_cast<const void*>(&ZERO_z) }
    };


    // --- basic math --- //


    const static SearchDictType vadd_func__ =
    { 
        { typeid(double).name(), reinterpret_cast<const void*>(&vdAdd) },
        { typeid(complex<double>).name(), reinterpret_cast<const void*>(&vzAdd) }   
    };
    
    const static SearchDictType vsub_func__ =
    { 
        { typeid(double).name(), reinterpret_cast<const void*>(&vdSub) },
        { typeid(complex<double>).name(), reinterpret_cast<const void*>(&vzSub) }   
    };

    const static SearchDictType vmul_func__ =
    { 
        { typeid(double).name(), reinterpret_cast<const void*>(&vdMul) },
        { typeid(complex<double>).name(), reinterpret_cast<const void*>(&vzMul) }   
    };

    const static SearchDictType vdiv_func__ =
    { 
        { typeid(double).name(), reinterpret_cast<const void*>(&vdDiv) },
        { typeid(complex<double>).name(), reinterpret_cast<const void*>(&vzDiv) }   
    };

    const static unordered_map<const char*, const SearchDictType&> basic_math_func__ = 
    {
        { "vadd", vadd_func__ },
        { "vsub", vsub_func__ },
        { "vmul", vmul_func__ },
        { "vdiv", vdiv_func__ }
    };

    template<typename T>
        inline vector<T> do_basic_math__(
                const char* op,
                vector<T>& v1, vector<T>& v2,
                int begin, int len)
        {
            using FuncPtrType = void(*)(const int, T*, T*, T*);
            const int N(len == -1 ? v1.size() : len);
            vector<T> rst(N);

            reinterpret_cast<FuncPtrType>(basic_math_func__.at(op).at(typeid(T).name()))
                        (N, &v1[begin], &v2[begin], &rst[0]);
            return rst;
        }

    template<typename T>
        inline vector<T> vadd(vector<T>& v1, vector<T>& v2,
                int begin = 0, int len = -1)
        {
            return do_basic_math__("vadd", v1, v2, begin, len);
        }

    template<typename T>
        inline vector<T> vsub(vector<T>& v1, vector<T>& v2,
                int begin = 0, int len = -1)
        {
            return do_basic_math__("vsub", v1, v2, begin, len);
        }

    template<typename T>
        inline vector<T> vmul(vector<T>& v1, vector<T>& v2,
                int begin = 0, int len = -1)
        {
            return do_basic_math__("vmul", v1, v2, begin, len);
        }

    template<typename T>
        inline vector<T> vdiv(vector<T>& v1, vector<T>& v2,
                int begin = 0, int len = -1)
        {
            return do_basic_math__("vdiv", v1, v2, begin, len);
        }


    // --- single-vector operation --- //
    

    const static SearchDictType vsqrt_func__ =
    { 
        { typeid(double).name(), reinterpret_cast<const void*>(&vdSqrt) }
    };

    const static SearchDictType vconj_func__ =
    { 
        { typeid(complex<double>).name(), reinterpret_cast<const void*>(&vzConj) }
    };

    const static SearchDictType varg_func__ =
    { 
        { typeid(complex<double>).name(), reinterpret_cast<const void*>(&vzArg) }
    };

    const static SearchDictType vabs_func__ =
    { 
        { typeid(double).name(), reinterpret_cast<const void*>(&vdAbs) },
        { typeid(complex<double>).name(), reinterpret_cast<const void*>(&vzAbs) }
    };

    const static SearchDictType vexp_func__ =
    { 
        { typeid(double).name(), reinterpret_cast<const void*>(&vdExp) }
    };

    const static SearchDictType vln_func__ =
    { 
        { typeid(double).name(), reinterpret_cast<const void*>(&vdLn) }
    };

    const static SearchDictType vlog10_func__ =
    { 
        { typeid(double).name(), reinterpret_cast<const void*>(&vdLog10) }
    };

    const static unordered_map<const char*, const SearchDictType&> single_vec_func__ = 
    {
        { "vsqrt", vsqrt_func__ },
        { "vconj", vconj_func__ },
        { "varg", varg_func__ },
        { "vabs", vabs_func__ },
        { "vexp", vexp_func__ },
        { "vln", vln_func__ },
        { "vlog10", vlog10_func__ }
    };

    template<typename T>
        inline vector<T> do_single_vec_func__(
                const char* op,
                vector<T>& v, 
                int begin, int len)
        {
            using FuncPtrType = void(*)(const int, T*, T*);
            const int N(len == -1 ? v.size() : len);
            vector<T> rst(N);

            reinterpret_cast<FuncPtrType>(single_vec_func__.at(op).at(typeid(T).name()))
                        (N, &v[begin], &rst[0]);
            return rst;
        }

    template<typename T>
        inline vector<T> vsqrt(vector<T>& v,
                int begin = 0, int len = -1)
        {
            return do_single_vec_func__("vsqrt", v, begin, len);
        }

    template<typename T>
        inline vector<T> vconj(vector<T>& v,
                int begin = 0, int len = -1)
        {
            return do_single_vec_func__("vconj", v, begin, len);
        }

    template<typename T>
        inline vector<T> varg(vector<T>& v,
                int begin = 0, int len = -1)
        {
            return do_single_vec_func__("varg", v, begin, len);
        }

    template<typename T>
        inline vector<T> vabs(vector<T>& v,
                int begin = 0, int len = -1)
        {
            return do_single_vec_func__("vabs", v, begin, len);
        }

    template<typename T>
        inline vector<T> vexp(vector<T>& v,
                int begin = 0, int len = -1)
        {
            return do_single_vec_func__("vexp", v, begin, len);
        }

    template<typename T>
        inline vector<T> vln(vector<T>& v,
                int begin = 0, int len = -1)
        {
            return do_single_vec_func__("vln", v, begin, len);
        }

    template<typename T>
        inline vector<T> vlog10(vector<T>& v,
                int begin = 0, int len = -1)
        {
            return do_single_vec_func__("vlog10", v, begin, len);
        }


    // --- scalar-vector operation --- //


    const static SearchDictType vpowx_func__ =
    { 
        { typeid(double).name(), reinterpret_cast<const void*>(&vdPowx) }
    };

    const static unordered_map<const char*, const SearchDictType&> scalar_vec_func__ = 
    {
        { "vpowx", vpowx_func__ }
    };

    template<typename T>
        inline vector<T> do_scalar_vec_func__(
                const char* op,
                vector<T>& v, const T& a,
                int begin, int len)
        {
            using FuncPtrType = void(*)(const int, T*, T, T*);
            const int N(len == -1 ? v.size() : len);
            vector<T> rst(N);

            reinterpret_cast<FuncPtrType>(scalar_vec_func__.at(op).at(typeid(T).name()))
                        (N, &v[begin], a, &rst[0]);
            return rst;
        }

    template<typename T>
        inline vector<T> vpowx(vector<T>& v, const T& a,
                int begin = 0, int len = -1)
        {
            return do_scalar_vec_func__("vpowx", v, a, begin, len);
        }

    // --- vcopy --- //

    const static SearchDictType vcopy_func__ =
    { 
        { typeid(double).name(), reinterpret_cast<const void*>(&dcopy) },
        { typeid(complex<double>).name(), reinterpret_cast<const void*>(&zcopy) }
    };

    template<typename T>
        inline void vcopy(
                int N,
                T* from, int from_inc,
                T* to, int to_inc
                )
        {
            using FuncPtrType = void(*)(int*, T*, int*, T*, int*);

            reinterpret_cast<FuncPtrType>(vcopy_func__.at(typeid(T).name()))
                        (&N, from, &from_inc, to, &to_inc);
        }
};

#endif // _MATRIXOP_MKL_ARITHMETIC
