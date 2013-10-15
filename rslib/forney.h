// Copyright 2013 sycy600

/// \file forney.h Forney algorithm.

#ifndef RSLIB_FORNEY_H_
#define RSLIB_FORNEY_H_

#include <rslib/extendedfieldelement.h>
#include <rslib/polynomial.h>
#include <vector>

namespace rslib {

/// \brief Forney algorithm.
class ForneyAlgorithm {
 public:
  /// \brief Find error values at given locations.
  /// \param errorLocators Error locators.
  /// \param syndromePolynomial Syndrome polynomial.
  /// \param errorLocatorPolynomial Error locator polynomial.
  /// \return Error values at given locations. These returned values
  ///         have to be used together with error locators.
  /// Source: https://en.wikipedia.org/wiki/Forney_algorithm
  static std::vector<ExtendedFieldElement> findErrorValues(
      const std::vector<ExtendedFieldElement>& errorLocators,
      const Polynomial<ExtendedFieldElement>& syndromePolynomial,
      const Polynomial<ExtendedFieldElement>& errorLocatorPolynomial);
 private:
  static Polynomial<ExtendedFieldElement> calculateErrorEvaluatorPolynomial(
      const Polynomial<ExtendedFieldElement>& syndromePolynomial,
      const Polynomial<ExtendedFieldElement>& errorLocatorPolynomial);

  static Polynomial<ExtendedFieldElement> calculatePolynomialDerivative(
      const Polynomial<ExtendedFieldElement>& polynomial);
};

}  // namespace rslib

#endif  // RSLIB_FORNEY_H_
