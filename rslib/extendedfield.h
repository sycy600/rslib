// Copyright 2013 sycy600

/// \file extendedfield.h Extended finite field.

#ifndef RSLIB_EXTENDEDFIELD_H_
#define RSLIB_EXTENDEDFIELD_H_

#include <rslib/polynomial.h>
#include <rslib/simplefieldelement.h>
#include <vector>

namespace rslib {

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

  /// \brief Zech Logarithm class.
  class ZechLogarithm {
  public:
    /// \brief Constructor.
    explicit ZechLogarithm(unsigned int value);

    /// \brief Check if Zech Logarithm equals to minus infinity.
    bool isMinusInfinity() const;

    /// \brief Get value.
    unsigned int getValue() const;

  private:
    unsigned int value_;
  };

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

/// \brief Check if two Zech logarithms are equal.
inline bool operator==(const ExtendedField::ZechLogarithm& first,
                       const ExtendedField::ZechLogarithm& second) {
  return first.getValue() == second.getValue();
}

/// \brief Check if two Zech logarithms are not equal.
inline bool operator!=(const ExtendedField::ZechLogarithm& first,
                       const ExtendedField::ZechLogarithm& second) {
  return !(first == second);
}

/// \brief Print Zech logarithm to output stream.
inline std::ostream& operator<<(
    std::ostream& os,  // NOLINT(runtime/references)
    const ExtendedField::ZechLogarithm&zechLogarithm) {
  if (zechLogarithm.isMinusInfinity()) {
    os << "-INF";
  } else {
    os << zechLogarithm.getValue();
  }
  return os;
}

}  // namespace rslib

#endif  // RSLIB_EXTENDEDFIELD_H_
