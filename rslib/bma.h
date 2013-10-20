// Copyright 2013 sycy600

/// \file bma.h Berlekamp-Massey algorithm.

#ifndef RSLIB_BMA_H_
#define RSLIB_BMA_H_

#include <rslib/extendedfieldelement.h>
#include <rslib/polynomial.h>

namespace rslib {

/// \brief Find error locator polynomial.
/// \param syndromePolynomial Syndrome polynomial of received word
///        S_0 + S_1x + S_2x^2 + ...
/// \param errorCorrectionCapability Error correction capability of
///        code which was used to encode information.
/// \return Error locator polynomial.
/// Source: Kody korekcyjne, kody Reeda-Solomon, lecture material.
Polynomial<ExtendedFieldElement> findLFSRPolynomial(
    const Polynomial<ExtendedFieldElement>& syndromePolynomial,
    unsigned int errorCorrectionCapability);

}  // namespace rslib

#endif  // RSLIB_BMA_H_
