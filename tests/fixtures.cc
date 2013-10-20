// Copyright 2013 sycy600

#include <rslib/bmadecoder.h>
#include <rslib/encoder.h>
#include <tests/fixtures.h>
#include <vector>

void RSTestFactory(unsigned int iterations,
                   unsigned int errorCorrectionCapability,
                   const rslib::ExtendedField& ef,
                   unsigned int maxNumberOfErrors) {
  rslib::Encoder encoder(errorCorrectionCapability, ef);
  rslib::BMADecoder decoder(errorCorrectionCapability, ef);
  for (unsigned int i = 0; i < iterations; ++i) {
    std::vector<rslib::ExtendedFieldElement> coefficients;
    for (unsigned int j = 0; j < 2 * errorCorrectionCapability; ++j) {
      coefficients.push_back(
            rslib::ExtendedFieldElement(
            std::rand() % ef.getSize(), ef));  // NOLINT(runtime/threadsafe_fn)
    }
    rslib::Polynomial<rslib::ExtendedFieldElement> information(coefficients);
    rslib::Polynomial<rslib::ExtendedFieldElement> codeword
        = encoder.encode(information);
    rslib::Polynomial<rslib::ExtendedFieldElement> receivedWord = codeword;
    unsigned int maxNumberOfErrorsThisIteration
     = std::rand() % (maxNumberOfErrors + 1);  // NOLINT(runtime/threadsafe_fn)
    for (unsigned int j = 0; j < maxNumberOfErrorsThisIteration; ++j) {
      receivedWord.setValue(
        std::rand() % (ef.getSize() - 1),  // NOLINT(runtime/threadsafe_fn)
        rslib::ExtendedFieldElement(
          std::rand() % ef.getSize(), ef));  // NOLINT(runtime/threadsafe_fn)
    }
    unsigned int varyingPositions = 0;
    for (unsigned int j = 0; j < ef.getSize() - 1; ++j) {
      if (codeword.getValue(j) != receivedWord.getValue(j)) {
        ++varyingPositions;
      }
    }
    if (varyingPositions <= errorCorrectionCapability) {
      ASSERT_EQ(decoder.decode(receivedWord), information);
    }
  }
}
