// Copyright 2013 sycy600

/// \file bmadecoder.h Reed-Solomon code Berlekamp-Massey decoder.

#ifndef RSLIB_BMADECODER_H_
#define RSLIB_BMADECODER_H_

#include <rslib/extendedfield.h>
#include <rslib/extendedfieldelement.h>
#include <rslib/polynomial.h>
#include <vector>

namespace rslib {

/// \brief Reed-Solomon code Berlekamp-Massey decoder.
class BMADecoder {
 public:
  /// \brief Constructor.
  /// \param errorCorrectionCapability The number of errors code can repair.
  /// \param extendedField Extended field where are placed codewords.
  BMADecoder(unsigned int errorCorrectionCapability,
             const ExtendedField& extendedField);

  /// \brief Decode received word and if possible correct errors if any.
  /// \param receivedWord Received word to be decoded.
  /// \return If possible, decoded information polynomial.
  Polynomial<ExtendedFieldElement> decode(
      const Polynomial<ExtendedFieldElement>& receivedWord) const;

 private:
  // Used to shift information polynomial while encoding.
  const unsigned int errorCorrectionCapability_;

  const ExtendedField& extendedField_;

  // Correct word by subtracting values at location given by error locators
  // and by value given by error values.
  Polynomial<ExtendedFieldElement> correctWord(
      const Polynomial<ExtendedFieldElement>& receivedWord,
      const std::vector<ExtendedFieldElement>& errorLocators,
      const std::vector<ExtendedFieldElement>& errorValues) const;

  // Extract information part of word.
  Polynomial<ExtendedFieldElement> extractInformation(
      const Polynomial<ExtendedFieldElement>& receivedWord) const;
};

}  // namespace rslib

#endif  // RSLIB_BMADECODER_H_
