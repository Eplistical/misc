#ifndef _VECTOR_HPP
#define _VECTOR_HPP
/* module for std::vector operations
 * require C++11
 * written based on <vector>
 *
 * Gaohan
 */
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <stdexcept>
#include "types.hpp"
#include "crasher.hpp"

// helpers

template <typename T1, typename T2>
void assertsize(const std::vector<T1>& v1, const std::vector<T2>& v2)
{
	misc::crasher::confirm<std::runtime_error>(v1.size() == v2.size(), 
			"assertsize: v1 & v2 have different sizes!");
}

template <typename T>
typename std::enable_if< std::is_arithmetic<T>::value, T >::type
conj(const T& a) {
	return a;
}

// element-wise math operations

template <typename T>
std::vector<T> conj(const std::vector<T>& v)
{
    const SIZE_T N(v.size());
    std::vector<T> rst(N);
    for(SIZE_T j(0); j < N; ++j) 
		rst[j] = conj(v[j]) ;
    return rst;
}

template <typename T>
std::vector<T> abs(const std::vector<T>& v)
{
    const SIZE_T N(v.size());
    std::vector<T> rst(N);
    for(SIZE_T j(0); j < N; ++j) 
		rst[j] = std::abs(v[j]) ;
    return rst;
}

template <typename T>
std::vector<T> sqrt(const std::vector<T>& v)
{
    const SIZE_T N(v.size());
	std::vector<T> rst(N);
    for(SIZE_T j(0); j < N; ++j) 
		rst[j] = std::sqrt(v[j]);
    return rst;
}

template <typename T1, typename T2>
auto pow(const std::vector<T1>& v1, const std::vector<T2>& v2) -> std::vector<decltype(std::pow(v1.at(0), v2.at(0)))>
{
	// pow(vec, vec)
    assertsize(v1, v2);
    const SIZE_T N(v1.size());
    std::vector<decltype(std::pow(v1.at(0), v2.at(0)))> rst(N);
    for(size_t j(0); j < N; ++j)
		rst[j] = std::pow(v1[j], v2[j]);
	return rst;
}

template <typename T1, typename T2>
auto pow(const std::vector<T1>& v1, const T2& a) -> std::vector<decltype(std::pow(v1.at(0), a))>
{
	// pow(vec, scal)
    const SIZE_T N(v1.size());
    std::vector<decltype(std::pow(v1.at(0), a))> rst(N);
    for(size_t j(0); j < N; ++j)
		rst[j] = std::pow(v1[j], a);
	return rst;
}

template <typename T1, typename T2>
auto pow(const T2& a, const std::vector<T1>& v1) -> std::vector<decltype(std::pow(a, v1.at(0)))>
{
	// pow(scal, vec)
    const SIZE_T N(v1.size());
    std::vector<decltype(a, std::pow(v1.at(0)))> rst(N);
    for(size_t j(0); j < N; ++j)
		rst[j] = std::pow(a, v1[j]);
	return rst;
}

template <typename T>
std::vector<T> exp(const std::vector<T>& v)
{
    const SIZE_T N(v.size());
    std::vector<T> rst(N);
    for(SIZE_T j(0); j < N; ++j) 
		rst[j] = std::exp(v[j]) ;
    return rst;
}

template <typename T>
std::vector<T> log(const std::vector<T>& v)
{
    const SIZE_T N(v.size());
    std::vector<T> rst(N);
    for(SIZE_T j(0); j < N; ++j) 
		rst[j] = std::log(v[j]) ;
    return rst;
}

template <typename T>
std::vector<T> log2(const std::vector<T>& v)
{
    const SIZE_T N(v.size());
    std::vector<T> rst(N);
    for(SIZE_T j(0); j < N; ++j) 
		rst[j] = std::log2(v[j]) ;
    return rst;
}

template <typename T>
std::vector<T> log10(const std::vector<T>& v)
{
    const SIZE_T N(v.size());
    std::vector<T> rst(N);
    for(SIZE_T j(0); j < N; ++j) 
		rst[j] = std::log10(v[j]) ;
    return rst;
}

template <typename T>
std::vector<T> sin(const std::vector<T>& v)
{
    const SIZE_T N(v.size());
    std::vector<T> rst(N);
    for(SIZE_T j(0); j < N; ++j) 
		rst[j] = std::sin(v[j]) ;
    return rst;
}

