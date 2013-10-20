// Copyright 2013 sycy600

#include <rslib/forney.h>

namespace rslib {

std::vector<ExtendedFieldElement> ForneyAlgorithm::findErrorValues(
    const std::vector<ExtendedFieldElement>& errorLocators,
    const Polynomial<ExtendedFieldElement>& syndromePolynomial,
    const Polynomial<ExtendedFieldElement>& errorLocatorPolynomial) {
  const Polynomial<ExtendedFieldElement> errorEvaluatorPolynomial
      = calculateErrorEvaluatorPolynomial(syndromePolynomial,
                                          errorLocatorPolynomial);
  const Polynomial<ExtendedFieldElement> errorLocatorPolynomialDerivative
      = calculatePolynomialDerivative(errorLocatorPolynomial);
  std::vector<ExtendedFieldElement> result;
  for (const ExtendedFieldElement& errorLocator : errorLocators) {
    ExtendedFieldElement errorLocatorInverse
        = errorLocator.multiplicativeInverse();
    ExtendedFieldElement errorValue
        = -(errorEvaluatorPolynomial.evaluate(errorLocatorInverse)
            / errorLocatorPolynomialDerivative.evaluate(errorLocatorInverse));
    result.push_back(errorValue);
  }
  return result;
}

Polynomial<ExtendedFieldElement>
ForneyAlgorithm::calculateErrorEvaluatorPolynomial(
    const Polynomial<ExtendedFieldElement>& syndromePolynomial,
    const Polynomial<ExtendedFieldElement>& errorLocatorPolynomial) {
  const ExtendedField& extendedField
      = syndromePolynomial.getValue(0).getField();
  Polynomial<ExtendedFieldElement> errorEvaluatorPolynomial
      = errorLocatorPolynomial * syndromePolynomial;
  Polynomial<ExtendedFieldElement> moduloer(
      {ExtendedFieldElement(0, extendedField)});
  moduloer.setValue(syndromePolynomial.getDegree(),
                    ExtendedFieldElement(1, extendedField));
  errorEvaluatorPolynomial = errorEvaluatorPolynomial % moduloer;
  return errorEvaluatorPolynomial;
}

Polynomial<ExtendedFieldElement>
ForneyAlgorithm::calculatePolynomialDerivative(
    const Polynomial<ExtendedFieldElement>& polynomial) {
  const ExtendedField& extendedField = polynomial.getValue(0).getField();
  if (polynomial.getDegree() == 0) {
    return Polynomial<ExtendedFieldElement>(
        {ExtendedFieldElement(0, extendedField)});
  }
  std::vector<ExtendedFieldElement> coefficients;
  for (unsigned int i = 1; i < polynomial.getDegree() + 1; ++i) {
    Polynomial<SimpleFieldElement> polynomialRepresentationOfElement
        = polynomial.getValue(i).getPolynomialRepresentation();
    SimpleField sf = polynomialRepresentationOfElement.getValue(0).getField();
    // Multiply each coefficient of polynomial representation by constant.
    Polynomial<SimpleFieldElement> mul({SimpleFieldElement(i, sf)});
    polynomialRepresentationOfElement *= mul;
    coefficients.push_back(
          ExtendedFieldElement(polynomialRepresentationOfElement,
                               extendedField));
  }
  return Polynomial<ExtendedFieldElement>(coefficients);
}

}  // namespace rslib
