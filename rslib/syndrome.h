// Copyright 2013 sycy600

/// \file syndrome.h Syndrome operations.

#ifndef RSLIB_SYNDROME_H_
#define RSLIB_SYNDROME_H_

#include <rslib/extendedfieldelement.h>
#include <rslib/polynomial.h>

namespace rslib {

/// \brief Calculate syndrome polynomial for received word.
/// \param receivedWord Received word.
/// \param errorCorrectionCapability Error correction capability of
///        code which was used to encode information.
/// \return Syndrome polynomial S_0 + S_1x + S_2x^2 + ...
Polynomial<ExtendedFieldElement> calculateSyndromePolynomial(
    const Polynomial<ExtendedFieldElement>& receivedWord,
    unsigned int errorCorrectionCapability);

}  // namespace rslib

#endif  // RSLIB_SYNDROME_H_