template <typename T>
std::vector<T> cos(const std::vector<T>& v)
{
    const SIZE_T N(v.size());
    std::vector<T> rst(N);
    for(SIZE_T j(0); j < N; ++j) 
		rst[j] = std::cos(v[j]) ;
    return rst;
}

template <typename T>
std::vector<T> tan(const std::vector<T>& v)
{
    const SIZE_T N(v.size());
    std::vector<T> rst(N);
    for(SIZE_T j(0); j < N; ++j) 
		rst[j] = std::tan(v[j]) ;
    return rst;
}

template <typename T>
std::vector<T> asin(const std::vector<T>& v)
{
    const SIZE_T N(v.size());
    std::vector<T> rst(N);
    for(SIZE_T j(0); j < N; ++j) 
		rst[j] = std::asin(v[j]) ;
    return rst;
}

template <typename T>
std::vector<T> acos(const std::vector<T>& v)
{
    const SIZE_T N(v.size());
    std::vector<T> rst(N);
    for(SIZE_T j(0); j < N; ++j) 
		rst[j] = std::acos(v[j]) ;
    return rst;
}

template <typename T>
std::vector<T> atan(const std::vector<T>& v)
{
    const SIZE_T N(v.size());
    std::vector<T> rst(N);
    for(SIZE_T j(0); j < N; ++j) 
		rst[j] = std::atan(v[j]) ;
    return rst;
}

template <typename T>
std::vector<T> sinh(const std::vector<T>& v)
{
    const SIZE_T N(v.size());
    std::vector<T> rst(N);
    for(SIZE_T j(0); j < N; ++j) 
		rst[j] = std::sinh(v[j]) ;
    return rst;
}

template <typename T>
std::vector<T> cosh(const std::vector<T>& v)
{
    const SIZE_T N(v.size());
    std::vector<T> rst(N);
    for(SIZE_T j(0); j < N; ++j) 
		rst[j] = std::cosh(v[j]) ;
    return rst;
}

template <typename T>
std::vector<T> tanh(const std::vector<T>& v)
{
    const SIZE_T N(v.size());
    std::vector<T> rst(N);
    for(SIZE_T j(0); j < N; ++j) 
		rst[j] = std::tanh(v[j]) ;
    return rst;
}

// collective operations

template <typename T>
T sum(const std::vector<T>& v)
{
	// return v[0] + v[1] + ... + v[N-1]
    T rst = static_cast<T>(0);
    const SIZE_T N(v.size());
    for(SIZE_T j(0); j < N; ++j) 
		rst += v.at(j);
    return rst;
}

template <typename T>
T mean(const std::vector<T>& v)
{
	// find the mean value of all elements in the std::vector
    return sum(v) / v.size();
}

template <typename T>
T prod(const std::vector<T>& v)
{
	// return v[0] * v[1] * ... * v[N-1]
    T rst = static_cast<T>(1);
    const SIZE_T N(v.size());
    for(SIZE_T j(0); j < N; ++j) 
		rst *= v[j];
    return rst;
}

template <typename T>
typename std::enable_if< std::is_integral<T>::value, DOUBLE_T>::type
norm(const std::vector<T>& v)
{
	// norm of the std::vector<T>
	DOUBLE_T rst(0.0);
    const SIZE_T N(v.size());
	for(SIZE_T j(0); j < N; ++j)
		rst += v[j] * v[j];
    return std::sqrt(rst);
}

template <typename T>
typename std::enable_if< std::is_floating_point<T>::value, T>::type
norm(const std::vector<T>& v)
{
	// norm of the std::vector<T>
	T rst(0.0);
    const SIZE_T N(v.size());
	for(SIZE_T j(0); j < N; ++j)
		rst += v[j] * v[j];
    return std::sqrt(rst);
}

template <typename T>
typename std::enable_if< std::is_integral<T>::value, DOUBLE_T>::type
norm(const std::vector< std::complex<T> >& v)
{
	// norm of the std::vector< complex<T> >
	DOUBLE_T rst(0.0);
    const SIZE_T N(v.size());
	for(SIZE_T j(0); j < N; ++j)
		rst += std::pow(v[j].real(), 2) + pow(v[j].imag(), 2);
    return std::sqrt(rst);
}

