#ifndef _POSITIVE_MOD_HPP
#define _POSITIVE_MOD_HPP
/* positive_mod function, calculate remainder (and, optional, quotient)
 * remiander returned will ALWAYS BE POSITIVE!
 *
 * module
 */

#include <cmath>
#include <cassert>
#include <vector>
#include "types.hpp"
#include "type_traiter.hpp"

template <typename NumerType, typename DenumType>
inline typename std::enable_if< std::is_fundamental<NumerType>::value && std::is_fundamental<DenumType>::value, DenumType>::type
positive_mod(const NumerType& numer, const DenumType& denum, INT_T& qoutitent) {
	// calculate remainder & qoutitent
	assert(denum > 0); 
	qoutitent = static_cast<INT_T>(floor(1.0 * numer / denum));
	return numer - denum * qoutitent;
}

template <typename NumerType, typename DenumType>
inline typename std::enable_if< std::is_fundamental<NumerType>::value && std::is_fundamental<DenumType>::value, DenumType>::type
positive_mod(const NumerType& numer, const DenumType& denum) {
	// calculate remainder only
	assert(denum > 0); 
	INT_T qoutitent = static_cast<INT_T>(floor(1.0 * numer / denum));
	return numer - denum * qoutitent;
}

template <typename NumerType, typename DenumType>
inline typename std::enable_if< std::is_fundamental<NumerType>::value && std::is_fundamental<DenumType>::value, std::vector<DenumType> >::type
positive_mod(	const std::vector<NumerType>& numer, 
			const DenumType& denum,
			std::vector<INT_T>& qoutitent) 
{
	// vector - scalar
	const INT_T N(numer.size());
	qoutitent.resize(N);
	std::vector<DenumType> remainder(N);
	for (INT_T i(0); i < N; ++i) {
		remainder[i] = positive_mod(numer[i], denum, qoutitent[i]);
	}
	return remainder;
}

template <typename NumerType, typename DenumType>
inline typename std::enable_if< std::is_fundamental<NumerType>::value && std::is_fundamental<DenumType>::value, std::vector<DenumType> >::type
positive_mod(	const std::vector<NumerType>& numer, 
			const DenumType& denum)
{
	// vector - scalar
	const INT_T N(numer.size());
	INT_T qoutitent;
	std::vector<DenumType> remainder(N);
	for (INT_T i(0); i < N; ++i) {
		remainder[i] = positive_mod(numer[i], denum[i], qoutitent);
	}
	return remainder;
}

template <typename NumerType, typename DenumType>
inline std::vector<DenumType> positive_mod(	const std::vector<NumerType>& numer, 
										const std::vector<DenumType>& denum,
										std::vector<INT_T>& qoutitent) 
{
	// vector - vector
	assert(numer.size() == denum.size());
	const INT_T N(numer.size());
	qoutitent.resize(N);
	std::vector<DenumType> remainder(N);
	for (INT_T i(0); i < N; ++i) {
		remainder[i] = positive_mod(numer[i], denum[i], qoutitent[i]);
	}
	return remainder;
}

template <typename NumerType, typename DenumType>
inline std::vector<DenumType> positive_mod(	const std::vector<NumerType>& numer, 
										const std::vector<DenumType>& denum)
{
	// vector - vector
	assert(numer.size() == denum.size());
	const INT_T N(numer.size());
	INT_T qoutitent;
	std::vector<DenumType> remainder(N);
	for (INT_T i(0); i < N; ++i) {
		remainder[i] = positive_mod(numer[i], denum[i], qoutitent);
	}
	return remainder;
}


#endif // _POSITIVE_MOD_HPP
