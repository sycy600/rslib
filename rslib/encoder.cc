// Copyright 2013 sycy600

#include <rslib/encoder.h>

namespace rslib {

Encoder::Encoder(unsigned int errorCorrectionCapability,
                 const ExtendedField& extendedField)
  : errorCorrectionCapability_(errorCorrectionCapability),
    extendedField_(extendedField),
    codeGenerator_(buildCodeGenerator(errorCorrectionCapability,
                                      extendedField)),
    encodingShifter_(buildEncodingShifter(errorCorrectionCapability,
                                          extendedField)) {
}

Polynomial<ExtendedFieldElement> Encoder::encode(
    const Polynomial<ExtendedFieldElement>& information) const {
  Polynomial<ExtendedFieldElement> result = information * encodingShifter_;
  result -= (result % codeGenerator_);
  return result;
}

Polynomial<ExtendedFieldElement> Encoder::getCodeGenerator() const {
  return codeGenerator_;
}

Polynomial<ExtendedFieldElement> Encoder::buildEncodingShifter(
    unsigned int errorCorrectionCapability,
    const ExtendedField& extendedField) const {
  Polynomial<ExtendedFieldElement> shifter =
      Polynomial<ExtendedFieldElement>({
                       ExtendedFieldElement(0, extendedField),
                       ExtendedFieldElement(1, extendedField)});

  unsigned int numIterations = 2 * errorCorrectionCapability - 1;
  Polynomial<ExtendedFieldElement> result = shifter;
  for (unsigned int i = 0; i < numIterations; ++i) {
    result *= shifter;
  }
  return result;
}

Polynomial<ExtendedFieldElement> Encoder::buildCodeGenerator(
    unsigned int errorCorrectionCapability,
    const ExtendedField& extendedField) const {
  Polynomial<ExtendedFieldElement> generator =
      Polynomial<ExtendedFieldElement>({
                           -ExtendedFieldElement(2, extendedField),
                           ExtendedFieldElement(1, extendedField)});
  Polynomial<ExtendedFieldElement> monomial = generator;
  unsigned int numIterations = 2 * errorCorrectionCapability - 1;
  ExtendedFieldElement alpha(2, extendedField);
  for (unsigned int i = 0; i < numIterations; ++i) {
    monomial.setValue(0, monomial.getValue(0) * alpha);
    generator *= monomial;
  }
  return generator;
}

}  // namespace rslib

