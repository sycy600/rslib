// Copyright 2013 sycy600

#include <rslib/bma.h>

namespace rslib {

Polynomial<ExtendedFieldElement> findLFSRPolynomial(
    const Polynomial<ExtendedFieldElement>& syndromePolynomial,
    unsigned int errorCorrectionCapability) {
  const ExtendedField& extendedField
      = syndromePolynomial.getValue(0).getField();
  unsigned int LFSRLength = 0;
  Polynomial<ExtendedFieldElement> errorLocatorPolynomial(
                          {ExtendedFieldElement(1, extendedField)});
  Polynomial<ExtendedFieldElement> xPolynomial(
                          {ExtendedFieldElement(0, extendedField),
                           ExtendedFieldElement(1, extendedField)});
  Polynomial<ExtendedFieldElement> corrector = xPolynomial;
  unsigned int maxIterationsToFindLFSR = 2 * errorCorrectionCapability + 1;
  for (unsigned int i = 1; i < maxIterationsToFindLFSR; ++i) {
    ExtendedFieldElement discrepancy(0, extendedField);
    // Compute discrepancy.
    for (unsigned int j = 0; j <= LFSRLength; ++j) {
      discrepancy += syndromePolynomial.getValue(i - j - 1)
          * errorLocatorPolynomial.getValue(j);
    }
    Polynomial<ExtendedFieldElement> temp = errorLocatorPolynomial;
    // Correct LFSR polynomial if needed.
    if (discrepancy != ExtendedFieldElement(0, extendedField)) {
      errorLocatorPolynomial -=
          Polynomial<ExtendedFieldElement>({discrepancy}) * corrector;
      if ((2 * LFSRLength <= i - 1)) {
        LFSRLength = i - LFSRLength;
        corrector = temp / Polynomial<ExtendedFieldElement>({discrepancy});
      }
    }
    corrector *= xPolynomial;
  }
  return errorLocatorPolynomial;
}

}  // namespace rslib
