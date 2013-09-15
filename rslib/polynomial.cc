// Copyright 2013 sycy600

#include <rslib/polynomial.h>

namespace rslib {

template <>
int getZero() { return 0; }

template <>
unsigned int getZero() { return 0u; }

template <>
double getZero() { return 0.0; }

}  // namespace rslib

