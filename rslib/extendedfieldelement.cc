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
  : value_(value), extendedField_(extendedField) { }

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
  return extendedField_.polynomialRepresentation_[value_];
}

ZechLogarithm rslib::ExtendedFieldElement::getZechLogarithm() const {
  return extendedField_.zechLogarithms_[value_];
}

ExtendedFieldElement& ExtendedFieldElement::operator+=(
    const ExtendedFieldElement& other) {
  checkIfTheSameField(other);
  *this = getField().add(*this, other);
  return *this;
}

ExtendedFieldElement ExtendedFieldElement::operator-() const {
  return getField().additiveInverse(*this);
}

ExtendedFieldElement& ExtendedFieldElement::operator-=(
    const ExtendedFieldElement& other) {
  *this += -other;
  return *this;
}

ExtendedFieldElement& ExtendedFieldElement::operator*=(
    const ExtendedFieldElement& other) {
  checkIfTheSameField(other);
  *this = getField().multiply(*this, other);
  return *this;
}

ExtendedFieldElement ExtendedFieldElement::multiplicativeInverse() const {
  if (getValue() == 0) {
    throw ExtendedFieldElementException("Zero has no multiplicative inverse");
  }
  return getField().multiplicativeInverse(*this);
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

bool operator==(const ExtendedFieldElement& first,
                const ExtendedFieldElement& second) {
  if (first.getField() != second.getField()) {
    throw ExtendedFieldElementException(
          "Elements must be placed in the same extended field");
  }
  return first.getValue() == second.getValue();
}

bool operator!=(const ExtendedFieldElement& first,
                const ExtendedFieldElement& second) {
  return !(first == second);
}

ExtendedFieldElement operator+(const ExtendedFieldElement& first,
                               const ExtendedFieldElement& second) {
  ExtendedFieldElement result(first);
  result += second;
  return result;
}

ExtendedFieldElement operator-(const ExtendedFieldElement& first,
                               const ExtendedFieldElement& second) {
  ExtendedFieldElement result(first);
  result -= second;
  return result;
}

ExtendedFieldElement operator*(const ExtendedFieldElement& first,
                               const ExtendedFieldElement& second) {
  ExtendedFieldElement result(first);
  result *= second;
  return result;
}

ExtendedFieldElement operator/(const ExtendedFieldElement& first,
                               const ExtendedFieldElement& second) {
  ExtendedFieldElement result(first);
  result /= second;
  return result;
}

}  // namespace rslib