template <typename T>
typename std::enable_if< std::is_floating_point<T>::value, T>::type
norm(const std::vector< std::complex<T> >& v)
{
	// norm of the std::vector< complex<T> >
	T rst(0.0);
    const SIZE_T N(v.size());
	for(SIZE_T j(0); j < N; ++j)
		rst += std::pow(v[j].real(), 2) + pow(v[j].imag(), 2);
    return std::sqrt(rst);
}


template <typename T>
T min(const std::vector<T>& v)
{
	// find the min element in the std::vector 
    const SIZE_T N(v.size());
    T rst = v[0];
    for(SIZE_T j(1); j < N; ++j)
        rst = (v[j] < rst)?v[j]:rst;
    return rst;
}

template <typename T>
T max(const std::vector<T>& v)
{
	// find the max element in the std::vector 
    const SIZE_T N(v.size());
    T rst = v[0];
    for(SIZE_T j(1); j < N; ++j)
        rst = (v[j] > rst)?v[j]:rst;
    return rst;
}

// arithmetic operators 

template <typename T1, typename T2>
auto operator+(const std::vector<T1>& v1, const std::vector<T2>& v2) -> std::vector<decltype(v1.at(0) + v2.at(0))>
{
	// vec + vec
    assertsize(v1, v2);
    const SIZE_T N(v1.size());
    std::vector<decltype(v1.at(0) + v2.at(0))> rst(N);
    for(SIZE_T j(0); j < N; ++j)
        rst[j] = v1[j] + v2[j];
	return rst;
}

template <typename T1, typename T2>
auto operator+(const std::vector<T1>& v1, const T2& a) -> std::vector<decltype(v1.at(0) + a)>
{
	// vec + scal
    const SIZE_T N(v1.size());
    std::vector<decltype(v1.at(0) + a)> rst(N);
    for(SIZE_T j(0); j < N; ++j)
        rst[j] = v1[j] + a;
	return rst;
}

template <typename T1, typename T2>
auto operator+(const T2& a, const std::vector<T1>& v1) -> std::vector<decltype(a + v1.at(0))>
{
	// scal + vec
	return v1 + a;
}

template <typename T1, typename T2>
std::vector<T1>& operator+=(std::vector<T1>& v1, const T2& a)
{
	// vec += scal
    const SIZE_T N(v1.size());
    for(SIZE_T j(0); j < N; ++j)
		v1[j] += a;
	return v1;
}

template <typename T1, typename T2>
std::vector<T1>& operator+=(std::vector<T1>& v1, const std::vector<T2>& v2)
{
	// vec += vec
	assertsize(v1, v2);
    const SIZE_T N(v1.size());
    for(SIZE_T j(0); j < N; ++j)
		v1[j] += v2[j];
	return v1;
}

template <typename T1>
std::vector<T1>& operator++(std::vector<T1>& v1)
{
	// ++vec
    const SIZE_T N(v1.size());
    for(SIZE_T j(0); j < N; ++j)
		v1[j] += static_cast<T1>(1.0);
	return v1;
}

template <typename T1>
std::vector<T1> operator++(std::vector<T1>& v1, int)
{
	// vec++
	std::vector<T1> rst(v1);
    const SIZE_T N(v1.size());
    for(SIZE_T j(0); j < N; ++j)
		v1[j] += static_cast<T1>(1.0);
	return rst;
}

template <typename T1, typename T2>
auto operator-(const std::vector<T1>& v1, const std::vector<T2>& v2) -> std::vector<decltype(v1.at(0) - v2.at(0))>
{
	// vec - vec
    assertsize(v1, v2);
    const SIZE_T N(v1.size());
    std::vector<decltype(v1.at(0) - v2.at(0))> rst(N);
    for(SIZE_T j(0); j < N; ++j)
        rst[j] = v1[j] - v2[j];
	return rst;
}

template <typename T1, typename T2>
auto operator-(const std::vector<T1>& v1, const T2& a) -> std::vector<decltype(v1.at(0) - a)>
{
	// vec - scal
    const SIZE_T N(v1.size());
    std::vector<decltype(v1.at(0) - a)> rst(N);
    for(SIZE_T j(0); j < N; ++j)
        rst[j] = v1[j] - a;
	return rst;
}

template <typename T1, typename T2>
auto operator-(const T2& a, const std::vector<T1>& v1) -> std::vector<decltype(a - v1.at(0))>
{
	// scal - vec
    const SIZE_T N(v1.size());
    std::vector<decltype(a - v1.at(0))> rst(N);
    for(SIZE_T j(0); j < N; ++j)
        rst[j] = a - v1[j];
	return rst;
}

