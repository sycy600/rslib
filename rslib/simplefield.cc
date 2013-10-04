// Copyright 2013 sycy600

#include <rslib/simplefield.h>
#include <cmath>

namespace rslib {

SimpleField::SimpleField(unsigned int characteristic)
  : characteristic_(characteristic) { }

unsigned int SimpleField::getCharacteristic() const {
  return characteristic_;
}

bool SimpleField::operator!=(const SimpleField& other) const {
  return !(*this == other);
}

bool SimpleField::operator==(const SimpleField& other) const {
  return getCharacteristic() == other.getCharacteristic();
}

}  // namespace rslib
