// Copyright 2013 sycy600

/// \file simplefieldelement.h Simple field element.

#ifndef RSLIB_SIMPLEFIELDELEMENT_H_
#define RSLIB_SIMPLEFIELDELEMENT_H_

#include <rslib/simplefield.h>
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
  SimpleFieldElement(unsigned int value, const SimpleField& simpleField)
    : simpleField_(simpleField) {
    value_ = value % simpleField.getCharacteristic();
  }

  /// \brief Get value.
  unsigned int getValue() const {
    return value_;
  }

  /// \brief Assignment operator.
  SimpleFieldElement& operator=(const SimpleFieldElement& other) {
    // Assigned element must be in the same field.
    if (getField() != other.getField()) {
      throw SimpleFieldElementException(
            "Assignment to field element from different field");
    }
    value_ = other.getValue();
    return *this;
  }

  /// \brief Get field.
  const SimpleField& getField() const {
    return simpleField_;
  }

 private:
  unsigned int value_;
  const SimpleField& simpleField_;
};

/// \brief Check if two simple field elements are equal.
inline bool operator==(const SimpleFieldElement& first,
                       const SimpleFieldElement& second) {
  if (first.getField() != second.getField()) {
    throw SimpleFieldElementException(
          "Assignment to field element from different field");
  }
  return first.getValue() == second.getValue();
}

/// \brief Check if two simple field elements are not equal.
inline bool operator!=(const SimpleFieldElement& first,
                       const SimpleFieldElement& second) {
  return !(first == second);
}

}  // namespace rslib

#endif  // RSLIB_SIMPLEFIELDELEMENT_H_
