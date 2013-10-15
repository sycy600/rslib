// Copyright 2013 sycy600

#include <rslib/extendedfieldelement.h>

namespace rslib {

template <>
ExtendedFieldElement getZero(ExtendedFieldElement elem) {
  const ExtendedField& ef = elem.getField();
  return ExtendedFieldElement(0, ef);
}

ExtendedFieldElement::ExtendedFieldElement(unsigned int value,
                                           const ExtendedField& extendedField)
  : value_(value % extendedField.getSize()), extendedField_(extendedField) { }

ExtendedFieldElement::ExtendedFieldElement(
    Polynomial<SimpleFieldElement> polynomialRepresentation,
    const ExtendedField& extendedField)
  : extendedField_(extendedField) {
  bool found = false;
  // Find exponent of alpha element represented by polynomial representation.
  for (unsigned int i = 0; i < extendedField_.getSize(); ++i) {
    if (extendedField_.getPolynomialRepresentation(i)
       == polynomialRepresentation) {
      value_ = i;
      found = true;
      break;
    }
  }
  if (!found) {
    throw ExtendedFieldElementException("Element not found");
  }
}

ExtendedFieldElement& ExtendedFieldElement::operator=(
    const ExtendedFieldElement& other) {
  // Assigned element must be in the same field.
  if (getField() != other.getField()) {
    throw ExtendedFieldElementException(
          "Assignment to field element from different field");
  }
  value_ = other.getValue();
  return *this;
}

const ExtendedField& ExtendedFieldElement::getField() const {
  return extendedField_;
}

Polynomial<SimpleFieldElement>
ExtendedFieldElement::getPolynomialRepresentation() const {
  return getField().getPolynomialRepresentation(value_);
}

ZechLogarithm rslib::ExtendedFieldElement::getZechLogarithm() const {
  return getField().getZechLogarithm(value_);
}

ExtendedFieldElement& ExtendedFieldElement::operator+=(
    const ExtendedFieldElement& other) {
  checkIfTheSameField(other);
  if (other.getValue() == 0) {
    return *this;
  } else if (getValue() == 0) {
    *this = other;
  } else if (*this == -other) {
    value_ = 0;
  } else if (getValue() > other.getValue()) {
    value_ = (
        other.getValue() +
        getField().getZechLogarithm(getValue() - other.getValue() + 1u)
        .getValue() - 1u) % (getField().getSize() - 1u) + 1u;
  } else {
    value_ = (
        getValue() +
        getField().getZechLogarithm(other.getValue() - getValue() + 1u)
        .getValue() - 1u) % (getField().getSize() - 1u) + 1u;
  }
  return *this;
}

ExtendedFieldElement ExtendedFieldElement::operator-() const {
  if (getValue() == 0 || getField().getCharacteristic() == 2) {
    return *this;
  } else {
    unsigned int result =
        (getValue() + (getField().getSize() - 1u) / 2u - 1u)
            % (getField().getSize() - 1u) + 1u;
    return ExtendedFieldElement(result, getField());
  }
}

ExtendedFieldElement& ExtendedFieldElement::operator-=(
    const ExtendedFieldElement& other) {
  *this += -other;
  return *this;
}

ExtendedFieldElement& ExtendedFieldElement::operator*=(
    const ExtendedFieldElement& other) {
  checkIfTheSameField(other);
  if (getValue() == 0) {
    return *this;
  } else if (other.getValue() == 0) {
    value_ = 0;
  } else {
    value_ = 1 + (getValue() + other.getValue() - 2u)
        % (getField().getSize() - 1u);
  }
  return *this;
}

ExtendedFieldElement ExtendedFieldElement::multiplicativeInverse() const {
  if (getValue() == 0) {
    throw ExtendedFieldElementException("Zero has no multiplicative inverse");
  }
  if (getValue() == 1) {
    return *this;
  } else {
    unsigned int result = getField().getSize() + 1 - getValue();
    return ExtendedFieldElement(result, getField());
  }
}

ExtendedFieldElement& ExtendedFieldElement::operator/=(
    const ExtendedFieldElement& other) {
  *this *= other.multiplicativeInverse();
  return *this;
}

void ExtendedFieldElement::checkIfTheSameField(
    const ExtendedFieldElement& other) const {
  if (getField() != other.getField()) {
    throw ExtendedFieldElementException(
          "Assignment to field element from different field");
  }
}

bool ExtendedFieldElement::operator==(
                const ExtendedFieldElement& other) const {
  if (getField() != other.getField()) {
    throw ExtendedFieldElementException(
          "Elements must be placed in the same extended field");
  }
  return getValue() == other.getValue();
}

bool ExtendedFieldElement::operator!=(
                const ExtendedFieldElement& other) const {
  return !(*this == other);
}

ExtendedFieldElement ExtendedFieldElement::operator+(
                               const ExtendedFieldElement& other) const {
  ExtendedFieldElement result(*this);
  result += other;
  return result;
}

ExtendedFieldElement ExtendedFieldElement::operator-(
                               const ExtendedFieldElement& other) const {
  ExtendedFieldElement result(*this);
  result -= other;
  return result;
}

ExtendedFieldElement ExtendedFieldElement::operator*(
                               const ExtendedFieldElement& other) const {
  ExtendedFieldElement result(*this);
  result *= other;
  return result;
}

ExtendedFieldElement ExtendedFieldElement::operator/(
                               const ExtendedFieldElement& other) const {
  ExtendedFieldElement result(*this);
  result /= other;
  return result;
}

unsigned int ExtendedFieldElement::getValue() const {
  return value_;
}

}  // namespace rslib