template <typename T1, typename T2>
std::vector<T1>& operator-=(std::vector<T1>& v1, const T2& a)
{
	// vec -= scal
    const SIZE_T N(v1.size());
    for(SIZE_T j(0); j < N; ++j)
		v1[j] -= a;
	return v1;
}

template <typename T1, typename T2>
std::vector<T1>& operator-=(std::vector<T1>& v1, const std::vector<T2>& v2)
{
	// vec -= vec
	assertsize(v1, v2);
    const SIZE_T N(v1.size());
    for(SIZE_T j(0); j < N; ++j)
		v1[j] -= v2[j];
	return v1;
}

template <typename T1>
std::vector<T1>& operator--(std::vector<T1>& v1)
{
	// --vec
    const SIZE_T N(v1.size());
    for(SIZE_T j(0); j < N; ++j)
		v1[j] -= static_cast<T1>(1.0);
	return v1;
}

template <typename T1>
std::vector<T1> operator--(std::vector<T1>& v1, int)
{
	// vec--
	std::vector<T1> rst(v1);
    const SIZE_T N(v1.size());
    for(SIZE_T j(0); j < N; ++j)
		v1[j] -= static_cast<T1>(1.0);
	return rst;
}

template <typename T>
std::vector<T> operator-(const std::vector<T>& v1)
{
	// negetive vec
    const SIZE_T N(v1.size());
    std::vector<T> rst(N);
    for(SIZE_T j(0); j < N; ++j)
        rst[j] = -v1[j];
	return rst;
}

template <typename T1, typename T2>
auto operator*(const std::vector<T1>& v1, const std::vector<T2>& v2) -> std::vector<decltype(v1.at(0) * v2.at(0))>
{
	// vec * vec
    assertsize(v1, v2);
    const SIZE_T N(v1.size());
    std::vector<decltype(v1.at(0) * v2.at(0))> rst(N);
    for(SIZE_T j(0); j < N; ++j)
        rst[j] = v1[j] * v2[j];
	return rst;
}

template <typename T1, typename T2>
auto operator*(const std::vector<T1>& v1, const T2& a) -> std::vector<decltype(v1.at(0) * a)>
{
	// vec - scal
    const SIZE_T N(v1.size());
    std::vector<decltype(v1.at(0) * a)> rst(N);
    for(SIZE_T j(0); j < N; ++j)
        rst[j] = v1[j] * a;
	return rst;
}

template <typename T1, typename T2>
auto operator*(const T2& a, const std::vector<T1>& v1) -> std::vector<decltype(a * v1.at(0))>
{
	// scal * vec
	return v1 * a;
}

template <typename T1, typename T2>
std::vector<T1>& operator*=(std::vector<T1>& v1, const T2& a)
{
	// vec *= scal
    const SIZE_T N(v1.size());
    for(SIZE_T j(0); j < N; ++j)
		v1[j] *= a;
	return v1;
}

template <typename T1, typename T2>
std::vector<T1>& operator*=(std::vector<T1>& v1, const std::vector<T2>& v2)
{
	// vec *= vec
	assertsize(v1, v2);
    const SIZE_T N(v1.size());
    for(SIZE_T j(0); j < N; ++j)
		v1[j] *= v2[j];
	return v1;
}

template <typename T1, typename T2>
auto operator/(const std::vector<T1>& v1, const std::vector<T2>& v2) -> std::vector<decltype(v1.at(0) / v2.at(0))>
{
	// vec / vec
    assertsize(v1, v2);
    const SIZE_T N(v1.size());
    std::vector<decltype(v1.at(0) / v2.at(0))> rst(N);
    for(SIZE_T j(0); j < N; ++j)
        rst[j] = v1[j] / v2[j];
	return rst;
}

template <typename T1, typename T2>
auto operator/(const std::vector<T1>& v1, const T2& a) -> std::vector<decltype(v1.at(0) / a)>
{
	// vec / scal
	return v1 * (static_cast<T2>(1.0) / a);
}

template <typename T1, typename T2>
auto operator/(const T2& a, const std::vector<T1>& v1) -> std::vector<decltype(a / v1.at(0))>
{
	// scal / vec
    const SIZE_T N(v1.size());
    std::vector<decltype(a / v1.at(0))> rst(N);
    for(SIZE_T j(0); j < N; ++j)
        rst[j] = a / v1[j];
	return rst;
}

