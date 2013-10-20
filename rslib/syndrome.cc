// Copyright 2013 sycy600

#include <rslib/syndrome.h>
#include <rslib/extendedfield.h>
#include <vector>

namespace rslib {

Polynomial<ExtendedFieldElement> calculateSyndromePolynomial(
    const Polynomial<ExtendedFieldElement>& receivedWord,
    unsigned int errorCorrectionCapability) {
  const ExtendedField& extendedField = receivedWord.getValue(0).getField();
  std::vector<ExtendedFieldElement> syndromeCoefficients;
  ExtendedFieldElement alpha(2, extendedField);
  ExtendedFieldElement nextFieldElement = alpha;
  unsigned int numberOfSyndromesToCalculate = 2 * errorCorrectionCapability;
  for (unsigned int i = 0; i < numberOfSyndromesToCalculate; ++i) {
    syndromeCoefficients.push_back(receivedWord.evaluate(nextFieldElement));
    nextFieldElement *= alpha;
  }
  return Polynomial<ExtendedFieldElement>(syndromeCoefficients);
}

}  // namespace rslib
