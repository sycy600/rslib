// Copyright 2013 sycy600

#include <rslib/simplefieldelement.h>
#include <cmath>

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
  value_ = (getValue() + other.getValue()) % getField().getCharacteristic();
  return *this;
}

SimpleFieldElement SimpleFieldElement::operator-() const {
  unsigned int result = getField().getCharacteristic() - getValue();
  return SimpleFieldElement(result, getField());
}

SimpleFieldElement& SimpleFieldElement::operator-=(
    const SimpleFieldElement& other) {
  *this += -other;
  return *this;
}

SimpleFieldElement& SimpleFieldElement::operator*=(
    const SimpleFieldElement& other) {
  checkIfTheSameField(other);
  value_ = (getValue() * other.getValue()) % getField().getCharacteristic();
  return *this;
}

SimpleFieldElement SimpleFieldElement::multiplicativeInverse() const {
  if (getValue() == 0) {
    throw SimpleFieldElementException("Zero has no multiplicative inverse");
  }
  // a * a^-1 = 1 multiplicative inverse
  // a^p \equiv a (mod p) Fermat's little theorem
  // in finite fields:
  // a^p = a
  // a^{p-1} = 1
  // a^{p-2} = 1/a = a^-1
  // http://en.wikipedia.org/wiki/Finite_field_arithmetic
  unsigned int result = static_cast<unsigned int>(
      std::pow(getValue(), getField().getCharacteristic() - 2))
      % getField().getCharacteristic();
  return SimpleFieldElement(result, getField());
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
