// Copyright 2013 sycy600

#include <rslib/bmadecoder.h>
#include <rslib/bma.h>
#include <rslib/errorlocators.h>
#include <rslib/forney.h>
#include <rslib/syndrome.h>
#include <vector>

namespace rslib {

BMADecoder::BMADecoder(
    unsigned int errorCorrectionCapability,
    const ExtendedField& extendedField)
  : errorCorrectionCapability_(errorCorrectionCapability),
    extendedField_(extendedField) {
}

Polynomial<ExtendedFieldElement> BMADecoder::decode(
    const Polynomial<ExtendedFieldElement>& receivedWord) const {
  const Polynomial<ExtendedFieldElement> syndromePolynomial
      = calculateSyndromePolynomial(receivedWord, errorCorrectionCapability_);
  // No errors.
  if (isReceivedWordAValidCodeword(syndromePolynomial)) {
    return extractInformation(receivedWord);
  }
  const Polynomial<ExtendedFieldElement> errorLocatorPolynomial
      = findLFSRPolynomial(syndromePolynomial, errorCorrectionCapability_);
  // Find where errors are located.
  const std::vector<ExtendedFieldElement> errorLocators
      = findErrorLocators(errorLocatorPolynomial);
  // Find what are the error values.
  const std::vector<ExtendedFieldElement> errorValues
      = ForneyAlgorithm::findErrorValues(errorLocators,
                                         syndromePolynomial,
                                         errorLocatorPolynomial);
  // If there are known error locations and error values then correct them.
  Polynomial<ExtendedFieldElement> correctedWord
      = correctWord(receivedWord, errorLocators, errorValues);
  return extractInformation(correctedWord);
}

Polynomial<ExtendedFieldElement> BMADecoder::correctWord(
    const Polynomial<ExtendedFieldElement>& receivedWord,
    const std::vector<ExtendedFieldElement>& errorLocators,
    const std::vector<ExtendedFieldElement>& errorValues) const {
  Polynomial<ExtendedFieldElement> correctedWord(receivedWord);
  for (unsigned int i = 0; i < errorLocators.size(); ++i) {
    correctedWord.setValue(
          errorLocators[i].getValue() - 1,
          correctedWord.getValue(errorLocators[i].getValue() - 1)
             - errorValues[i]);
  }
  return correctedWord;
}

Polynomial<ExtendedFieldElement> BMADecoder::extractInformation(
    const Polynomial<ExtendedFieldElement>& receivedWord) const {
  std::vector<ExtendedFieldElement> coefficients;
  unsigned int numberOfInformationPositions
      = extendedField_.getSize() - 2 * errorCorrectionCapability_ + 1;
  for (unsigned int i = 0; i < numberOfInformationPositions; ++i) {
    coefficients.push_back(
          receivedWord.getValue(2 * errorCorrectionCapability_ + i));
  }
  return Polynomial<ExtendedFieldElement>(coefficients);
}

bool BMADecoder::isReceivedWordAValidCodeword(
    const Polynomial<ExtendedFieldElement>& syndromePolynomial) const {
  const ExtendedFieldElement zero(0, extendedField_);
  return syndromePolynomial.getDegree() == 0
      && syndromePolynomial.getValue(0) == zero;
}

}  // namespace rslib

