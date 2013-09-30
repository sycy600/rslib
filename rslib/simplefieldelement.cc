// Copyright 2013 sycy600

#include <rslib/simplefieldelement.h>

namespace rslib {

template <>
SimpleFieldElement getZero(SimpleFieldElement elem) {
  const SimpleField& sf = elem.getField();
  return SimpleFieldElement(0, sf);
}

SimpleFieldElement::SimpleFieldElement(unsigned int value,
                                       const SimpleField& simpleField)
  : simpleField_(simpleField) {
  value_ = value % simpleField.getCharacteristic();
}

SimpleFieldElement& SimpleFieldElement::operator=(
    const SimpleFieldElement& other) {
  // Assigned element must be in the same field.
  checkIfTheSameField(other);
  value_ = other.getValue();
  return *this;
}

SimpleFieldElement& SimpleFieldElement::operator+=(
    const SimpleFieldElement& other) {
  checkIfTheSameField(other);
  *this = getField().add(*this, other);
  return *this;
}

SimpleFieldElement SimpleFieldElement::operator-() const {
  return getField().additiveInverse(*this);
}

SimpleFieldElement& SimpleFieldElement::operator-=(
    const SimpleFieldElement& other) {
  *this += -other;
  return *this;
}

SimpleFieldElement& SimpleFieldElement::operator*=(
    const SimpleFieldElement& other) {
  checkIfTheSameField(other);
  *this = getField().multiply(*this, other);
  return *this;
}

SimpleFieldElement SimpleFieldElement::multiplicativeInverse() const {
  if (getValue() == 0) {
    throw SimpleFieldElementException("Zero has no multiplicative inverse");
  }
  return getField().multiplicativeInverse(*this);
}

SimpleFieldElement& SimpleFieldElement::operator/=(
    const SimpleFieldElement& other) {
  *this *= other.multiplicativeInverse();
  return *this;
}

void SimpleFieldElement::checkIfTheSameField(
    const SimpleFieldElement& other) const {
  if (getField() != other.getField()) {
    throw SimpleFieldElementException(
          "Assignment to field element from different field");
  }
}

bool operator==(const SimpleFieldElement& first,
                const SimpleFieldElement& second) {
  if (first.getField() != second.getField()) {
    throw SimpleFieldElementException(
          "Assignment to field element from different field");
  }
  return first.getValue() == second.getValue();
}

bool operator!=(const SimpleFieldElement& first,
                const SimpleFieldElement& second) {
  return !(first == second);
}

SimpleFieldElement operator+(const SimpleFieldElement& first,
                             const SimpleFieldElement& second) {
  SimpleFieldElement result(first);
  result += second;
  return result;
}

SimpleFieldElement operator-(const SimpleFieldElement& first,
                             const SimpleFieldElement& second) {
  SimpleFieldElement result(first);
  result -= second;
  return result;
}

SimpleFieldElement operator*(const SimpleFieldElement& first,
                             const SimpleFieldElement& second) {
  SimpleFieldElement result(first);
  result *= second;
  return result;
}

SimpleFieldElement operator/(const SimpleFieldElement& first,
                             const SimpleFieldElement& second) {
  SimpleFieldElement result(first);
  result /= second;
  return result;
}

}  // namespace rslib
