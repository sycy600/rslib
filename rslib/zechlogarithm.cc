// Copyright 2013 sycy600

#include <rslib/zechlogarithm.h>
#include <limits>

namespace rslib {

ZechLogarithm::ZechLogarithm(unsigned int value)
  : value_(value) { }

bool ZechLogarithm::isMinusInfinity() const {
  return std::numeric_limits<unsigned int>::max() == value_;
}

unsigned int ZechLogarithm::getValue() const {
  return value_;
}

}  // namespace rslib