template <typename T1, typename T2>
std::vector<T1>& operator/=(std::vector<T1>& v1, const T2& a)
{
	// vec /= scal
	const T2 a_inv(static_cast<T2>(1.0) / a);
    const SIZE_T N(v1.size());
    for(SIZE_T j(0); j < N; ++j)
		v1[j] *= a_inv;
	return v1;
}

template <typename T1, typename T2>
std::vector<T1>& operator/=(std::vector<T1>& v1, const std::vector<T2>& v2)
{
	// vec /= vec
	assertsize(v1, v2);
    const SIZE_T N(v1.size());
    for(SIZE_T j(0); j < N; ++j)
		v1[j] /= v2[j];
	return v1;
}

template <typename T1, typename T2>
auto operator%(const std::vector<T1>& v1, const std::vector<T2>& v2) -> std::vector<decltype(v1.at(0) % v2.at(0))>
{
	// vec % vec
    assertsize(v1, v2);
    const SIZE_T N(v1.size());
    std::vector<decltype(v1.at(0) % v2.at(0))> rst(N);
    for(SIZE_T j(0); j < N; ++j)
        rst[j] = v1[j] % v2[j];
	return rst;
}

template <typename T1, typename T2>
auto operator%(const std::vector<T1>& v1, const T2& a) -> std::vector<decltype(v1.at(0) % a)>
{
	// vec % scal
	return v1 * (static_cast<T2>(1.0) % a);
}

template <typename T1, typename T2>
auto operator%(const T2& a, const std::vector<T1>& v1) -> std::vector<decltype(a % v1.at(0))>
{
	// scal % vec
    const SIZE_T N(v1.size());
    std::vector<decltype(a % v1.at(0))> rst(N);
    for(SIZE_T j(0); j < N; ++j)
        rst[j] = a % v1[j];
	return rst;
}

template <typename T1, typename T2>
std::vector<T1>& operator%=(std::vector<T1>& v1, const T2& a)
{
	// vec %= scal
    const SIZE_T N(v1.size());
    for(SIZE_T j(0); j < N; ++j)
		v1[j] %= a;
	return v1;
}

template <typename T1, typename T2>
std::vector<T1>& operator%=(std::vector<T1>& v1, const std::vector<T2>& v2)
{
	// vec %= vec
	assertsize(v1, v2);
    const SIZE_T N(v1.size());
    for(SIZE_T j(0); j < N; ++j)
		v1[j] %= v2[j];
	return v1;
}

// relational operators

