// Copyright 2013 sycy600

#include <rslib/simplefield.h>
#include <cmath>

namespace rslib {

SimpleFieldElement SimpleField::add(const SimpleFieldElement& first,
                                    const SimpleFieldElement& second) const {
  unsigned int result = (first.getValue() + second.getValue())
      % getCharacteristic();
  return SimpleFieldElement(result, *this);
}

SimpleFieldElement SimpleField::additiveInverse(
    const SimpleFieldElement& element) const {
  unsigned int result = (getCharacteristic() - element.getValue())
      % getCharacteristic();
  return SimpleFieldElement(result, *this);
}

SimpleFieldElement SimpleField::multiply(
    const SimpleFieldElement& first,
    const SimpleFieldElement& second) const {
  unsigned int result = (first.getValue() * second.getValue())
      % getCharacteristic();
  return SimpleFieldElement(result, *this);
}

SimpleFieldElement SimpleField::multiplicativeInverse(
    const SimpleFieldElement& element) const {
  // a * a^-1 = 1 multiplicative inverse
  // a^p \equiv a (mod p) Fermat's little theorem
  // in finite fields:
  // a^p = a
  // a^{p-1} = 1
  // a^{p-2} = 1/a = a^-1
  // http://en.wikipedia.org/wiki/Finite_field_arithmetic
  unsigned int result = static_cast<unsigned int>(
        std::pow(element.getValue(), getCharacteristic() - 2))
      % getCharacteristic();
  return SimpleFieldElement(result, *this);
}

}  // namespace rslib
