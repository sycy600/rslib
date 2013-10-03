// Copyright 2013 sycy600

/// \file extendedfieldelement.h Extended field element.

#ifndef RSLIB_EXTENDEDFIELDELEMENT_H_
#define RSLIB_EXTENDEDFIELDELEMENT_H_

#include <rslib/extendedfield.h>
#include <rslib/polynomial.h>
#include <rslib/simplefieldelement.h>
#include <rslib/zechlogarithm.h>
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
                       const ExtendedField& extendedField);

  /// \brief Get value.
  unsigned int getValue() const;

  /// \brief Assignment operator.
  ExtendedFieldElement& operator=(const ExtendedFieldElement& other);

  /// \brief Get field.
  const ExtendedField& getField() const;

  /// \brief Get polynomial representation.
  Polynomial<SimpleFieldElement> getPolynomialRepresentation() const;

  /// \brief Get Zech logarithm.
  ZechLogarithm getZechLogarithm() const;

  /// \brief Addition operator.
  ExtendedFieldElement& operator+=(const ExtendedFieldElement& other);

  /// \brief Additive inverse operator.
  ExtendedFieldElement operator-() const;

  /// \brief Subtraction operator.
  ExtendedFieldElement& operator-=(const ExtendedFieldElement& other);

  /// \brief Multiplication operator.
  ExtendedFieldElement& operator*=(const ExtendedFieldElement& other);

  /// \brief Multiplicative inverse.
  ExtendedFieldElement multiplicativeInverse() const;

  /// \brief Division operator.
  ExtendedFieldElement& operator/=(const ExtendedFieldElement& other);

  /// \brief Check if two extended field elements are equal.
  bool operator==(const ExtendedFieldElement& other) const;

  /// \brief Check if two extended field elements are not equal.
  bool operator!=(const ExtendedFieldElement& other) const;

  /// \brief Add two extended field elements.
  ExtendedFieldElement operator+(const ExtendedFieldElement& other) const;

  /// \brief Subtract one extended field element from other extended
  ///        field element.
  ExtendedFieldElement operator-(const ExtendedFieldElement& other) const;

  /// \brief Multiply two extended field elements.
  ExtendedFieldElement operator*(const ExtendedFieldElement& other) const;

  /// \brief Divide one extended field element by other extended
  ///        field element.
  ExtendedFieldElement operator/(const ExtendedFieldElement& other) const;

 private:
  unsigned int value_;
  const ExtendedField& extendedField_;

  void checkIfTheSameField(const ExtendedFieldElement& other) const;
};

/// \brief Print extended field element to output stream.
inline std::ostream& operator<<(
    std::ostream& os,  // NOLINT(runtime/references)
    const ExtendedFieldElement& element) {
  unsigned int value = element.getValue();
  if (value <= 1) {
    os << value;
  } else if (value == 2) {
    os << "A";
  } else {
    os << "A^" << (value - 1);
  }
  return os;
}

}  // namespace rslib

#endif  // RSLIB_EXTENDEDFIELDELEMENT_H_
