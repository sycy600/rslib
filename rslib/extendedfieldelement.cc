// Copyright 2013 sycy600

#include <rslib/extendedfieldelement.h>

namespace rslib {

template <>
ExtendedFieldElement getZero(ExtendedFieldElement elem) {
  const ExtendedField& ef = elem.getField();
  return ExtendedFieldElement(0, ef);
}

}  // namespace rslib
