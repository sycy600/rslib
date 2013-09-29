// Copyright 2013 sycy600

/// \file extendedfield.h Extended finite field.

#ifndef RSLIB_EXTENDEDFIELD_H_
#define RSLIB_EXTENDEDFIELD_H_

#include <rslib/extendedfieldelement.h>
#include <rslib/polynomial.h>
#include <rslib/simplefieldelement.h>
#include <rslib/zechlogarithm.h>
#include <vector>

namespace rslib {

class ExtendedFieldElement;

/// \brief Extended finite field.
class ExtendedField {
 public:
  /// \brief Constructor.
  explicit ExtendedField(const Polynomial<SimpleFieldElement>& generator);

  /// \brief Get generator.
  const Polynomial<SimpleFieldElement>& getGenerator() const {
    return generator_;
  }

  /// \brief Get characteristic.
  unsigned int getCharacteristic() const {
    return characteristic_;
  }

  /// \brief Get extension order.
  unsigned int getExtensionOrder() const {
    return extensionOrder_;
  }

  /// \brief Get size.
  unsigned int size() const {
    return size_;
  }

 private:
  const Polynomial<SimpleFieldElement> generator_;
  const unsigned int characteristic_;
  const unsigned int extensionOrder_;
  const unsigned int size_;
  const SimpleField simpleField_;
  std::vector<Polynomial<SimpleFieldElement>> polynomialRepresentation_;
  std::vector<ZechLogarithm> zechLogarithms_;

  friend class ExtendedFieldElement;

  void createPolynomialRepresentation();

  void createAdditionTable();

  ExtendedFieldElement add(const ExtendedFieldElement& first,
                           const ExtendedFieldElement& second) const;

  ExtendedFieldElement additiveInverse(
      const ExtendedFieldElement& element) const;

  ExtendedFieldElement multiply(const ExtendedFieldElement& first,
                                const ExtendedFieldElement& second) const;

  ExtendedFieldElement multiplicativeInverse(
      const ExtendedFieldElement& element) const;
};

/// \brief Check if two extended fields are equal.
inline bool operator==(const ExtendedField& first,
                       const ExtendedField& second) {
  return first.getGenerator() == second.getGenerator();
}

/// \brief Check if two extended fields are not equal.
inline bool operator!=(const ExtendedField& first,
                       const ExtendedField& second) {
  return !(first == second);
}

}  // namespace rslib

#endif  // RSLIB_EXTENDEDFIELD_H_
