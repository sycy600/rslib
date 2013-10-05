// Copyright 2013 sycy600

/// \file encoder.h Reed-Solomon code encoder.

#ifndef RSLIB_ENCODER_H_
#define RSLIB_ENCODER_H_

#include <rslib/extendedfield.h>
#include <rslib/extendedfieldelement.h>
#include <rslib/polynomial.h>

namespace rslib {

/// \brief Reed-Solomon code encoder.
class Encoder {
 public:
  /// \brief Constructor.
  /// \param errorCorrectionCapability The number of errors code can repair.
  /// \param extendedField Extended field where are placed codewords.
  Encoder(unsigned int errorCorrectionCapability,
          const ExtendedField& extendedField);

  /// \brief Encode data.
  /// \param information Data to be encoded as information polynomial.
  /// \return Encoded data.
  Polynomial<ExtendedFieldElement> encode(
      const Polynomial<ExtendedFieldElement>& information) const;

  /// \brief Get generator polynomial of constructed code.
  Polynomial<ExtendedFieldElement> getCodeGenerator() const;

 private:
  unsigned int errorCorrectionCapability_;
  const ExtendedField& extendedField_;
  const Polynomial<ExtendedFieldElement> codeGenerator_;

  // Used to shift information polynomial while encoding.
  const Polynomial<ExtendedFieldElement> encodingShifter_;

  Polynomial<ExtendedFieldElement> buildEncodingShifter(
      unsigned int errorCorrectionCapability,
      const ExtendedField& extendedField) const;

  Polynomial<ExtendedFieldElement> buildCodeGenerator(
      unsigned int errorCorrectionCapability,
      const ExtendedField& extendedField) const;
};

}  // namespace rslib

#endif  // RSLIB_ENCODER_H_
