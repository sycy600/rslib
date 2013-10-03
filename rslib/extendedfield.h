// Copyright 2013 sycy600

/// \file extendedfield.h Extended finite field.

#ifndef RSLIB_EXTENDEDFIELD_H_
#define RSLIB_EXTENDEDFIELD_H_

#include <rslib/polynomial.h>
#include <rslib/simplefieldelement.h>
#include <rslib/zechlogarithm.h>
#include <vector>

namespace rslib {

/// \brief Extended finite field.
class ExtendedField {
 public:
  /// \brief Constructor.
  explicit ExtendedField(const Polynomial<SimpleFieldElement>& generator);

  /// \brief Get generator.
  const Polynomial<SimpleFieldElement>& getGenerator() const;

  /// \brief Get characteristic.
  unsigned int getCharacteristic() const;

  /// \brief Get extension order.
  unsigned int getExtensionOrder() const;

  /// \brief Get size.
  unsigned int getSize() const;

  /// \brief Check if two extended fields are equal.
  bool operator==(const ExtendedField& other) const;

  /// \brief Check if two extended fields are not equal.
  bool operator!=(const ExtendedField& other) const;

 private:
  const Polynomial<SimpleFieldElement> generator_;
  const unsigned int characteristic_;
  const unsigned int extensionOrder_;
  const unsigned int size_;
  const SimpleField simpleField_;
  std::vector<Polynomial<SimpleFieldElement>> polynomialRepresentation_;
  std::vector<ZechLogarithm> zechLogarithms_;

  void createPolynomialRepresentation();

  void createAdditionTable();

  ZechLogarithm getZechLogarithm(unsigned int index) const;

  Polynomial<SimpleFieldElement>
  getPolynomialRepresentation(unsigned int index) const;

  friend class ExtendedFieldElement;
};

}  // namespace rslib

#endif  // RSLIB_EXTENDEDFIELD_H_
