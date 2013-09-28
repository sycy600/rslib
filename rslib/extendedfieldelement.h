// Copyright 2013 sycy600

/// \file extendedfieldelement.h Extended field element.

#ifndef RSLIB_EXTENDEDFIELDELEMENT_H_
#define RSLIB_EXTENDEDFIELDELEMENT_H_

#include <rslib/extendedfield.h>
#include <rslib/polynomial.h>
#include <rslib/simplefieldelement.h>
#include <stdexcept>
#include <string>

namespace rslib {

template <class T>
T getZero(T elem);

/// \brief Extended field exception.
class ExtendedFieldElementException : public std::runtime_error {
 public:
  /// \brief Constructor.
  explicit ExtendedFieldElementException(const std::string& message)
     : std::runtime_error(message) {}
};

/// \brief Extended field element.
class ExtendedFieldElement {
 public:
  /// \brief Constructor.
  /// \param value It can be zero or it is an exponent of alpha element.
  /// The exponent is given as exponent + 1, so element 0 is of value 0,
  /// element 1 is of value 1, element alpha is of value 2 etc.
  /// \param extendedField Extended field in which element is placed.
  ExtendedFieldElement(unsigned int value,
                       const ExtendedField& extendedField)
    : value_(value), extendedField_(extendedField) { }

  /// \brief Get value.
  unsigned int getValue() const {
    return value_;
  }

  /// \brief Assignment operator.
  ExtendedFieldElement& operator=(const ExtendedFieldElement& other) {
    // Assigned element must be in the same field.
    if (getField() != other.getField()) {
      throw ExtendedFieldElementException(
            "Assignment to field element from different field");
    }
    value_ = other.getValue();
    return *this;
  }

  /// \brief Get field.
  const ExtendedField& getField() const {
    return extendedField_;
  }

  /// \brief Get polynomial representation.
  Polynomial<SimpleFieldElement> getPolynomialRepresentation() const {
    return extendedField_.polynomialRepresentation_[value_];
  }

  /// \brief Get Zech logarithm.
  ExtendedField::ZechLogarithm getZechLogarithm() const {
    return extendedField_.zechLogarithms_[value_];
  }

 private:
  unsigned int value_;
  const ExtendedField& extendedField_;
};

/// \brief Check if two extended field elements are equal.
inline bool operator==(const ExtendedFieldElement& first,
                       const ExtendedFieldElement& second) {
  if (first.getField() != second.getField()) {
    throw ExtendedFieldElementException(
          "Elements must be placed in the same extended field");
  }
  return first.getValue() == second.getValue();
}

/// \brief Check if two extended field elements are not equal.
inline bool operator!=(const ExtendedFieldElement& first,
                       const ExtendedFieldElement& second) {
  return !(first == second);
}

/// \brief Print extended field element to output stream.
inline std::ostream& operator<<(
    std::ostream& os,  // NOLINT(runtime/references)
    const ExtendedFieldElement& element) {
  unsigned int value = element.getValue();
  if (value == 0) {
    os << 0;
  } else if (value == 1) {
    os << 1;
  } else if (value == 2) {
    os << "A";
  } else {
    os << "A^" << (value - 1);
  }
  return os;
}

}  // namespace rslib

#endif  // RSLIB_EXTENDEDFIELDELEMENT_H_