template <typename T1, typename T2>
std::vector<BOOL_T> operator==(const std::vector<T1>& v1, const std::vector<T2>& v2)
{
	// vec == vec
    assertsize(v1, v2);
    const SIZE_T N(v1.size());
    std::vector<BOOL_T> rst(N);
    for(size_t j(0); j < N; ++j)
        rst[j] = (v1[j] == v2[j]);
	return rst;
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator==(const std::vector<T1>& v1, const T2& a)
{
	// vec == scal
    const SIZE_T N(v1.size());
    std::vector<BOOL_T> rst(N);
    for(size_t j(0); j < N; ++j)
        rst[j] = (v1[j] == a);
	return rst;
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator!=(const std::vector<T1>& v1, const std::vector<T2>& v2)
{
	// vec != vec
    assertsize(v1, v2);
    const SIZE_T N(v1.size());
    std::vector<BOOL_T> rst(N);
    for(size_t j(0); j < N; ++j)
        rst[j] = (v1[j] != v2[j]);
	return rst;
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator!=(const std::vector<T1>& v1, const T2& a)
{
	// vec != scal
    const SIZE_T N(v1.size());
    std::vector<BOOL_T> rst(N);
    for(size_t j(0); j < N; ++j)
        rst[j] = (v1[j] != a);
	return rst;
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator>=(const std::vector<T1>& v1, const std::vector<T2>& v2)
{
	// vec >= vec
    assertsize(v1, v2);
    const SIZE_T N(v1.size());
    std::vector<BOOL_T> rst(N);
    for(SIZE_T j(0); j < N; ++j)
        rst[j] = (v1[j] >= v2[j]);
	return rst;
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator>=(const std::vector<T1>& v1, const T2& a)
{
	// vec >= scal
    const SIZE_T N(v1.size());
    std::vector<BOOL_T> rst(N);
    for(size_t j(0); j < N; ++j)
        rst[j] = (v1[j] >= a);
	return rst;
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator<=(const std::vector<T1>& v1, const std::vector<T2>& v2)
{
	// vec <= vec
    assertsize(v1, v2);
    const SIZE_T N(v1.size());
    std::vector<BOOL_T> rst(N);
    for(size_t j(0); j < N; ++j)
        rst[j] = (v1[j] <= v2[j]);
	return rst;
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator<=(const std::vector<T1>& v1, const T2& a)
{
	// vec <= scal
    const SIZE_T N(v1.size());
    std::vector<BOOL_T> rst(N);
    for(size_t j(0); j < N; ++j)
        rst[j] = (v1[j] <= a);
	return rst;
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator>(const std::vector<T1>& v1, const std::vector<T2>& v2)
{
	// vec > vec
    assertsize(v1, v2);
    const SIZE_T N(v1.size());
    std::vector<BOOL_T> rst(N);
    for(size_t j(0); j < N; ++j)
        rst[j] = (v1[j] > v2[j]);
	return rst;
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator>(const std::vector<T1>& v1, const T2& a)
{
	// vec > scal
    const SIZE_T N(v1.size());
    std::vector<BOOL_T> rst(N);
    for(size_t j(0); j < N; ++j)
        rst[j] = (v1[j] > a);
	return rst;
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator<(const std::vector<T1>& v1, const std::vector<T2>& v2)
{
	// vec < vec
    assertsize(v1, v2);
    const SIZE_T N(v1.size());
    std::vector<BOOL_T> rst(N);
    for(size_t j(0); j < N; ++j)
        rst[j] = (v1[j] < v2[j]);
	return rst;
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator<(const std::vector<T1>& v1, const T2& a)
{
	// vec < scal
    const SIZE_T N(v1.size());
    std::vector<BOOL_T> rst(N);
    for(size_t j(0); j < N; ++j)
        rst[j] = (v1[j] < a);
	return rst;
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator==(const T2& a, const std::vector<T1>& v1)
{
	// scal == vec
	return (v1 == a);
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator!=(const T2& a, const std::vector<T1>& v1)
{
	// scal != vec
	return (v1 != a);
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator>=(const T2& a, const std::vector<T1>& v1)
{
	// scal >= vec
	return (v1 <= a);
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator<=(const T2& a, const std::vector<T1>& v1)
{
	// scal <= vec
	return (v1 >= a);
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator>(const T2& a, const std::vector<T1>& v1)
{
	// scal > vec
	return (v1 < a);
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator<(const T2& a, const std::vector<T1>& v1)
{
	// scal < vec
	return (v1 > a);
}

// logical operators

template <typename T>
std::vector<BOOL_T> operator!(const std::vector<T>& v) 
{
	// !vec
    const SIZE_T N(v.size());
    std::vector<BOOL_T> rst(N);
    for(size_t j(0); j < N; ++j)
		rst[j] = static_cast<BOOL_T>(!v[j]);
	return rst;
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator&&(const std::vector<T1>& v1, const std::vector<T2>& v2) 
{
	// vec && vec
	assertsize(v1, v2);
    const SIZE_T N(v1.size());
    std::vector<BOOL_T> rst(N);
    for(size_t j(0); j < N; ++j)
		rst[j] = static_cast<BOOL_T>(v1[j] && v2[j]);
	return rst;
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator&&(const std::vector<T1>& v1, const T2& a) 
{
	// vec && scal
    const SIZE_T N(v1.size());
    std::vector<BOOL_T> rst(N);
    for(size_t j(0); j < N; ++j)
		rst[j] = static_cast<BOOL_T>(v1[j] && a);
	return rst;
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator&&(const T2& a, const std::vector<T1>& v1) 
{
	// scal && vec
	return v1 && a;
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator||(const std::vector<T1>& v1, const std::vector<T2>& v2) 
{
	// vec || vec
	assertsize(v1, v2);
    const SIZE_T N(v1.size());
    std::vector<BOOL_T> rst(N);
    for(size_t j(0); j < N; ++j)
		rst[j] = static_cast<BOOL_T>(v1[j] || v2[j]);
	return rst;
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator||(const std::vector<T1>& v1, const T2& a) 
{
	// vec || scal
    const SIZE_T N(v1.size());
    std::vector<BOOL_T> rst(N);
    for(size_t j(0); j < N; ++j)
		rst[j] = static_cast<BOOL_T>(v1[j] || a);
	return rst;
}

template <typename T1, typename T2>
std::vector<BOOL_T> operator||(const T2& a, const std::vector<T1>& v1) 
{
	// scal || vec
	return v1 || a;
}

// other operators

template <typename T1, typename T2>
auto operator^(const std::vector<T1>& v1, const std::vector<T2>& v2) -> std::vector<decltype(std::pow(v1.at(0), v2.at(0)))>
{
	// vec^vec
	return pow(v1, v2);
}

template <typename T1, typename T2>
auto operator^(const std::vector<T1>& v1, const T2& a) -> std::vector<decltype(std::pow(v1.at(0), a))>
{
	// vec^scal
	return pow(v1, a);
}

template <typename T1, typename T2>
auto operator^(const T2& a, const std::vector<T1>& v1) -> std::vector<decltype(std::pow(a, v1.at(0)))>
{
	// scal^vec
	return pow(a, v1);
}

template <typename T1, typename T2>
std::vector<T1>& operator^=(std::vector<T1>& v1, const std::vector<T2>& v2)
{
	// vec^=vec
    assertsize(v1, v2);
    const SIZE_T N(v1.size());
    for(size_t j(0); j < N; ++j)
		v1[j] = std::pow(v1[j], v2[j]);
	return v1;
}

template <typename T1, typename T2>
std::vector<T1> operator^=(std::vector<T1>& v1, const T2& a)
{
	// vec^=scal
    const SIZE_T N(v1.size());
    for(size_t j(0); j < N; ++j)
		v1[j] = std::pow(v1[j], a);
	return v1;
}

template <typename T1>
std::vector<T1> operator|(const std::vector<T1>& v1, const std::vector<T1>& v2)
{
	// vec|vec
	std::vector<T1> rst(v1);
	rst.insert(rst.end(), v2.begin(), v2.end());
	return rst;
}

template <typename T1, typename T2>
std::vector<T1> operator|(const std::vector<T1>& v1, const T2& a)
{
	// vec|scal
	std::vector<T1> rst;
	rst.reserve(v1.size() + 1);
	rst.insert(rst.end(), v1.begin(), v1.end());
	rst.push_back(static_cast<T1>(a));
	return rst;
}

template <typename T1, typename T2>
std::vector<T1> operator|(const T2& a, const std::vector<T1>& v1)
{
	// scal|vec
	std::vector<T1> rst(1, static_cast<T1>(a));
	rst.reserve(v1.size() + 1);
	rst.insert(rst.end(), v1.begin(), v1.end());
	return rst;
}

template <typename T1>
std::vector<T1>& operator|=(std::vector<T1>& v1, const std::vector<T1>& v2)
{
	// vec|=vec
	v1.insert(v1.end(), v2.begin(), v2.end());
	return v1;
}

template <typename T1, typename T2>
std::vector<T1>& operator|=(std::vector<T1>& v1, const T2& a)
{
	// vec|=scal
	v1.push_back(static_cast<T1>(a));
	return v1;
}

template <typename T1, typename T2>
typename std::enable_if< std::is_integral<T2>::value, std::vector<T1> >::type
operator<<(const std::vector<T1>& v1, const T2& a)
{
	// vec<<scal
	const SIZE_T N(v1.size());
	if (N < 2) {
		return v1;
	}

	if (a == 0) {
		return v1;
	}
	else {
		std::vector<T1> rst(v1);
		if (a > 0) {
			std::rotate(rst.begin(), rst.begin() + a % N, rst.end());
		}
		else {
			std::rotate(rst.begin(), rst.begin() + N - (-a) % N, rst.end());
		}
		return rst;
	}
}

template <typename T1, typename T2>
typename std::enable_if< std::is_integral<T2>::value, std::vector<T1>& >::type
operator<<=(std::vector<T1>& v1, const T2& a)
{
	// vec<<=scal
	const SIZE_T N(v1.size());
	if (N < 2) {
		return v1;
	}

	if (a > 0) {
		std::rotate(v1.begin(), v1.begin() + a % N, v1.end());
	}
	else if (a < 0) {
		std::rotate(v1.begin(), v1.begin() + N - (-a) % N, v1.end());
	}
	return v1;
}

template <typename T1, typename T2>
typename std::enable_if< std::is_integral<T2>::value, std::vector<T1> >::type
operator>>(const std::vector<T1>& v1, const T2& a)
{
	// vec>>scal
	return v1 << -a;
}

template <typename T1, typename T2>
typename std::enable_if< std::is_integral<T2>::value, std::vector<T1>& >::type
operator>>=(std::vector<T1>& v1, const T2& a)
{
	// vec>>=scal
	v1<<=-a;
	return v1;
}


template <typename T1>
auto operator~(const std::vector<T1>& v1) -> std::vector<decltype(v1.at(0) / norm(v1))>
{
	// ~v => extract unit vector along v1 direction
	const auto v1nrm(norm(v1));
	const SIZE_T N(v1.size());
	std::vector<decltype(v1[0] / v1nrm)> rst(N);
	for (SIZE_T j(0); j < N; ++j) {
		rst[j] = v1[j] / v1nrm;
	}
	return rst;
}

// other utilities

template <typename T>
std::vector<T> subvec(const std::vector<T>& v, SIZE_T start, SIZE_T N)
{
	// get sub-vector (v[start], v[start+1], ..., v[start + N - 1])
    return std::vector<T>(v.begin() + start, v.begin() + start + N);
}

template <typename T>
std::vector<T> subvec(const std::vector<T>& v, const std::vector<BOOL_T>& flags)
{
	// get sub-vector (v[k]) for all flags[k] == true
    assertsize(v, flags);
    const SIZE_T N(v.size());
	std::vector<T> rst;
	for (SIZE_T j(0); j < N; ++j) {
		if (flags[j]) {
			rst.push_back(v[j]);
		}
	}
	return rst;
}

template <typename T, typename T1>
typename std::enable_if< std::is_integral<T1>::value, std::vector<T> >::type
subvec(const std::vector<T>& v, const std::vector<T1>& idx)
{
	// get subvector (v[k]) for all k in std::vector idx
    const SIZE_T N(idx.size());
	std::vector<T> rst(N);
	for (T1 j(0); j < N; ++j) {
		rst[j] = v[idx[j]];
	}
	return rst;
}


template <typename T> 
std::vector<T> linspace(const T& xmin, const T& xmax, SIZE_T Nx, BOOL_T endpoint = true) 
{
	// see numpy linspace
	std::vector<T> x(Nx);
	const T dx(endpoint ? (xmax - xmin) / (Nx - 1) : (xmax - xmin) / Nx);
	for (SIZE_T j(0); j < Nx; ++j) {
		x[j] = xmin + j * dx;
	}
	return x;
}

template <typename T> 
std::vector<T> linspace(const T& xmin, const T& xmax, SIZE_T Nx, T& dx, BOOL_T endpoint = true) 
{
	// see numpy linspace, dx requested 
	std::vector<T> x(Nx);
	dx = (endpoint ? (xmax - xmin) / (Nx - 1) : (xmax - xmin) / Nx);
	for (SIZE_T j(0); j < Nx; ++j) {
		x[j] = xmin + j * dx;
	}
	return x;
}


template <typename T>
std::vector<T> arange(T start, T end, T step = 1) 
{
	// see numpy.arange
	std::vector<T> rst;
	rst.reserve(static_cast<SIZE_T>((end - start) / step + 1));

	T x(start);
	while (x < end) {
		rst.push_back(x);
		x += step;
	}
	return rst;
}

template <typename T>
std::vector<T> arange(T end) 
{
	// see numpy.arange
	return arange(static_cast<T>(0), end);
}


template <typename T>
void meshgrid(const std::vector<T>& X, const std::vector<T>& Y, std::vector<T>& meshX, std::vector<T>& meshY) 
{
	// see matlab meshgrid
	const SIZE_T Nx(X.size());
	const SIZE_T Ny(Y.size());

	meshX.resize(Nx * Ny);
	meshY.resize(Nx * Ny);

	for (SIZE_T j(0); j < Nx; ++j) {
		for (SIZE_T k(0); k < Ny; ++k) {
			meshX[k + j * Ny] = X[j];
			meshY[k + j * Ny] = Y[k];
		}
	}
}

#endif
