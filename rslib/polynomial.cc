// Copyright 2013 sycy600

#include <rslib/polynomial.h>

namespace rslib {

template <>
int getZero(int elem) { return 0; }

template <>
unsigned int getZero(unsigned int elem) { return 0u; }

template <>
double getZero(double elem) { return 0.0; }

}  // namespace rslib

