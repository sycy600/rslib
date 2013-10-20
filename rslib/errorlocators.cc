// Copyright 2013 sycy600

#include <rslib/errorlocators.h>

namespace rslib {

std::vector<ExtendedFieldElement> findErrorLocators(
    const Polynomial<ExtendedFieldElement>& errorLocatorPolynomial) {
  const ExtendedField& extendedField
      = errorLocatorPolynomial.getValue(0).getField();
  std::vector<ExtendedFieldElement> errorLocators;
  const ExtendedFieldElement zero(0, extendedField);
  const ExtendedFieldElement alpha(2, extendedField);
  ExtendedFieldElement nextFieldElement(1, extendedField);
  unsigned int sizeOfField = extendedField.getSize();
  for (unsigned int i = 1; i < sizeOfField; ++i) {
    if (errorLocatorPolynomial.evaluate(nextFieldElement) == zero) {
      errorLocators.push_back(nextFieldElement.multiplicativeInverse());
    }
    nextFieldElement *= alpha;
  }
  return errorLocators;
}

}  // namespace rslib
