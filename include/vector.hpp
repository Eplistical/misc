#ifndef _VECTOR_HPP
#define _VECTOR_HPP
/* module for vector operations
 * require C++11
 * written based on <vector>
 *
 * Gaohan
 */
#include <iostream>
#include <cmath>
#include <vector>
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

// basic operators 

template <typename T1, typename T2>
auto operator+(const std::vector<T1>& v1, const std::vector<T2>& v2) -> std::vector<decltype(v1.at(0) + v2.at(0))>
{
    const SIZE_T N = v1.size();
    assertsize(v1, v2);
    std::vector<decltype(v1.at(0) + v2.at(0))> rst(N);
    for(SIZE_T j = 0; j < N; j++)
        rst[j] = v1[j] + v2[j];
	return rst;
}

template <typename T1, typename T2>
auto operator+(const std::vector<T1>& v1, const T2& a) -> std::vector<decltype(v1.at(0) + a)>
{
    const SIZE_T N = v1.size();
    std::vector<decltype(v1.at(0) + a)> rst(N);
    for(SIZE_T j = 0; j < N; j++)
        rst[j] = v1[j] + a;
	return rst;
}

template <typename T1, typename T2>
auto operator+(const T2& a, const std::vector<T1>& v1) -> std::vector<decltype(a + v1.at(0))>
{
	return v1 + a;
}

template <typename T1, typename T2>
auto operator-(const std::vector<T1>& v1, const std::vector<T2>& v2) -> std::vector<decltype(v1.at(0) - v2.at(0))>
{
    const SIZE_T N = v1.size();
    assertsize(v1, v2);
    std::vector<decltype(v1.at(0) - v2.at(0))> rst(N);
    for(SIZE_T j = 0; j < N; j++)
        rst[j] = v1[j] - v2[j];
	return rst;
}

template <typename T1, typename T2>
auto operator-(const std::vector<T1>& v1, const T2& a) -> std::vector<decltype(v1.at(0) - a)>
{
    const SIZE_T N = v1.size();
    std::vector<decltype(v1.at(0) - a)> rst(N);
    for(SIZE_T j = 0; j < N; j++)
        rst[j] = v1[j] - a;
	return rst;
}

template <typename T1, typename T2>
auto operator-(const T2& a, const std::vector<T1>& v1) -> std::vector<decltype(a - v1.at(0))>
{
    const SIZE_T N = v1.size();
    std::vector<decltype(a - v1.at(0))> rst(N);
    for(SIZE_T j = 0; j < N; j++)
        rst[j] = a - v1[j];
	return rst;
}

template <typename T>
std::vector<T> operator-(const std::vector<T>& v1)
{
    const SIZE_T N = v1.size();
    std::vector<T> rst(N);
    for(SIZE_T j = 0; j < N; j++)
        rst[j] = -v1[j];
	return rst;
}

template <typename T1, typename T2>
auto operator*(const std::vector<T1>& v1, const std::vector<T2>& v2) -> std::vector<decltype(v1.at(0) * v2.at(0))>
{
    const SIZE_T N = v1.size();
    assertsize(v1, v2);
    std::vector<decltype(v1.at(0) * v2.at(0))> rst(N);
    for(SIZE_T j = 0; j < N; j++)
        rst[j] = v1[j] * v2[j];
	return rst;
}

template <typename T1, typename T2>
auto operator*(const std::vector<T1>& v1, const T2& a) -> std::vector<decltype(v1.at(0) * a)>
{
    const SIZE_T N = v1.size();
    std::vector<decltype(v1.at(0) * a)> rst(N);
    for(SIZE_T j = 0; j < N; j++)
        rst[j] = v1[j] * a;
	return rst;
}

template <typename T1, typename T2>
auto operator*(const T2& a, const std::vector<T1>& v1) -> std::vector<decltype(a * v1.at(0))>
{
	return v1 * a;
}

