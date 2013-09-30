// Copyright 2013 sycy600

#include <rslib/simplefield.h>
#include <cmath>

namespace rslib {

SimpleField::SimpleField(unsigned int characteristic)
  : characteristic_(characteristic) { }

unsigned int SimpleField::getCharacteristic() const {
  return characteristic_;
}

bool operator!=(const SimpleField& first, const SimpleField& second) {
  return !(first == second);
}

bool operator==(const SimpleField& first, const SimpleField& second) {
  return first.getCharacteristic() == second.getCharacteristic();
}

}  // namespace rslib
