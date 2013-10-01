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
  return getField().getPolynomialRepresentationFromField(value_);
}

ZechLogarithm rslib::ExtendedFieldElement::getZechLogarithm() const {
  return getField().getZechLogarithmFromField(value_);
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
        getField().getZechLogarithmFromField(
                                  getValue() - other.getValue() + 1u)
        .getValue() - 1u) % (getField().size() - 1u) + 1u;
  } else {
    value_ = (
        getValue() +
        getField().getZechLogarithmFromField(
                                  other.getValue() - getValue() + 1u)
        .getValue() - 1u) % (getField().size() - 1u) + 1u;
  }
  return *this;
}

ExtendedFieldElement ExtendedFieldElement::operator-() const {
  if (getValue() == 0 || getField().getCharacteristic() == 2) {
    return *this;
  } else {
    unsigned int result =
        (getValue() + (getField().size() - 1u) / 2u - 1u)
            % (getField().size() - 1u) + 1u;
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
        % (getField().size() - 1u);
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
    unsigned int result = getField().size() + 1 - getValue();
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
