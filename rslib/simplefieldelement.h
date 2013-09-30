// Copyright 2013 sycy600

/// \file simplefieldelement.h Simple field element.

#ifndef RSLIB_SIMPLEFIELDELEMENT_H_
#define RSLIB_SIMPLEFIELDELEMENT_H_

#include <rslib/simplefield.h>
#include <ostream>
#include <stdexcept>
#include <string>

namespace rslib {

template <class T>
T getZero(T elem);

/// \brief Simple field element exception.
class SimpleFieldElementException : public std::runtime_error {
 public:
  /// \brief Constructor.
  explicit SimpleFieldElementException(const std::string& message)
     : std::runtime_error(message) {}
};

/// \brief Simple field element.
class SimpleFieldElement {
 public:
  /// \brief Constructor.
  /// \param value Value of simple field element. This value is modulo'ed
  /// by field characteristic so it's always in the field.
  /// \param simpleField Field in which element is placed.
  SimpleFieldElement(unsigned int value, const SimpleField& simpleField);

  /// \brief Get value.
  unsigned int getValue() const {
    return value_;
  }

  /// \brief Assignment operator.
  SimpleFieldElement& operator=(const SimpleFieldElement& other);

  /// \brief Addition operator.
  SimpleFieldElement& operator+=(const SimpleFieldElement& other);

  /// \brief Additive inverse operator.
  SimpleFieldElement operator-() const;

  /// \brief Subtraction operator.
  SimpleFieldElement& operator-=(const SimpleFieldElement& other);

  /// \brief Multiplication operator.
  SimpleFieldElement& operator*=(const SimpleFieldElement& other);

  /// \brief Multiplicative inverse.
  SimpleFieldElement multiplicativeInverse() const;

  /// \brief Division operator.
  SimpleFieldElement& operator/=(const SimpleFieldElement& other);

  /// \brief Get field.
  const SimpleField& getField() const {
    return simpleField_;
  }

 private:
  unsigned int value_;
  const SimpleField& simpleField_;

  // Check if current object and other objects are in the same field.
  // If they are not then throw exception.
  void checkIfTheSameField(const SimpleFieldElement& other) const;
};

/// \brief Check if two simple field elements are equal.
bool operator==(const SimpleFieldElement& first,
                const SimpleFieldElement& second);

/// \brief Check if two simple field elements are not equal.
bool operator!=(const SimpleFieldElement& first,
                const SimpleFieldElement& second);

/// \brief Add two simple field elements.
SimpleFieldElement operator+(const SimpleFieldElement& first,
                             const SimpleFieldElement& second);

/// \brief Subtract one simple field element from other simple field element.
SimpleFieldElement operator-(const SimpleFieldElement& first,
                             const SimpleFieldElement& second);

/// \brief Multiply two simple field elements.
SimpleFieldElement operator*(const SimpleFieldElement& first,
                             const SimpleFieldElement& second);

/// \brief Divide one simple field element by other simple field element.
SimpleFieldElement operator/(const SimpleFieldElement& first,
                             const SimpleFieldElement& second);

/// \brief Print simple field element to output stream.
inline std::ostream& operator<<(std::ostream& os,  // NOLINT(runtime/references)
                                const SimpleFieldElement& element) {
  os << element.getValue();
  return os;
}

}  // namespace rslib

#endif  // RSLIB_SIMPLEFIELDELEMENT_H_
