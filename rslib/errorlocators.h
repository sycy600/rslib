// Copyright 2013 sycy600

/// \file errorlocators.h Function to find error locators.

#ifndef RSLIB_ERRORLOCATORS_H_
#define RSLIB_ERRORLOCATORS_H_

#include <rslib/extendedfieldelement.h>
#include <rslib/polynomial.h>
#include <vector>

namespace rslib {

/// \brief Find error locators by finding reciprocals of roots
///        of error locator polynomial.
/// \param errorLocatorPolynomial Error locator polynomial.
/// \return Error locators.
/// Source: Kody korekcyjne, kody Reeda-Solomon, lecture material.
std::vector<ExtendedFieldElement> findErrorLocators(
    const Polynomial<ExtendedFieldElement>& errorLocatorPolynomial);

}  // namespace rslib

#endif  // RSLIB_ERRORLOCATORS_H_