template <typename T1, typename T2>
auto operator/(const std::vector<T1>& v1, const std::vector<T2>& v2) -> std::vector<decltype(v1.at(0) / v2.at(0))>
{
    const SIZE_T N = v1.size();
    assertsize(v1, v2);
    std::vector<decltype(v1.at(0) / v2.at(0))> rst(N);
    for(SIZE_T j = 0; j < N; j++)
        rst[j] = v1[j] / v2[j];
	return rst;
}

template <typename T1, typename T2>
auto operator/(const std::vector<T1>& v1, const T2& a) -> std::vector<decltype(v1.at(0) / a)>
{
    const SIZE_T N = v1.size();
    std::vector<decltype(v1.at(0) / a)> rst(N);
    for(SIZE_T j = 0; j < N; j++)
        rst[j] = v1[j] / a;
	return rst;
}

template <typename T1, typename T2>
auto operator/(const T2& a, const std::vector<T1>& v1) -> std::vector<decltype(a / v1.at(0))>
{
    const SIZE_T N = v1.size();
    std::vector<decltype(a / v1.at(0))> rst(N);
    for(SIZE_T j = 0; j < N; j++)
        rst[j] = a / v1[j];
	return rst;
}

// vector utilities

template <typename T>
std::vector<T> abs(const std::vector<T>& v)
{
    const SIZE_T N = v.size();
    std::vector<T> rst(N);
    for(SIZE_T j = 0; j < N; j++) 
		rst[j] = std::abs(v[j]) ;
    return rst;
}

template <typename T1, typename T2>
std::vector<T1> pow(const std::vector<T1>& v1, const T2& a)
{
    const SIZE_T N = v1.size();
    std::vector<T1> rst(N);
    for(SIZE_T j = 0; j < N; j++)
        rst[j] = std::pow(v1[j], a);
	return rst;
}

template <typename T>
std::vector<T> exp(const std::vector<T>& v)
{
    const SIZE_T N = v.size();
    std::vector<T> rst(N);
    for(SIZE_T j = 0; j < N; j++) 
		rst[j] = std::exp(v[j]) ;
    return rst;
}

template <typename T>
std::vector<T> subvec(const std::vector<T>& v, SIZE_T start, SIZE_T N)
{
    return std::vector<T>(&v.at(start), &v.at(start + N));
}

template <typename T>
T sum(const std::vector<T>& v)
{
    T rst = static_cast<T>(0);
    const SIZE_T N = v.size();
    for(SIZE_T j = 0;j < N;j++) 
		rst += v.at(j);
    return rst;
}

template <typename T>
T mean(const std::vector<T>& v)
{
    return sum(v) / v.size();
}

template <typename T>
T product(const std::vector<T>& v)
{
    T rst = static_cast<T>(1);
    const SIZE_T N = v.size();
    for(SIZE_T j = 0;j < N;j++) 
		rst *= v.at(j);
    return rst;
}

template <typename T>
T norm(const std::vector<T>& v)
{
    return std::sqrt(sum(v * v));
}

template <typename T>
T min(const std::vector<T>& v)
{
    const SIZE_T N = v.size();
    T rst = v.at(0);
    for(INT_T j = 1;j < N;j++)
        rst = (v[j] < rst)?v[j]:rst;
    return rst;
}

template <typename T>
T max(const std::vector<T>& v)
{
    const SIZE_T N = v.size();
    T rst = v.at(0);
    for(INT_T j = 1;j < N;j++)
        rst = (v[j] > rst)?v[j]:rst;
    return rst;
}

std::vector<DOUBLE_T> linspace(DOUBLE_T xmin, DOUBLE_T xmax, SIZE_T Nx, BOOL_T endpoint = true) 
{
	std::vector<DOUBLE_T> x(Nx, 0.0);
	const DOUBLE_T dx(endpoint ? (xmax - xmin) / (Nx - 1) : (xmax - xmin) / Nx);
	for (SIZE_T j(0); j < Nx; ++j) {
		x[j] = xmin + j * dx;
	}
	return x;
}


template <typename T>
std::vector<T> arange(T start, T end, T step = 1) 
{
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
	return arange(static_cast<T>(0), end);
}

#endif
