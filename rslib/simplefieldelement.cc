// Copyright 2013 sycy600

#include <rslib/simplefieldelement.h>

namespace rslib {

template <>
SimpleFieldElement getZero(SimpleFieldElement elem) {
  const SimpleField& sf = elem.getField();
  return SimpleFieldElement(0, sf);
}

}  // namespace rslib
